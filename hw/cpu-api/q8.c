#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipefd[2]; // read, write
  char buf[10];
  int pid1, pid2;

  if (pipe(pipefd) < 0) {
    perror("pipe failed");
    exit(1);
  }

  pid1 = fork();
  if (pid1 < 0) {
    perror("fork failed");
  } else if (pid1 == 0) {
    // child 1: write to pipe
    close(pipefd[0]);
    printf("(%d): writing hello to pipe\n", (int)getpid());
    write(pipefd[1], "hello", 6);
    exit(0);
  }
  pid2 = fork();
  if (pid2 < 0) {
    perror("fork failed");
  } else if (pid2 == 0) {
    // child 2: read from pipe
    close(pipefd[1]);
    read(pipefd[0], buf, 6);
    printf("(%d): received %s from pipe\n", (int)getpid(), buf);
    exit(0);
  }

  int wc1 = wait(NULL);
  int wc2 = wait(NULL);

  printf("(%d): waited following 2 processes (%d, %d)\n", (int)getpid(), wc1,
         wc2);

  return 0;
}
