#ifndef COMMAND_H
#define COMMAND_H

#include"shell.h"

int command_cd(char** args,char* current_dir);
int command_pwd();
int command_echo(char** args,char** env);
int command_env(char** env);
int command_which(char** args,char** env);

char** command_setenv(char** args,char** env);
char** command_unsetenv(char** args,char** env);
#endif
