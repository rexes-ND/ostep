#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"

volatile int counter = 0;
int loops;

void *worker(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);

    /*
        pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

        pthread_t *thread: pointer to a pthread_t structure
        const pthread_attr_t *attr: pointer to a pthread_attr_t structure
        void *(*start_routine) (void *): pointer to a function that takes a void pointer as an argument and returns a void pointer
        void *arg: pointer to the argument of the function
    */
    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("Final value   : %d\n", counter);
    return 0;
}
