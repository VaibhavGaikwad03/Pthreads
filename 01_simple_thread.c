/* A simple program using Pthreads */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

static void *thread_func(void *arg)
{
    char *s = (char *)arg;

    printf("%s", s);

    return (void *)strlen(s);
}

int main(int argc, char *argv[])
{
    int s;
    void *result;
    pthread_t t1;

    s = pthread_create(&t1, NULL, thread_func, "Hello, World!\n"); // Create a thread
    if (s != 0)
        perror("pthread_create");

    printf("Message from main()\n");
    // Return value from the thread_func() is 'result'
    s = pthread_join(t1, &result); // Main thread waits for the thread to terminate
    if (s != 0)
        perror("pthread_join");

    printf("Thread returned %ld\n", (long)result);

    exit(EXIT_SUCCESS);
}