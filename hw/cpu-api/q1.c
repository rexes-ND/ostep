#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  /*
    It works as if both parent and child have separate copy of x.
  */
  int x = 100;
  printf("before fork, x = %d\n (parent:%d)\n", x, (int)getpid());
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    ++x;
    printf("after fork, x = %d\n (child:%d)\n", x, (int)getpid());
  } else {
    ++x;
    printf("after fork, x = %d\n (parent:%d)\n", x, (int)getpid());
  }
  return 0;
}
