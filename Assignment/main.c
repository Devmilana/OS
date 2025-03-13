#include "buffer.h"
#include "reader.h"
#include "validators.h"
#include "printResults.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/********* Main Function *********/
int main(int argc, char *argv[])
{
    int i, j;
    int threadResult;
    ValidationBuffer buffer; /* Initialize buffer */
    pthread_t threads[NUM_THREADS]; /* Initialize thread array */
    ThreadArg args[NUM_THREADS];    /* Initialize thread arguments array */

    if (argc < 3)
    {
        fprintf(stderr, "\nIncorrect arguments provided! Correct usage is: %s <filename.txt> <delay_time>\n\n", argv[0]);
        return 1;
    }

    /* Initialize buffer variables */
    buffer.delay = atoi(argv[2]);
    buffer.threadsCompleted = 0;
    buffer.counter = 0;

    /* Read solution file */
    if (solutionReader(&buffer, argv[1]) != EXIT_SUCCESS)
    {
        return 1;
    }

    /* Initialize mutex and condition variables */
    pthread_mutex_init(&buffer.mutex, NULL);
    pthread_cond_init(&buffer.wakeup, NULL);

    /* Create threads for row, column, and subgrid validation based on thread ID */
    for (i = 0; i < NUM_THREADS; i++)
    {
        args[i].buffer = &buffer; /* Assign buffer to thread arguments */
        args[i].threadID = i + 1; /* Assign thread IDs */

        if (i == 3)
        {
            threadResult = pthread_create(&threads[i], NULL, columnValidator, &args[i]); /* For thread 4 (column validator) */
        }
        else
        {
            threadResult = pthread_create(&threads[i], NULL, rowSubgridValidator, &args[i]); /* For threads 1-3 (row and subgrid validator) */
        }
        if (threadResult != 0) /* Error handling for thread creation */
        {
            fprintf(stderr, "\nUnable to create thread %d\n\n", i+1);
            
            for (j = 0; j < i; j++) /* Destroy any previously created threads and resources */
            {
                pthread_join(threads[j], NULL);
            }
            
            pthread_mutex_destroy(&buffer.mutex);
            pthread_cond_destroy(&buffer.wakeup);
            
            return 1;
        }
    }

    /* Wait for all child threads to complete */
    pthread_mutex_lock(&buffer.mutex);
    while (buffer.threadsCompleted < NUM_THREADS)
    {
        pthread_cond_wait(&buffer.wakeup, &buffer.mutex); /* Wait for the signal from the last thread */
    }
    pthread_mutex_unlock(&buffer.mutex);

    /* Check and print the status of rows, columns, and subgrids */
    printResults(&buffer);

    /* Join threads */
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    /* Destroy mutex and condition variables */
    pthread_mutex_destroy(&buffer.mutex);
    pthread_cond_destroy(&buffer.wakeup);

    return 0;
}