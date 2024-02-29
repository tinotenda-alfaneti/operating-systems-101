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
} Frame;

void insertFrame(PageEntry *entry, Frame *memory);
// Frame memory[MEMORY_SIZE]; // Array to simulate memory
int accessMemory(int frameNumber, int offset, Frame *memory);
Frame *createFrame(int numFrames);
void releaseFrame(Frame *frame);
