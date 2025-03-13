#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>

#define SOL_SIZE 9 /* Size of the Sudoku solution grid (9x9 grid) */
#define NUM_THREADS 4 /* Number of threads (3 for row and subgrid validation, 1 for column validation) */
#define MAX_VALID_TOTAL (SOL_SIZE * 3) /* Maximum valid total for the Sudoku solution grid (27 valid sections) */

/* Main validation buffer structure */
typedef struct 
{
    int Sol[SOL_SIZE][SOL_SIZE];
    int Row[SOL_SIZE];
    int Col[SOL_SIZE];
    int Sub[SOL_SIZE];
    
    int threadsCompleted;
    int counter;
    int delay;
    
    pthread_mutex_t mutex;
    pthread_cond_t wakeup;
    
} ValidationBuffer;

/* Separate structure for passing arguments to thread functions */
typedef struct 
{
    ValidationBuffer *buffer; /* Pointer to validation buffer */
    int threadID;             
} ThreadArg;

#endif