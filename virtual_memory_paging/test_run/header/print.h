#ifndef __PRINT_H__
#define __PRINT_H__

#include "simulation.h"
#include "process.h"
#include "colors.h"

void printMemory(Frame *memory);
void printProcessTable(Process *process);
void printRequestQueue(Process process);

#endif