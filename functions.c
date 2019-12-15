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
      int argIndex = 0;
      while(argv[argIndex])
      {
        printf("we have begun!! 888888888888888888888888888888888888888888888888888\n");
        printf("argv we are on right now: %ld\n", argv + argIndex);
        if(!strcmp(argv[argIndex], ">"))
        {
          printf("in here?\n");
          int fileDescriptor = open(argv[argIndex + 1], O_WRONLY, 0644);
          // printf("fileDescriptor: %d\n", fileDescriptor);
          // printf("argv[argIndex + 1] is: %s\n", argv[argIndex + 1]);
          printf("argv[argIndex - 1] is: %ld\n", argv[argIndex - 1]);
          printf("argv[argIndex] is: %ld\n", argv[argIndex]);
          printf("argv[argIndex + 1] is: %ld\n", argv[argIndex + 1]);
          int numberOfBytes = write(fileDescriptor, stdout, 10000);
          printf("numberOfBytes: %d\n", numberOfBytes);
          close(fileDescriptor);
          argv[argIndex] = ";";//this is faulty
          argv[argIndex + 1] = argv[argIndex - 1];
          printf("argv[argIndex + 1]: %s\n", argv[argIndex + 1]);
          printf("argv[argIndex]: %s\n", argv[argIndex]);
          printf("argv before cmdsep: %ld\n", argv);
          cmdsep(&argv);
          printf("argv after cmdsep: %ld\n", argv);
          execute(argv);
          printf("this thing?\n");
          exit(0);
        }
        else if(!strcmp(argv[argIndex], "<"))
        {
          printf("in here?\n");
          // int fileDescriptor = open(argv[argIndex + 1], O_RDONLY, 0644);
          // printf("fileDescriptor: %d\n", fileDescriptor);
          // printf("argv[argIndex + 1] is: %s\n", argv[argIndex + 1]);
          // int numberOfBytes = read(fileDescriptor, argv[argIndex - 1], 10000);
          // printf("numberOfBytes: %d\n", numberOfBytes);
          // close(fileDescriptor);
          // argv[argIndex] = NULL;//this is faulty
          // printf("argv[argIndex - 1]: %s\n", argv[argIndex - 1]);
          // printf("argv[argIndex]: %s\n", argv[argIndex]);
          // execvp(argv[argIndex - 1], argv);
          // exit(0);
        }
        argIndex ++;
        // if(!argv[argIndex])
        // {
        //   printf("will exit loop in the next iteration\n\n");
        // }
      }
      // printf("loop exited!\n");
      // printf("argIndex now: %d\n", argIndex);
      // printf("what is argv[0]?: %s\n", argv[0]);
      execvp(argv[0], argv);
      // int errorMessage = execvp(argv[0], argv);
      // printf("this is errorMessage: %d\n", execvp(argv[0], argv));
      // printf("does anything happen after this? \n");
      exit(0);
    }
    else
    {
      printf("creation of a child was unsuccessful\n");
    }
  }
}
