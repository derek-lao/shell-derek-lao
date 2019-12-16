#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void alterp(int * a, int b)
{
  * a = b;
}

void alter(int a, int b)
{
  alterp(&a, b);
}

int main()
{
  int x = 5;
  int y = 7;
  printf("x: %d\n", x);
  printf("y: %d\n", y);

  alter(x, 7);
  printf("x: %d\n", x);
  printf("y: %d\n", y);

  alterp(&x, 7);
  printf("x: %d\n", x);
  return 0;
}
