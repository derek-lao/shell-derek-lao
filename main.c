#include "functions.h"

static void sighandler(int signo);

// int main()
// {
//   int * stupidStatus;
//   printf("no forks occured yet\n");
//   printf("pid: %d     parent pid: %d\n\n", getpid(), getppid());
//   int a = fork();
//   wait(stupidStatus);
//   printf("first fork just finished\n");
//   printf("pid: %d     parent pid: %d     fork(): %d     wait stupidStatus: %d\n\n", getpid(), getppid(), a, stupidStatus);
//   int b = fork();
//   wait(stupidStatus);
//   printf("second fork just finished\n");
//   printf("pid: %d     parent pid: %d     fork(): %d     wait stupidStatus: %d\n\n", getpid(), getppid(), b, stupidStatus);
//   int c = fork();
//   wait(stupidStatus);
//   printf("third fork just finished\n");
//   printf("pid: %d     parent pid: %d     fork(): %d     wait stupidStatus: %d\n\n", getpid(), getppid(), c, stupidStatus);
//   return 0;
// }

// int main()
// {
//   printf("running...\n");
//   printf("testing parse_args(line1) for line1 = \"ls -a -l\"\n");
//   char line[100];
//   int running = 1;
//   while(running)
//   {
//     if(fgets(line, sizeof(line), stdin))
//     {
//       int argIndex = 0;
//       char ** args = parse_args(line);//memory already allocated
//       while(argIndex < 5)
//       {
//         printf("args[%d] is %s\n", argIndex, args[argIndex]);
//         argIndex ++;
//       }
//       execute(args);
//     }
//     else
//     {
//       printf("Please enter a command\n");
//     }
//   }
//   return 0;
// }

int main()
{
  printf("running...\n");
  char * cwd;
  // printf("seg fault here??\n");
  // getcwd(cwd, 100);
  // printf("%s\n", getcwd(cwd, 100));
  while(1)
  {
    printf("%s\n", getcwd(cwd, 1000));
    char line[100];
    fgets(line, sizeof(line), stdin);
    char * enemy = strchr(line, (char)'\n');
    *enemy = '\0';
    char ** args = parse_args(line);
    if(!strcmp(args[0], "exit"))
    {
      break;
    }
    execute(args);
  }
  return 0;
}
