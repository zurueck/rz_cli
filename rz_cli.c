#include <stdio.h>
#include <string.h>
#include "rz_cli.h"
#include "rz_ctype.h"

static Rz_cmd_s *s_cmd_table_ptr;
static int s_cmd_table_num;

/* return 0 GG */
static int parse_command_string(char *cmdStr, char * argv[])
{
    int argc = 0;

    while (*cmdStr != '\n') {
        /*
         * skip white
         * check 9        10   11   12   13            32
         * check 0x09     0x0A 0x0B 0x0C 0x0D          0x20
         * check \t(tab)  \r   VT   FF   CR(\n)(enter) space
         */
        while (isspace(*cmdStr)) {
            cmdStr++;
        }

        argv[argc++] = cmdStr;
        cmdStr++;

        /* find arg end */
        while (!isspace(*cmdStr)) {
            cmdStr++;
        }

        /* check cmdStr end */
        if (*cmdStr == '\n') {
            /* add argv[] string end */
            *cmdStr = '\0';
            return argc;
        }

        //overload
        *cmdStr++ = '\0';
        if (argc > CONFIG_RZ_CLI_MAX_ARG)
            return argc;
    }
    return argc;
}

/* return 0 gg */
static Rz_cmd_s * find_cmd(char *name, Rz_cmd_s *table)
{
    Rz_cmd_s *cmdp = table;

    if (!cmdp->name)
        /* no command at all */
        return 0;

    while (strcmp(name, cmdp->name)) {
        if (cmdp >= table + s_cmd_table_num - 1) {
            /* out of range */
            return 0;
        }
        cmdp++;
    }

    return cmdp;
}

/* return 0 = ok, -1 = gg*/
static int is_space_string(char *s)
{
    while (isspace(*s)) {
        if (*s == '\n') {
            /* str = "     " */
            return -1;
        }
        s++;
    }

    return 0;
}

void regist_cmd_table(Rz_cmd_s * table, int size)
{
   s_cmd_table_ptr = table;
   s_cmd_table_num = size/sizeof(Rz_cmd_s);
}

int cli_run_command(char * cmdStr)
{
    int argc = 0;
    char *argv[CONFIG_RZ_CLI_MAX_ARG];
    Rz_cmd_s *cmdp;

    /* space string "    " */
    if (is_space_string(cmdStr))
        return _RUN_COMMAND_NONE;

    argc = parse_command_string(cmdStr, argv);
    if (!argc)
        return _RUN_COMMAND_NO_FOUND;

    /* find name */
    cmdp = find_cmd(argv[0], s_cmd_table_ptr);
    if (!cmdp)
        return _RUN_COMMAND_NO_FOUND;

    /* exacute */
    cmdp->cmd(cmdp, argc, argv);

    return 0;
}

int rz_add_cmd(){
static Rz_cmd_s *s_cmd_table_ptr;
    s_cmd_table_num++;


}
