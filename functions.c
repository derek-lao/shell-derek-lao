#include "functions.h"

//Return an array of pointers to each individual argument in the parameter string, that could be used for execvp()
char ** parse_args( char * line )//from what I read online, standards conventions is that the args ends with a null argument
{
  // char * arg = malloc(100 * sizeof(char *));
  int argIndex;
  char ** argArray = malloc(100 * sizeof(char **));//memory is allocated
  for(argIndex = 0 ; argIndex < 100 ; argIndex ++)
  {
    if(!line)
    {
      argArray[argIndex] = NULL;
      argIndex = 100;
      argArray[argIndex - 1] = NULL;
    }
    else
    {
      argArray[argIndex] = strsep(&line, " ");
    }
  }
  return argArray;
}

//Read a line at a time, parse the line to separate the command from its arguments.
//It should then fork and exec the command.
//The parent process should wait until the exec'd program exits and then it should read the next command.
// void execute(int argc, char * argv[])
// {
//   int running = 1;
//   while(running)
//   {
//     char * command = argv[0];
//     execvp(argv[0], argv);
//     running = 0;
//   }
// }

void execute(char * argv[])
{
  int * stupidStatus;
  // printf("hi\n");
  int child = fork();
  // printf("just forked, nothing else\n");
  // printf("pid: %d     parent pid: %d     child: %d\n", getpid(), getppid(), child);
  if(child > 0)
  {
    // printf("just forked, about to wait\n");
    // printf("while waiting:\npid: %d     parent pid: %d     child: %d\n", getpid(), getppid(), child);
    wait(stupidStatus);
    // printf("just finished waiting\n");
    // printf("pid: %d     parent pid: %d     child: %d\n", getpid(), getppid(), child);
  }
  else if(!child)
  {
    if(!strcmp(argv[0], "cd"))
    {
      if(!argv[1])
      {
        printf("Please gimme a directory!\n");
      }
      else
      {
        char * cwd;
        printf("%s\n", getcwd(cwd, 1000));
        chdir(argv[1]);
        printf("%s\n", getcwd(cwd, 1000));
      }
    }
    else
    {
      execvp(argv[0], argv);
    }
    exit(0);
  }
  else
  {
    printf("creation of a child was unsuccessful\n");
  }
  // running = 0;
}
