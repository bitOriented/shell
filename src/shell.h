#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

#include"commands.h"
#include"executor.h"
#include"env.h"
#include"history.h"
#include"rawmode.h"


#define MAX_ARGS 64


extern char* current_dir; 
void init_current_dir(void);

char** parse_input(char* input);
void free_tokens(char **tokens);

int shell_builtin(char** args,char** env,char* current_dir);

#endif