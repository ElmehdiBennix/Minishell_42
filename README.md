# Minishell

## Introduction
`Minishell` is a shell implementation that mimics the behavior of Bash. This project focuses on understanding processes, file descriptors, and shell operations.
- [More about the implementation here](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

## Features
- Custom command prompt.
- Command execution with absolute, relative, or `$PATH`-based search.
- Handling of built-in commands.
- Support for input/output redirections (`<`, `>`, `<<`, `>>`).
- Piping (`|`) to chain commands.
- Environment variable expansion (`$VAR`).
- Exit status variable (`$?`).
- Signal handling for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.
- Proper memory management to prevent leaks.

## Usage
### Compilation
To compile the project, use the provided `Makefile`:
```sh
make
```
This will generate the `Minishell` binary.

### Running the Shell
To start `minishell`, simply run:
```sh
./Minishell
```
Use standard shell commands or built-ins to interact with the shell.

### Built-in Commands
- `echo [-n] [text...]` – Print text to standard output.
- `cd [dir]` – Change directory.
- `pwd` – Print the current working directory.
- `export [VAR=value]` – Set an environment variable.
- `unset [VAR]` – Remove an environment variable.
- `env` – Display all environment variables.
- `exit [status]` – Exit the shell.

## Redirections & Pipes
- `<` – Redirect input from a file.
- `>` – Redirect output to a file.
- `>>` – Append output to a file.
- `<<` – Here-document (read input until a delimiter is found).
- `|` – Pipe output to another command.

## Error Handling
The program ensures proper error handling by:
- Preventing execution of non-existent commands.
- Handling invalid syntax.
- Checking for permission errors.
- Managing memory allocation failures.

## Makefile Targets
- `make`: Compile `minishell`.
- `make clean`: Remove object files.
- `make fclean`: Remove executables and object files.
- `make re`: Recompile everything.
