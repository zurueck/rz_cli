#ifndef RZ_CLI_H
#define RZ_CLI_H

/* ========== config ========== */
/* maximum number of argument for one command */
#define CONFIG_RZ_CLI_MAX_ARG       32

/* ========== end config ====== */

#define _RUN_COMMAND_OK       (0)
#define _RUN_COMMAND_NONE     (-1)
#define _RUN_COMMAND_NO_FOUND (-2)

#define _ADD_CMD(n, c, h) \
    { \
        .name = n, \
        .cmd = c, \
        .helpMsg = h, \
    }

/**
 * Structure of a single command
 */
typedef struct rz_cmd_s{
    const char *name;
    void  (*cmd)(struct rz_cmd_s *, int, char * []);
    const char *helpMsg;
}Rz_cmd_s;

/**
 * Regist your command table to rz_cli
 *
 * @param [in] table command table array
 * @param [in] size  length of table(byte)
 */
void regist_cmd_table(Rz_cmd_s *table, int size);

/**
 * Input a command string and run the command
 *
 * @param [in] cmdStr   It should is ended with \\ n
 * @return 0 ok \n
 *         -1 nothing happend \n
 *         -2 no this command
 */
int cli_run_command(char *cmdStr);

#endif //RZ_CLI_H
