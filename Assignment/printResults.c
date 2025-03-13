#include "printResults.h"
#include "buffer.h"
#include <stdbool.h>
#include <stdio.h>

/********* Print validation result statements *********/
void printResults(ValidationBuffer *buffer) 
{
    bool valid;
    int i, j;
    int length, errors;
    int startingRow, startingSubgrid;
    char details[256] = {0}; /* Buffer to store the validation result */

    for (i = 0; i < NUM_THREADS; i++) 
    {
        valid = true; /* Flag to check if the solution is valid */
        length = 0; /* Length of the result string */
        errors = 0; /* Count of errors */

        if (i < 3) 
        {   
            startingRow = i * 3; /* Starting row for each row thread */
            for (j = startingRow; j < startingRow + 3; j++) 
            {
                /* Check if the row is valid (1 for valid, 0 for invalid) */
                if (!buffer->Row[j]) 
                {
                    valid = false;
                    length += sprintf(details + length, "row %d, ", j + 1); /* Append the invalid row number to the details string */
                    errors++; /* Increment the error count */
                }
            }
            startingSubgrid = i * 3; /* Starting subgrid for each subgrid thread */
            for (j = startingSubgrid; j < startingSubgrid + 3; j++) 
            {
                /* Check if the subgrid is valid (1 for valid, 0 for invalid) */
                if (!buffer->Sub[j]) 
                {
                    valid = false;
                    length += sprintf(details + length, "sub-grid %d, ", j + 1); /* Append the invalid subgrid number to the details string */
                    errors++; /* Increment the error count */
                }
            }
            if (valid) 
            {
                printf("Thread ID-%d: valid\n", i + 1);
            } 
            else
            { 
                details[length - 2] = '\0'; /* Remove the last comma and space */
                if (errors > 1) 
                {
                    printf("Thread ID-%d: %s are invalid\n", i + 1, details); /* Print invalid rows and subgrids for each thread */
                } 
                else 
                {
                    printf("Thread ID-%d: %s is invalid\n", i + 1, details); /* Print invalid row and subgrid for each thread */
                }
            }
        } 
        else 
        {
            for (j = 0; j < SOL_SIZE; j++) 
            {
                /* Check if the column is valid (1 for valid, 0 for invalid) */
                if (!buffer->Col[j]) 
                {
                    valid = false;
                    length += sprintf(details + length, "column %d, ", j + 1); /* Append the invalid column number to the details string */
                    errors++; /* Increment the error count */
                }
            }
            if (valid) 
            {
                printf("Thread ID-4: valid\n");
            } 
            else
            {
                details[length - 2] = '\0'; /* Remove the last comma and space */
                if (errors > 1) 
                {
                    printf("Thread ID-4: %s are invalid\n", details); /* Print invalid columns for the column thread */
                } 
                else 
                {
                    printf("Thread ID-4: %s is invalid\n", details); /* Print invalid column for the column thread */
                }
            }
        }
    }
    /* Check if the total number of valid sections is equal to the maximum valid total */
    if (buffer->counter == MAX_VALID_TOTAL) 
    {
        printf("\nThere are in total %d valid rows, columns, and subgrids, and the solution is valid\n\n", buffer->counter); /* Valid solution message */
    } 
    else 
    {
        printf("\nThere are in total %d valid rows, columns, and subgrids, and the solution is invalid\n\n", buffer->counter); /* Invalid solution message */
    }
}