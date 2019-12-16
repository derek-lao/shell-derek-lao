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
  printf("execute called\n");
  int * stupidStatus;
  int argIndex = 0;
  int isRedirect = 0;
  while(argv[argIndex])
  {
    if(!strcmp(argv[argIndex], ">") || !strcmp(argv[argIndex], "<"))
    {
      isRedirect = 1;
      redirectRun(&argv);
      break;
    }
    argIndex ++;
  }

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

  else if(!isRedirect);
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
      exit(0);
    }
  }
}

void redirectRun(char *** argv)
{
  printf("redirectRun called\n");
  int argIndex = 0;
  int redirectCounter = 0;
  int inputRedirectIndex = 1000;
  int outputRedirectIndex = 1000;
  //loop to count the redirects
  while((*argv)[argIndex])
  {
    printf("in while loop that alters inputRedirectIndex and outputRedirectIndex\n");
    if(!strcmp((*argv)[argIndex], "<"))
    {
      inputRedirectIndex = argIndex;
      redirectCounter ++;
    }
    if(!strcmp((*argv)[argIndex], ">"))
    {
      outputRedirectIndex = argIndex;
      redirectCounter ++;
    }
    argIndex ++;
  }
  printf("exited aforementioned while loop\n");

  if(redirectCounter == 1)
  {
    printf("inside check for redirectCounter = 1\n");
    if(inputRedirectIndex < 100)
    {
      printf("inside check for inputRedirectIndex < 100 while redirectCounter = 1\n");
      int fileDescriptor = open((*argv)[inputRedirectIndex + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
      if(fileDescriptor < 0)
      {
        // fileDescriptor = open(argv[inputRedirectIndex + 1], O_RDWR);
        printf("-bash: %s: No such file or directory\n\n", (*argv)[inputRedirectIndex + 1]);
        exit(0);
      }
      int io = STDIN_FILENO;
      int temp = io;//makes temp STDIN_FILENO;
      dup2(fileDescriptor, io);
      (*argv)[inputRedirectIndex] = NULL;
      execute(*argv);
      close(fileDescriptor);
      dup2(temp, io);//make input output back into STDIN_FILENO
      *argv = (*argv) + inputRedirectIndex + 1;
    }
    else if(outputRedirectIndex < 100)
    {
      printf("inside check for outputRedirectIndex < 100 while redirectCounter = 1\n");
      int fileDescriptor = open((*argv)[outputRedirectIndex + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
      if(fileDescriptor < 0)
      {
        fileDescriptor = open((*argv)[outputRedirectIndex + 1], O_RDWR);
      }
      int io = STDOUT_FILENO;
      int temp = io;//makes temp STDOUT_FILENO;
      dup2(fileDescriptor, io);
      (*argv)[outputRedirectIndex] = NULL;
      execute(*argv);
      printf("1\n");
      close(fileDescriptor);
      dup2(temp, io);//make input output back into STDOUT_FILENO
      *argv = (*argv) + outputRedirectIndex + 1;
    }
  }

  //multi-redirect
  else if(redirectCounter == 2)
  {
    printf("inside check for redirectCounter = 1\n");
    int fileDescriptor1 = open((*argv)[inputRedirectIndex + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
    if(fileDescriptor1 < 0)
    {
      // fileDescriptor = open(argv[inputRedirectIndex + 1], O_RDWR);
      printf("-bash: %s: No such file or directory\n\n", (*argv)[inputRedirectIndex + 1]);
      exit(0);
    }
    int fileDescriptor2 = open((*argv)[outputRedirectIndex + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
    if(fileDescriptor2 < 0)
    {
      fileDescriptor2 = open((*argv)[outputRedirectIndex + 1], O_RDWR);
    }
    int io1 = STDOUT_FILENO;
    int io2 = STDIN_FILENO;
    int temp1 = io1;
    int temp2 = io2;
    (*argv)[inputRedirectIndex] = NULL;
    (*argv)[outputRedirectIndex] = NULL;
    execute(*argv);
    close(fileDescriptor1);
    close(fileDescriptor2);
    dup2(fileDescriptor1, io1);
    dup2(fileDescriptor2, io2);
    *argv = (*argv) + outputRedirectIndex + 1;
  }

  else if(redirectCounter == 3)
  {
    printf("Do not perform redirects more than twice\n");
    exit(0);
  }

}
