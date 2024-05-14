#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  /*
    Used waitpid instead of wait
  */
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello\n");
  } else {
    // int wc = wait(NULL);
    waitpid(rc, NULL, 0);
    printf("goodbye\n");
  }
  return 0;
}
