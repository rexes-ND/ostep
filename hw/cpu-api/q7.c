#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  /*
    The child printf doesn't output anything.
    However, parent printf works.
  */
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  if (rc == 0) {
    close(STDOUT_FILENO);
    printf("child\n");
  } else {
    wait(NULL);
    printf("parent\n");
  }
  return 0;
}