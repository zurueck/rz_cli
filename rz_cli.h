#ifndef RZ_CLI_H
#define RZ_CLI_H

//===== config =====
#define CONFIG_RZ_CLI_SELFTEST      1
#define CONFIG_RZ_CLI_MAX_ARG       32
//===== end config =====

#define _RUN_COMMAND_OK       0
#define _RUN_COMMAND_NONE     -1
#define _RUN_COMMAND_NO_FOUND -2

#define _ADD_CMD(n, c, h) \
    { \
        .name = n, \
        .cmd = c, \
        .helpMsg = h, \
    }

struct rz_cmd_s {
    const char *name;
    void  (*cmd)(struct rz_cmd_s *, int, char * []);
    const char *helpMsg; 
};
typedef struct rz_cmd_s Rz_cmd_s;

void regist_cmd_table(Rz_cmd_s *table, int size);
int cli_run_command(char *cmdStr);

#endif //RZ_CLI_H
