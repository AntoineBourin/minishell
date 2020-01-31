# Minishell project

Minishell is a 42 project where we have to reproduce some basic shell commands with C langage. 
This project must be accomplished with 2 students.

### Commands to reproduce 

echo with option '-n', cd without '-', pwd without options, export without options, unset without options, env without options, exit without options. Redirections (>) & Pipes (|) must works in program.

### Featuring creation process

- Create new feature branch with command `git checkout -b feat/feature-name`
- When your feature is ready, push code on your branch
- Compare branches & create a pull request `https://github.com/AntoineBourin/minishell/compare?expand=1` to master branch
- When your pull request is merged, you can go back to master branch `git checkout master` and get last sources `git pull origin master`

### Retrieve master sources on your current branch

- `git fetch origin -p` allow you to retrieve sources
- `git rebase origin/master` apply sources and rebase master branch to your current branch
- If rebase command indicate that there is some conflicts, fix them and type `git rebase --continue`

### Program execution

A Makefile is written inside the project to compile library (libft) and program. `make all` compile all code in project & give you access to `minishell` binary file.

### Native functions allowed

- malloc --> Reserve memory on heap
- free --> Free memory 
- write --> Write data on fildes
- open --> Open file with file descriptor
- read --> Read data on file descriptor 
- close --> Close file opened before 
- fork --> Create child process which runs concurrently with the process that makes the fork() `https://www.geeksforgeeks.org/fork-system-call/`
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