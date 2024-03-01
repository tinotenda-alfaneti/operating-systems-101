#include "header/frame.h"

// global variable
int pageFaults = 0;
int hits = 0;
int totalAccesses = 0;

int accessMemory(PageEntry *entry, Frame *memory) {
    int frameNumber = entry->frameNumber;
    if (frameNumber < 0 || frameNumber >= MEMORY_SIZE) {
        printf("Invalid frame number\n");
        return -1;
    }

    if (memory[frameNumber].valid == 0) {
        printf("Frame %d is not allocated\n", frameNumber);
        return -1;
    }

    // Accessing data from memory
    int accessedData = memory[entry->frameNumber].pid; // Example: accessing PID stored in the frame
    printf("\nMEMORY ACCESS REQUEST\n");
    printf("\nData at frame %d, offset %d: %d\n", frameNumber, entry->offset, accessedData);
    printf("Frame ID: %d\n", memory[frameNumber].frameNumber);
    hits++;
    return frameNumber;
}


void insertFrame(PageEntry *entry, Frame *memory, Process *processes) {
    int i, j = -1;
    for (i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].valid == 0) {
            j = i;
        }
        // add the outer page index and then the pid
        if (memory[i].pageNumber == entry->pageNumber && memory[i].outerIndex == entry->outerIndex && memory[i].pid == entry->pid) {
            entry->frameNumber = i;
            entry->valid = 1;
            accessMemory(entry, memory);
            return;
        }
    }

    if (j != -1) {
        memory[j].frameNumber = j;
        memory[j].pageNumber = entry->pageNumber;
        memory[j].pid = entry->pid;
        memory[j].valid = 1;
        memory[j].offset = entry->offset;
        memory[j].outerIndex = entry->outerIndex;
        entry->frameNumber = j;
        printf("Frame successfully allocated into memory for PID: %d\n", memory[j].pid);
        
    }
    else {
        j = rand() % MEMORY_SIZE;
        Frame removedFrame = memory[j];
        memory[j].frameNumber = j;
        memory[j].pageNumber = entry->pageNumber;
        memory[j].pid = entry->pid;
        memory[j].valid = 1;
        memory[j].offset = entry->offset;
        memory[j].outerIndex = entry->outerIndex;
        entry->frameNumber = j;
        removeFromFrame(removedFrame, processes);
        printf("Memory is full, removed page %d added: %d\n",removedFrame.pageNumber, entry->pageNumber);
        pageFaults ++;
    }
    totalAccesses++; 
}

// Function to calculate hit rate
void printStatistics() {
    printf("Total Page Accessed :| %d\n", totalAccesses);
    printf("Total Page hits     :| %d\n", hits);
    printf("Total Page faults   :| %d\n", pageFaults);
    printf("Hit Rate            :| %f\n", ((float)hits / totalAccesses) * 100);
}

void removeFromFrame(Frame remove, Process *processes) {

    PageEntry *entry = &(processes[remove.pid % 100].table->innerPageTables[remove.outerIndex].entries[remove.pageNumber]);
    entry->frameNumber = -1;

}

// Function to create a new frame
Frame *createFrame(int numFrames) {
    Frame *frames = (Frame *)malloc(numFrames * sizeof(Frame));
    if (frames == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < numFrames; i++) {
        frames[i].pid = -1;
        frames[i].pageNumber = -1;
        frames[i].frameNumber = i;
        frames[i].valid = 0;
        frames[i].outerIndex = -1;
        frames[i].offset = -1;
    }
    return frames;
}

void releaseFrame(Frame *frame) {
    free(frame);
}
