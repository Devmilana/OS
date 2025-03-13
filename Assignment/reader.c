#include "reader.h"
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>

/********* Sudoku Solution File Reader *********/
int solutionReader(ValidationBuffer* buffer, const char* filename)
{
    int i;
    int numRows = 0; /* Counter to keep track of the number of rows read */
    char line[1024]; /* Buffer to store each line of the file */
    char tail[100]; /* Buffer to check for unwanted characters beyond the expected integers */
    int inputArray[SOL_SIZE]; /* Temporary array to store the integers read from the file */

    FILE* file = fopen(filename, "r"); 
    if (!file) 
    {
        fprintf(stderr, "\nError opening file!\n\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) && numRows < SOL_SIZE) 
    {
        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %[^\n]", 
                   &inputArray[0], &inputArray[1], &inputArray[2], &inputArray[3], &inputArray[4], 
                   &inputArray[5], &inputArray[6], &inputArray[7], &inputArray[8], tail) == 9) /* Check for nine integers */
        {
            for (i = 0; i < SOL_SIZE; i++) 
            {
                buffer->Sol[numRows][i] = inputArray[i]; /* Pass the integers to the Solution array in the buffer */
            }
            numRows++; /* Increment the row counter */
        } 
        else 
        {
            fprintf(stderr, "\nError detected! Incorrect format or extra characters in row %d\n\n", numRows + 1);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    if (numRows != SOL_SIZE) 
    {
        fprintf(stderr, "\nError detected! Incorrect number of rows (found %d, expected 9)\n\n", numRows);
        return 1;
    }

    return 0;
}