#ifndef _FRAME_H
#define _FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "process.h"

#define MEMORY_SIZE 8

// Define a structure for the frame
typedef struct {
    int pid;
    int pageNumber;   
    int frameNumber;
    int valid;
    int offset;
    int outerIndex;
} Frame;

void insertFrame(PageEntry *entry, Frame *memory, Process *processes);
int accessMemory(PageEntry *entry, Frame *memory);
Frame *createFrame(int numFrames);
void releaseFrame(Frame *frame);
void removeFromFrame(Frame remove, Process *processes);
void printStatistics();

#endif
