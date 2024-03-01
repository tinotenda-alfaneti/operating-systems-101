#include "frame.h"

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
    totalAccesses++;
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
        hits++;
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
        pageFaults ++;
        removeFromFrame(removedFrame, processes);
        printf("Memory is full, removed page %d added: %d\n",removedFrame.pageNumber, entry->pageNumber);
        // totalAccesses++;
    }
    totalAccesses++; 
}

void printStatistics(int totalAccesses, int hits, int pageFaults) {
    // Calculate hit rate
    float hitRate = ((float)hits / totalAccesses) * 100;

    // Print table
    printf("\n\t\tPAGE STATISTICS\n");
    printf("+-----------------------+----------------+\n");
    printf("|  %-20s |  %12d  |\n", "Total Page Accessed", totalAccesses);
    printf("+-----------------------+----------------+\n");
    printf("|  %-20s |  %12d  |\n", "Total Page hits", hits);
    printf("+-----------------------+----------------+\n");
    printf("|  %-20s |  %12d  |\n", "Total Page faults", pageFaults);
    printf("+-----------------------+----------------+\n");
    printf("|  %-20s |  %12.2f%% |\n", "Hit Rate", hitRate);
    printf("+-----------------------+----------------+\n");
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
        pageFaults ++;
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
