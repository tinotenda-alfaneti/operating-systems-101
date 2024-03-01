#ifndef _FRAME_H
#define _FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "process.h"

#define MEMORY_SIZE 128
#define PAGE_SIZE 16
#define NUM_FRAMES (MEMORY_SIZE / PAGE_SIZE)

// Define a structure for the frame
typedef struct {
    int pid;
    int pageNumber;   
    int frameNumber;
    int valid;
    int outerIndex;
    int *offset;
} Frame;

void insertFrame(PageEntry *entry, Frame *memory, Process *processes);
int accessMemory(PageEntry *entry, Frame *memory);
Frame *createFrame();
void releaseFrame(Frame *frame);
void removeFromFrame(Frame remove, Process *processes);
void printStatistics();

#endif
