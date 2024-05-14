#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  /*
    Return value of wait is child PID.
    `wait` in child process fails since it doesn't have any child process.
   */
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("pid: %d (child)\n", (int)getpid());
    int wc = wait(NULL);
    printf("return value of wait in child: %d\n", wc);
    if (wc < 0) {
      // fprintf(stderr, "wait failed: %s\n", strerror(errno));
      perror("wait failed");
      exit(1);
    }
  } else {
    printf("pid: %d (parent)\n", (int)getpid());
    int wc = wait(NULL);
    printf("return value of wait in parent: %d\n", wc);
  }
  return 0;
}
