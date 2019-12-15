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
    char ** temp1 = args;
    char ** temp2 = commands;
    while(args[0])
    {
      commands = cmdsep(&args);
      char thing[1];
      scanf(thing, "%s", thing);
      //this line is BS to allow the redirection code to work
      if(!strcmp(commands[0], "exit"))
      {
        break;
      }
      execute(commands);

      // printf("done executing!\n");
    }
    if(*commands && !strcmp(commands[0], "exit"))
    {
      break;
    }
    free(temp1);
    free(temp2);
    printf("\n");
  }
  return 0;
}
