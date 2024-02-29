#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "process.h"
#include <time.h> 
#include "frame.h"

typedef struct {
    int address;
    int process_id;  
} Request;

void simulateProcessesRun( Process processes[], int NUMBER_OF_PROCESSES);
void shuffle(Request *items, int num_items);

#endif /* SIMULATION_H */