#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sighandler(int signo);

int main()
{
  printf("no forks occured yet\n");
  printf("pid: %d     parent pid: %d\n\n", getpid(), getppid());
  fork();
  printf("first fork just finished\n");
  printf("pid: %d     parent pid: %d\n\n", getpid(), getppid());
  fork();
  printf("second fork just finished\n");
  printf("pid: %d     parent pid: %d\n\n", getpid(), getppid());
  fork();
  printf("third fork just finished\n");
  printf("pid: %d     parent pid: %d\n\n", getpid(), getppid());
  printf("hello\n");
  return 0;
}
