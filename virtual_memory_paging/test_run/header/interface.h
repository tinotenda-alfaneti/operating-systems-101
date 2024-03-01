#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10 // Maximum number of processes
#define MAX_MEMORY 128    // Maximum number of pages per process

int moreMemoryRequest(int more_resources);
void manualSystem();
void automatedSystem();

#endif

