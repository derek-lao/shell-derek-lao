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

char ** cmdsep(char *** arg)
{
  int argIndex = 0;
  while((* arg)[argIndex])
  {
    // printf("argument: %lu\n", (* arg) + argIndex);
    if(!strcmp(";", (* arg)[argIndex]))
    {
      // printf("argument inside if statement: %lu\n", (* arg) + argIndex);
      (* arg)[argIndex] = NULL;
      char ** temp = (* arg);
      * arg = (*arg) + argIndex + 1;
      // printf("what we are going to return: %lu\n", temp);
      // printf("what the new arg is: %lu\n", * arg);
      return temp;
    }
    else
    {
      argIndex ++;
    }
  }
  // printf("exited because argument is null\n");
  char ** temp = (* arg);
  * arg = (*arg) + argIndex + 1;
  return temp;
}

void execute(char * argv[])
{
  int * stupidStatus;
  if(argv && !strcmp(argv[0], "cd"))
  {
    if(!argv[1])
    {
      printf("Please cd to a specified directory!\n");
    }
    else
    {
      char cwd[1000];
      chdir(argv[1]);
    }
  }
  else
  {
    int child = fork();
    if(child > 0)
    {
      wait(stupidStatus);
    }
    else if(!child)
    {
      execvp(argv[0], argv);
      exit(0);
    }
    else
    {
      printf("creation of a child was unsuccessful\n");
    }
  }
}
