#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv)
{
    // sizeof(int) = 4
    int *p = malloc(sizeof(int)); // a1
    assert(p != NULL);
    // getpid returns the process ID of the calling process
    printf("(%d) address pointed to by p: %p\n", getpid(), p); // Hexadecimal representation of the memory address that p points to // a2
    *p = 0;                                                    // a3
    while (1)
    {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p); // a4
    }
}
