# Minishell project

Minishell is a 42 project where we have to reproduce some basic shell commands with C langage. 
This project must be accomplished with 2 students.

### Commands to reproduce 

echo with option '-n', cd without '-', pwd without options, export without options, unset without options, env without options, exit without options. Redirections (>) & Pipes (|) must works in program.

### Program execution

A Makefile is written inside the project to compile library (libft) and program. `make all` compile all code in project & give you access to `minishell` binary file.

### Native functions allowed

- malloc --> Reserve memory on heap
- free --> Free memory 
- write --> Write data on fildes
- open --> Open file with file descriptor
- read --> Read data on file descriptor 
- close --> Close file opened before 
- fork --> 
- wait --> 
- waitpid -->
- wait3 --> 
- wait4 --> 
- signal --> 
- kill --> 
- exit --> 
- getcwd --> 
- chdir --> 
- stat --> 
- lstat --> 
- fstat --> 
- execve --> 
- dup --> 
- dup2 --> 
- pipe --> 
- opendir -->
- readdir -->
- closedir --> 
- strerror -->
- errno -->