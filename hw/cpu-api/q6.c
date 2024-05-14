#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  /*
    I think if you have multiple child processes,
    you can use waitpid to specify which child process to wait.
   */
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("pid: %d (child)\n", (int)getpid());
    // int wc = wait(NULL);
    int wc = waitpid(-1, NULL, 0);
    printf("return value of wait in child: %d\n", wc);
    if (wc < 0) {
      fprintf(stderr, "wait failed: %s\n", strerror(errno));
    }
  } else {
    printf("pid: %d (parent)\n", (int)getpid());
    // int wc = wait(NULL);
    int wc = waitpid(-1, NULL, 0);
    printf("return value of wait in parent: %d\n", wc);
  }
  return 0;
}
