/* Creating a thread with the detached attribute */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void func()
{
    printf("Hello from thread...\n");
}

int main(void)
{
    pthread_t thread;
    pthread_attr_t attr;
    int s;

    s = pthread_attr_init(&attr); /* Assigns default values */
    if (s != 0)
        perror("pthread_attr_init");

    s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (s != 0)
        perror("pthread_attr_setdetachstate");

    s = pthread_create(&thread, &attr, func, 0);
    if (s != 0)
        perror("pthread_create");

    s = pthread_attr_destroy(&attr); /* No longer needed */
    if (s != 0)
        perror("pthread_attr_destroy");

    return 0;
}