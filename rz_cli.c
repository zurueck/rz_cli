#include <stdio.h>
#include <string.h>
#include "rz_cli.h"
#include "rz_ctype.h"

static Rz_cmd_s *s_cmd_table_ptr;
static int s_cmd_table_num;

/**
 * cmdStr should end with \n
 * @return 0 GG
 */
static int parse_command_string(char *cmdStr, char * argv[]) {
    int argc = 0;
    
    while (*cmdStr != '\n') {
        /** 
         * skip white
         * check 9        10   11   12   13            32
         * check 0x09     0x0A 0x0B 0x0C 0x0D          0x20
         * check \t(tab)  \r   VT   FF   CR(\n)(enter) space
         */
        while(isspace(*cmdStr)) {
            cmdStr++;    
        }
        
        argv[argc++] = cmdStr;  
        cmdStr++;

        /* find arg end */
        while(!isspace(*cmdStr)) {
            cmdStr++;    
        }

        /* check cmdStr end */
        if (*cmdStr == '\n' || *cmdStr == '\0') {
            /* add argv[] string end */
            *cmdStr = '\0';
            return argc;
        } 
        
        //overload
        *cmdStr++ = '\0';
        if (argc > CONFIG_RZ_CLI_MAX_ARG) {
            return argc;   
        }
    }
    return argc;
}

/**
 *
 * @return 0: gg
 */
static Rz_cmd_s * find_cmd(char *name, Rz_cmd_s *table) {
    Rz_cmd_s *cmdp = table;

    if (!cmdp->name) { 
        /* no command at all */
        return 0; 
    }
    
    while(strcmp(name, cmdp->name)) {
        if (cmdp >= table + s_cmd_table_num - 1) {
            /* out of range */
            return 0;
        }
        cmdp++;
    }

    return cmdp;
}

static int is_space_string(char *s) {
    while(isspace(*s)) {
        if (*s == '\n') {  /* str = "     " */
            return 1;   
        }
        s++;    
    }

    return 0;
}
    
void regist_cmd_table(Rz_cmd_s * table, int size) {
   s_cmd_table_ptr = table;
   s_cmd_table_num = size/sizeof(Rz_cmd_s);
}


/**
 *
 * @return  0 ok
 * @return  -1 nothing happend
 * @return  -2 no this command
 */
int cli_run_command(char * cmdStr) {
    char *cmd_name;
    int cmd_name_len;
    int argc = 0;
    char *argv[CONFIG_RZ_CLI_MAX_ARG];
    Rz_cmd_s *cmdp;

    /* empty string "" */
    if (!strlen(cmdStr)) { return _RUN_COMMAND_NONE; }

    /* add \n by itself */
    *(cmdStr + strlen(cmdStr)) = '\n';

    /* space string "    " */
    if(is_space_string(cmdStr)) { return _RUN_COMMAND_NONE; }
    
    argc = parse_command_string(cmdStr, argv);
    if (!argc) {
        return _RUN_COMMAND_NO_FOUND;    
    }

    /* find name */
    cmdp = find_cmd(argv[0], s_cmd_table_ptr);
    if (!cmdp) {
        return _RUN_COMMAND_NO_FOUND;    
    }

    /* exacute */
    cmdp->cmd(cmdp, argc, argv);

    return 0;
}

#if CONFIG_RZ_CLI_SELFTEST
#include <assert.h>
void testCmd(Rz_cmd_s *cmd, int argc, char *argv[]) {
    int i;

    printf("testCmd start\n");
    for (i=0; i<argc; i++) {
        printf("i=%d, argv[%d]=%s\n", i, i, argv[i]);
    }
    printf("testCmd end\n\n");
}

Rz_cmd_s cmd_table[] = {
   _ADD_CMD("g", testCmd, "this is help0"),
   _ADD_CMD("test1", testCmd, "this is help1"),
   _ADD_CMD("test2", testCmd, "this is help2"),
   _ADD_CMD("test3", testCmd, "this is help3"),
   _ADD_CMD("test4", testCmd, "this is help4"),
   _ADD_CMD("test5", testCmd, "this is help5"),
};

int main (int argc, char * argv[]) {
    char s1[] = "test1      1     2 34 a b c dd";
    char s2[] = "test5";
    char s3[] = "test6";
    char s4[] = "";
    char s5[] = "   ";
    char s6[] = "g 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 \
                   21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36   ";
    int rc;
    
    regist_cmd_table(cmd_table , sizeof(cmd_table));
    
    rc = cli_run_command(s1);
    assert(rc == _RUN_COMMAND_OK);
    rc = cli_run_command(s2);
    assert(rc == _RUN_COMMAND_OK);
    rc = cli_run_command(s3);
    assert(rc == _RUN_COMMAND_NO_FOUND);
    rc = cli_run_command(s4);
    assert(rc == _RUN_COMMAND_NONE);
    rc = cli_run_command(s5);
    assert(rc == _RUN_COMMAND_NONE);
    rc = cli_run_command(s6);
    assert(rc == _RUN_COMMAND_OK);
    
    return 0;
}
#endif //CONFIG_RZ_CLI_SELFTEST

