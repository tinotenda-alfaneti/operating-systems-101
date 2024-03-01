#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "process.h"
#include <time.h> 
#include "frame.h"

void simulateProcessesRun( Process processes[], int NUMBER_OF_PROCESSES, int reqProcess);
void printMemory(Frame *memory);
void addProcessPagesToMemory(Process *process, Frame *memory, int needMemory);
int countFreeFrames(Frame *memory);
int requestMoreMemory(Process *process, int additionalMemory, Frame *memory);

#endif /* SIMULATION_H */