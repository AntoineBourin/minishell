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
- wait --> L'appel système wait() suspend l'exécution du processus appelant jusqu'à ce que l'un de ses fils se termine
- waitpid --> like wait but you select the PID
- wait3 --> 
- wait4 --> 
- signal --> a lot of signal
- kill --> (int kill(pid_t pid, int sig);) : L'appel système kill() peut être utilisé pour envoyer n'importe quel signal à n'importe quel processus ou groupe de processus.

- exit --> LOL JUST EXIT
- getcwd --> (char *getcwd(char *buf, size_t size);) : La fonction getcwd() copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par buf, qui est de longueur size.

- chdir --> (int chdir(const char *path);) : chdir() remplace le répertoire de travail courant du processus appelant par celui indiqué dans le chemin path.

- stat --> (int stat(const char *path, struct stat *buf);): Ces fonctions renvoient des informations à propos d'un fichier. Aucune permission n'est nécessaire sur le fichier lui-même, mais vous devez --- dans le cas de stat() et lstat() --- avoir la permission d'exécution (parcours) pour tous les répertoires de path qui mènent au fichier.
- lstat --> (int lstat(const char *path, struct stat *buf);) : 
- fstat --> (int fstat(int fd, struct stat *buf);) : 

- execve --> (int execve(const char *fichier, char *const argv[],char *const envp[]);  ) execve() exécute le programme correspondant au fichier. Celui-ci doit être un exécutable binaire ou bien un script

- dup --> ( int dup(int oldfd);    ) : dup() et dup2() créent une copie du descripteur de fichier oldfd.
- dup2 --> (    int dup2(int oldfd, int newfd);     ) 

- pipe --> (    int pipe(int pipefd[2]);    ) : pipe() crée un tube, un canal unidirectionnel de données qui peut être utilisé pour la communication entre processus

- opendir --> La fonction opendir() ouvre un flux répertoire correspondant au répertoire name, et renvoie un pointeur sur ce flux

- readdir -->La fonction readdir() renvoie un pointeur sur une structure dirent représentant l'entrée suivante du flux répertoire pointé par dir. Elle renvoie NULL à la fin du répertoire, ou en cas d'erreur.

- closedir --> La fonction closedir() ferme le flux de répertoire associé à dir. Après cette invocation, le descripteur dir du flux de répertoire n'est plus disponible.  

- strerror --> La fonction strerror() renvoie une chaîne décrivant le code d'erreur passé en argument errnum

- errno --> Value of errno change when an error appeard 