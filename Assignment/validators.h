#ifndef VALIDATORS_H
#define VALIDATORS_H

#include "buffer.h"

void* rowSubgridValidator(void* arg);
void* columnValidator(void* arg);
int solutionValidator(int array[SOL_SIZE]);

#endif