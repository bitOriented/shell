#include "shell.h"

// Shell loop
// Input Parsing
// Command execution 
// Handle Built-in commands exp. cd, pwd, echo, env, setenv, unsetenv, which, exit
// Execute external commands
// Manage environment variables
// Manage Path
// Error Handling

void display_help() {
    printf("Available commands:\n");
    printf("\tcd <directory>      - Change the current directory.\n");
    printf("\tpwd                 - Print the current working directory.\n");
    printf("\techo <text>         - Print the given text.\n");
    printf("\tenv                 - Display all environment variables.\n");
    printf("\tsetenv VAR=value    - Set an environment variable.\n");
    printf("\tunsetenv <variable> - Remove an environment variable.\n");
    printf("\twhich <command>     - Locate an executable in the system's PATH.\n");
    printf("\t.help               - Display this help message.\n");
    printf("\texit or quit        - Exit the shell.\n");
}


void cleanup_shell() {
    if (current_dir != NULL) {
        free(current_dir);
    }
}


// Built-ins: cd, pwd, echo, env, setenv, unsetenv, which, exit
// Binary: ls, cat.. we'll use executor
int shell_builts(char** args, char** env, char* current_dir)
{
    if (strcmp(args[0], "history") == 0) {
        print_history();
    }else if (strcmp(args[0], "cd") == 0) {
        return command_cd(args, current_dir);
    } else if (strcmp(args[0], "pwd") == 0) {
        return command_pwd();
    } else if (strcmp(args[0], "echo") == 0) {
        return command_echo(args, env);
    } else if (strcmp(args[0], "env") == 0) {
        return command_env(env);
    } else if (strcmp(args[0], "which") == 0) {
        return command_which(args, env);
    } else if (strcmp(args[0], ".help") == 0) {
        display_help();
        return 0;
    } else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        // Not a built-in command, execute as external command
        return executor(args, env);
    }
    return 0;
}

//Raw mode enabled method to process input character by character
void read_input(char* buffer) {
    int len = 0;
    buffer[0] = '\0';

    reset_history_index();
    enable_raw_mode();

    char c;
    while(read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n') {
            buffer[len] = '\0';
            printf("\n");
            break;
        } else if (c == 127 || c == '\b') {
            if (len > 0) {
                len--;
                buffer[len] = '\0';
                printf("\b \b");
                fflush(stdout);
            }
        } else if (c == 27) {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 1 &&
                read(STDIN_FILENO, &seq[1], 1) == 1) {
                    if (seq[0] == '[') {
                        if (seq[1] == 'A') {
                            const char* prevCmd = get_history_up();
                            if (prevCmd) {
                                for (int i = 0; i < len; i++) printf("\b \b");
                                len = snprintf(buffer, MAX_INPUT, "%s", prevCmd);
                                printf("%s", buffer);
                                fflush(stdout);
                            }
                        } else if (seq[1] == 'B') {
                            const char* nextCmd = get_history_down();
                            for (int i = 0; i < len; i++) printf("\b \b");
                            if (nextCmd) {
                                len = snprintf(buffer, MAX_INPUT, "%s", nextCmd);
                                printf("%s", buffer);
                                fflush(stdout);
                            } else {
                                len = 0;
                                buffer[0] = '\0';
                                fflush(stdout);
                            }
                        }
                    }
            }
        } else {
            if (len < MAX_INPUT - 1) {
                buffer[len++] = c;
                write(STDOUT_FILENO, &c, 1);
            }
        }
    }

    disable_raw_mode();
}

void shell_loop(char** env)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    current_dir = NULL;
    init_current_dir();

    printf("Type .help for a list of available commands.\n");

    while (1)
    {
        printf("shell:%s~$ ",current_dir);
        fflush(stdout);
        
        read_input(input);

        if (strlen(input) == 0) continue;

        add_to_history(input);


        if (strcmp(input, "exit") == 0 || strcmp(input,"quit") == 0) {
            break;
        }

        if (strcmp(input, "printenv") == 0) {
            print_shell_var();
            continue;
        }

        if (is_valid_assignment(input)) {
            handle_valid_assignment(input);
            continue;
        }

        char *expanded_input = expand_variables(input);

        if (!expanded_input) {
            perror("Memory error during expansion\n");
            continue;
        }

        char *token = strtok(expanded_input, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (!args[0]) {
            return;
        } else if (strcmp(args[0], "setenv") == 0) {
            env = command_setenv(args, env);
        } else if (strcmp(args[0], "unsetenv") == 0) {
            env = command_unsetenv(args, env);
        } else {
            shell_builts(args, env, current_dir);
        }
        
    }
    
    cleanup_shell();
} 

int main (int argc, char** argv, char** env)
{
    (void)argc;
    (void)argv;

    shell_loop(env);

    return 0;
}