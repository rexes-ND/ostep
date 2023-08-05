#ifndef __common_h__ // if not defined
#define __common_h__ // define it

#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

double GetTime()
{
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

void Spin(int howlong)
{
    /*
        Spin for howlong seconds
    */
    double t = GetTime();
    while ((GetTime() - t) < (double)howlong)
        ; // do nothing in loop
}

#endif // __common_h__
