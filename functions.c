#include "functions.h"

//Return an array of pointers to each individual argument in the parameter string, that could be used for execvp()
char ** parse_args( char * line )//from what I read online, standards conventions is that the args ends with a null argument
{
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
    if(!strcmp(";", (* arg)[argIndex]))
    {
      (* arg)[argIndex] = NULL;
      char ** temp = (* arg);
      * arg = (*arg) + argIndex + 1;
      return temp;
    }
    // else if(!strncmp(";;""))
    else
    {
      argIndex ++;
    }
  }
  char ** temp = (* arg);
  * arg = (*arg) + argIndex;
  return temp;
}

void execute(char * argv[])
{
  int * stupidStatus;
  if(argv && !strcmp(argv[0], "cd"))
  {
    if(!argv[1])
    {
      printf("Please enter a specified directory!\n");
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

void redirect(char * argv[])
{
  int argIndex = 0;
  int redirectCounter = 0;
  while(argv[argIndex])
  {
    if(!strcmp(argv[argIndex], "<"))
    {
      redirectCounter ++;
    }
    if(!strcmp(argv[argIndex], ">"))
    {
      redirectCounter ++;
    }
    argIndex ++;
  }
  argIndex = 0;
  while(argv[argIndex])
  {
    if(!strcmp(argv[argIndex], "<"))
    {
      redirectCounter ++;
      int fileDescriptor = open(argv[argIndex + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
      if(fileDescriptor < 0)
      {
        fileDescriptor = open(argv[argIndex + 1], O_RDWR);
      }
      int io = STDIN_FILENO;
      int temp = io;//makes temp STDIN_FILENO;
      dup2(fileDescriptor, io);
      close(fileDescriptor);
      argv[argIndex] = ";";
      argv[argIndex + 1] = argv[argIndex - 1];
      cmdsep(&argv);
      execute(argv);
      dup2(temp, io);//make input output back into STDIN_FILENO
      exit(0);
    }
    if(!strcmp(argv[argIndex], ">"))
    {
      redirectCounter ++;
      int fileDescriptor = open(argv[argIndex + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
      if(fileDescriptor < 0)
      {
        fileDescriptor = open(argv[argIndex + 1], O_RDWR);
      }
      int io = STDOUT_FILENO;
      int temp = io;//makes temp STDOUT_FILENO;
      dup2(fileDescriptor, io);
      close(fileDescriptor);
      argv[argIndex] = ";";//this is faulty
      argv[argIndex + 1] = argv[argIndex - 1];
      cmdsep(&argv);
      execute(argv);
      dup2(temp, io);//make input output back into STDOUT_FILENO
      exit(0);
    }
    argIndex ++;
  }
}
