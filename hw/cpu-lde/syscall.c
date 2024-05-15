#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
  struct timeval start;
  struct timeval end;
  char c;
  int nloops = 100000;

  gettimeofday(&start, NULL);

  for (int i = 0; i < nloops; ++i) {
    read(0, &c, 0);
  }

  gettimeofday(&end, NULL);

  long total =
      (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
  printf(
      "Total: %ld microseconds. Each syscall took around %.3f microseconds\n",
      total, (float)total / nloops);

  return 0;
}