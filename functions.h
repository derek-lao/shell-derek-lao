#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

char ** parse_args( char * line );//Return an array of pointers to each individual argument in the parameter string, that could be used for execvp()

char ** cmdsep(char *** arg);

void execute(char * argv[]);
//The parent process should wait until the exec'd program exits and then it should read the next command.

void redirect(char *** argv);
