#include "functions.h"

static void sighandler(int signo);

// int main()
// {
//
//   return 0;
// }

int main()
{
  printf("running...\n");
  char cwd[1000];
  while(1)
  {
    printf("%s\n", getcwd(cwd, 1000));
    char line[4000];
    fgets(line, sizeof(line), stdin);
    char * lastCharAfterLastArgument = strchr(line, (char)'\n');
    *lastCharAfterLastArgument = '\0';
    char ** args = parse_args(line);
    char ** commands = malloc(100 * sizeof(char *));
    while(args[0])
    {
      // printf("the argument is: %s\n", *args);
      // printf("args: %lu     commands: %lu\n", args, commands);
      commands = cmdsep(&args);
      // printf("commands[0] in the while loop is: %lu\n", commands[0]);
      if(!strcmp(commands[0], "exit"))
      {
        break;
      }
      execute(commands);
    }
    // printf("commands[0] is: %lu\n", commands[0]);
    if(*commands && !strcmp(commands[0], "exit"))
    {
      break;
    }
  }
  return 0;
}
