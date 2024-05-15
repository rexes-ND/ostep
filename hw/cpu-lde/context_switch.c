#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  struct timeval start;
  struct timeval end;
  int pipe1[2];
  int pipe2[2];
  cpu_set_t set;
  char c;
  int nloops = 100000;

  CPU_ZERO(&set);
  CPU_SET(0, &set);

  if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
    perror("pipe failed");
    exit(1);
  }

  if (sched_setaffinity(getpid(), sizeof(set), &set)) {
    perror("sched_setaffinity failed");
    exit(1);
  }

  int rc1 = fork();
  if (rc1 < 0) {
    perror("fork failed");
    exit(1);
  } else if (rc1 == 0) {
    if (sched_setaffinity(getpid(), sizeof(set), &set)) {
      perror("sched_setaffinity failed");
      exit(1);
    }
    for (int i = 0; i < nloops; ++i) {
      write(pipe1[0], &c, 1);
      read(pipe2[1], &c, 1);
    }
    exit(0);
  }

  int rc2 = fork();
  if (rc2 < 0) {
    perror("fork failed");
    exit(1);
  } else if (rc2 == 0) {
    if (sched_setaffinity(getpid(), sizeof(set), &set)) {
      perror("sched_setaffinity failed");
      exit(1);
    }
    gettimeofday(&start, NULL);

    for (int i = 0; i < nloops; ++i) {
      read(pipe1[1], &c, 1);
      write(pipe2[0], &c, 1);
    }

    gettimeofday(&end, NULL);

    long total =
        (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
    printf("Total: %ld microseconds. Each loop took around %.3f microseconds\n",
           total, (float)total / nloops);

    exit(0);
  }

  wait(NULL);
  wait(NULL);

  return 0;
}