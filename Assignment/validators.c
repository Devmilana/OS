#include "validators.h"
#include "buffer.h"
#include <unistd.h>
#include <stdio.h>

/********* Row and Subgrid Validator *********/
void* rowSubgridValidator(void* arg) 
{
    int i, j, k;
    int temp[SOL_SIZE]; /* Temporary array to store subgrid elements */
    int threadID, row, startingRow, subgrid, subgridIndex;

    ThreadArg *threadArg = (ThreadArg *)arg; 
    ValidationBuffer *buffer = threadArg->buffer;
    threadID = threadArg->threadID; /* Get the thread ID from the argument */

    startingRow = (threadID - 1) * 3;  /* Calculate the starting row based on thread ID */

    /* Validate rows */
    for (row = startingRow; row < startingRow + 3; row++) 
    {
        pthread_mutex_lock(&buffer->mutex);
        if (solutionValidator(buffer->Sol[row])) /* Check if row is valid */
        {
            buffer->Row[row] = 1;  /* Mark row as valid */
            buffer->counter++;  /* Increment the counter of valid sections */
        }
        pthread_mutex_unlock(&buffer->mutex);
        
        sleep(buffer->delay);
    }

    /* Validate subgrids */
    for (subgrid = 0; subgrid < 3; subgrid++) 
    {
        subgridIndex = subgrid + (threadID - 1) * 3; /* Calculate the subgrid index based on thread ID */

        /* Calculate indices for the subgrid */
        k = 0;

        for (i = 0; i < 3; i++) 
        {
            for (j = 0; j < 3; j++) 
            {
                temp[k++] = buffer->Sol[(subgridIndex / 3) * 3 + i][(subgridIndex % 3) * 3 + j]; /* Store the subgrid elements in temporary array */
            }
        }

        pthread_mutex_lock(&buffer->mutex);
        if (solutionValidator(temp)) /* Check if subgrid is valid */
        {
            buffer->Sub[subgridIndex] = 1;  /* Mark subgrid as valid */
            buffer->counter++;  /* Increment the counter of valid sections */
        }
        pthread_mutex_unlock(&buffer->mutex);
        
        sleep(buffer->delay);
    }

    pthread_mutex_lock(&buffer->mutex); 
    buffer->threadsCompleted++; /* Increment the number of threads completed */
    if (buffer->threadsCompleted == 4) /* Check if all threads have completed */
    {  
        pthread_cond_signal(&buffer->wakeup);  /* Signal main thread that all validations are complete */
        printf("\nThread ID-%d is the last thread\n\n", threadID);
    }
    pthread_mutex_unlock(&buffer->mutex);

    pthread_exit(NULL);
}

/********* Column Validator *********/
void* columnValidator(void* arg) 
{
    int i, j;
    int threadID;
    int temp[SOL_SIZE]; /* Temporary array to store column elements */

    ThreadArg *threadArg = (ThreadArg *)arg;
    ValidationBuffer *buffer = threadArg->buffer;
    threadID = threadArg->threadID; /* Get the thread ID from the argument */

    /* Validate columns */
    for (j = 0; j < SOL_SIZE; j++) 
    {
        for (i = 0; i < SOL_SIZE; i++) 
        {
            temp[i] = buffer->Sol[i][j]; /* Store the column elements in temporary array */
        }

        pthread_mutex_lock(&buffer->mutex);
        if (solutionValidator(temp)) /* Check if column is valid */
        {
            buffer->Col[j] = 1;  /* Mark column as valid */
            buffer->counter++;  /* Increment the counter of valid sections */
        }
        pthread_mutex_unlock(&buffer->mutex);
        sleep(buffer->delay);
    }

    pthread_mutex_lock(&buffer->mutex);
    buffer->threadsCompleted++; /* Increment the number of threads completed */
    if (buffer->threadsCompleted == 4) /* Check if all threads have completed */
    {  
        pthread_cond_signal(&buffer->wakeup);  /* Signal main thread that all validations are complete */
        printf("\nThread ID-%d is the last thread\n\n", threadID);
    }
    pthread_mutex_unlock(&buffer->mutex);

    pthread_exit(NULL);
}

/********* Solution Validator *********/
int solutionValidator(int array[SOL_SIZE]) 
{
    int i;
    int validatorArray[SOL_SIZE + 1] = {0};  /* Initialize temp array with zeros */
    
    for (i = 0; i < SOL_SIZE; i++) 
    {
        /* Check if the number is within the range 1-9 and has not been used */
        if (array[i] < 1 || array[i] > SOL_SIZE || validatorArray[array[i]]) 
        {
            return 0;
        }
        validatorArray[array[i]] = 1;  /* Mark index as seen */
    }

    return 1;
}