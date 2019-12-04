#include "function.h"

char ** parse_args( char * line )//from what I read online, standards conventions is that the args ends with a null argument
{
  // char * arg = malloc(100 * sizeof(char *));
  int argIndex;
  char ** argArray = malloc(6 * sizeof(char **));//memory is allocated
  for(argIndex = 0 ; argIndex < 5 ; argIndex ++)
  {
    if(!line)
    {
      argArray[argIndex] = NULL;
      argIndex = 5;
      argArray[argIndex] = NULL;
    }
    else
    {
      argArray[argIndex] = strsep(&line, " ");
    }
  }
  return argArray;
}
