# Rz_cli

## Introduction
Rz_cli is a simple command line interface(CLI) for bare metal MCU system. 

## Dependancy
* stdio.h
* string.h

## How to use
1. set "config" in header file
2. create a command table array
3. add command name, callback function name into table
4. create callback function body for the command
5. register table by  
   `regist_cmd_table()`
6. execute your command string by  
   `cli_run_command()`

* See example in test.c

## API
```
void regist_cmd_table(Rz_cmd_s *table, int size);
int cli_run_command(char *cmdStr);
```

## Todo
1. add API add_cmd()
2. support help message
