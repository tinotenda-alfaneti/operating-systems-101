#include "frame.h"

// global variable
int pageFaults = 0;
int hits = 0;
int totalAccesses = 0;


int accessMemory(int frameNumber, int offset, Frame *memory) {
    if (frameNumber < 0 || frameNumber >= MEMORY_SIZE) {
        printf("Invalid frame number\n");
        return -1;
    }

    if (memory[frameNumber].valid == 0) {
        printf("Frame %d is not allocated\n", frameNumber);
        return -1;
    }

    int accessedData = memory[frameNumber].pid; 
    printf("Data at frame %d, offset %d: %d\n", frameNumber, offset, accessedData);
    printf("Frame ID: %d\n", memory[frameNumber].frameNumber);
    hits++;
    return frameNumber;
}

void insertFrame(PageEntry *entry, Frame *memory) {
    
    int i, j = -1;
    for (i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].valid == 0) {
            j = i;
        }
        // add the outer page index and then the pid
        if (memory[i].pageNumber == entry->pageNumber) {
            entry->frameNumber = i;
            accessMemory(entry->frameNumber, 0, memory);
            return;
        }
    }

    if (j != -1) {
        memory[j].frameNumber = j;
        memory[j].pageNumber = entry->pageNumber;
        memory[j].pid = entry->pid;
        memory[j].valid = 1;
        entry->frameNumber = j;
        printf("Frame successfully allocated into memory for PID: %d\n", memory[j].pid);
        
    }
    else {
        pageFaults ++;
        printf("Memory is full, cannot insert page %d for PID: %d\n",entry->pageNumber, entry->pid);
       
    }
    totalAccesses++; 
}

// Function to calculate hit rate
float printStatistics() {
    printf("Total Page Accessed :| %d\n", totalAccesses);
    printf("Total Page hits     :| %d\n", hits);
    printf("Total Page faults   :| %d\n", pageFaults);
    printf("Hit Rate            :| %f\n", ((float)hits / totalAccesses) * 100);
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
    }
    printf("%d frames created in memory. Memory size: %d\n", numFrames, MEMORY_SIZE);
    return frames;
}

void releaseFrame(Frame *frame) {
    free(frame);
}

//TEST
// int main() {
//     // Test code
//     Frame *frames = createFrame(10); // Creating 10 frames
//     Frame frame1 = {1, 0, 0, 1}; // Sample frame
//     insertFrame(frame1);
//     accessMemory(0, 0); 
//     releaseFrame(frames); // Releasing frames
//     return 0;
// }
