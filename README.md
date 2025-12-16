# Custom C Shell

A lightweight, Unix-like shell implementation in C. This project mimics the core functionality of standard shells like Bash, providing a command-line interface for interacting with the operating system. It demonstrates fundamental systems programming concepts including process creation, file I/O, pipelines, and signal handling.

## Features

- **Command Execution**: Execute standard external commands (e.g., `ls`, `grep`, `vim`).
- **Built-in Commands**:
  - `cd <directory>`: Change the current working directory.
  - `pwd`: Print the current working directory.
  - `echo <text>`: Display a line of text.
  - `env`: List all environment variables.
  - `setenv <VAR=value>`: Set a new environment variable.
  - `unsetenv <VAR>`: Remove an environment variable.
  - `which <command>`: Locate a command in the system PATH.
  - `history`: Show command history.
  - `exit` / `quit`: Terminate the shell session.
- **I/O Redirection**:
  - Input Redirection (`<`): Read input from a file.
  - Output Redirection (`>`): Overwrite output to a file.
  - Append Redirection (`>>`): Append output to a file.
- **Pipelining**: Chain multiple commands together using the pipe operator (`|`).
- **Interactive Line Editing**:
  - **History Navigation**: Use Up/Down arrow keys to cycle through previous commands.
  - **Cursor Navigation**: Use Left/Right arrow keys to move the cursor within the input line.
  - **In-line Editing**: Insert text anywhere in the line and use Backspace to delete characters from the middle of the line.
- **Environment Variable Expansion**: Supports variables like `$HOME`, `$USER`, etc.

## Installation and execution

### Prerequisites
- GCC Compiler
- Make (optional, but recommended)
- Linux/Unix environment

### Build
To compile the project, simply run:
```bash
make
```
This will compile the source files and generate the `main` executable.

### Run
Start the shell by running:
```bash
./main
```

## Usage Examples

**Basic Commands:**
```bash
shell:~$ ls -l
shell:~$ pwd
shell:~$ echo "Hello, World!"
```

**Redirection:**
```bash
shell:~$ ls > files.txt
shell:~$ cat < files.txt
shell:~$ echo "New line" >> files.txt
```

**Piping:**
```bash
shell:~$ ls -l | grep "src"
shell:~$ cat file.txt | sort | uniq
```

**Environment Variables:**
```bash
shell:~$ echo $HOME
shell:~$ setenv MY_VAR=123
shell:~$ printenv
```

## Future Scope

The following features are planned for future development to enhance the shell's capabilities:

1.  **Tab Completion**: Auto-complete command names and file paths by pressing the Tab key.
2.  **Signal Handling**: Proper handling of signals like `SIGINT` (Ctrl+C) and `SIGTSTP` (Ctrl+Z) to interrupt or pause running processes without killing the shell itself.
3.  **Job Control**:
    - Support for background processes using `&`.
    - Commands to manage jobs: `jobs`, `fg`, `bg`.
4.  **Scripting Support**:
    - Execution of shell scripts (`./script.sh`).
    - Control structures: `if`/`else`, `for`/`while` loops.
    - Local shell variables and arithmetic operations.
5.  **Configuration File**: Support for a startup configuration file (e.g., `.myshellrc`) to persist aliases, environment variables, and custom prompt settings.
6.  **Syntax Highlighting**: Colorize commands, arguments, and valid/invalid paths as the user types.
7.  **Alias Support**: Allow users to define shortcuts for long commands (e.g., `alias ll='ls -l'`).
