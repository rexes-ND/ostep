#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

double GetTime() {
  struct timeval t;
  /*
      t.tv_sec: seconds
      t.tv_usec: microseconds

      after UNIX epoch
  */
  int rc = gettimeofday(&t, NULL);
  assert(rc == 0);
  return (double)t.tv_sec + (double)t.tv_usec / 1e6;
}

void Spin(int howlong) {
  /*
      Spin for howlong seconds
  */
  double t = GetTime();
  while ((GetTime() - t) < (double)howlong)
    ; // do nothing in loop
}
