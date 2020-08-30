# Rz_cli

## Introduction
Rz_cli is a simle command line interface(CLI) for bare metal MCU system. Porting will be very easy.

## Dependancy
C standard library

* stdio.h
* string.h

## How to use
1. set "config" in header file
2. create a command table
3. add command name, callback function name into table
4. create callback function body for the command
5. register table to rz_cli by
`regist_cmd_table()`
6. execute your command string by 
 `cli_run_command()`

* See example in test.c

## API
```
_ADD_CMD(n, c, h)
void regist_cmd_table(Rz_cmd_s *table, int size);
int cli_run_command(char *cmdStr);
```


## Todo
1. seperate test function to test.c
2. test string needs to be correct(end by \n)
   after that, debug cli_run_command() 
3. add doxygen style comment
5. more readme
