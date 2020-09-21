#include <stdio.h>
#include <assert.h>
#include "rz_cli.h"

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
    char s1[] = "test1      1     2 34 a b c dd\n";
    char s2[] = "test5\n";
    char s3[] = "test6\n";
    char s4[] = "\n";
    char s5[] = "   \n";
    char s6[] = "g 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 \
                   21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36   \n";
    int rc;

    regist_cmd_table(cmd_table , sizeof(cmd_table));

    //normal cmd
    rc = cli_run_command(s1);
    assert(rc == _RUN_COMMAND_OK);

    //normal cmd
    rc = cli_run_command(s2);
    assert(rc == _RUN_COMMAND_OK);

    //no cmd
    rc = cli_run_command(s3);
    assert(rc == _RUN_COMMAND_NO_FOUND);

    //empty string
    rc = cli_run_command(s4);
    assert(rc == _RUN_COMMAND_NONE);

    rc = cli_run_command(s5);
    assert(rc == _RUN_COMMAND_NONE);

    //too many arg
    rc = cli_run_command(s6);
    assert(rc == _RUN_COMMAND_OK);

    printf("if you see this line, it means test done with no error\n");

    return 0;
}
