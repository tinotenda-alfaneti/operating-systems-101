#include "header/frame.h"
#include "header/colors.h"

// global variable
int pageFaults = 0;
int hits = 0;
int totalAccesses = 0;

int accessMemory(PageEntry *entry, Frame *memory) {
    int frameNumber = entry->frameNumber;
    if (frameNumber < 0 || frameNumber >= NUM_FRAMES) {
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
    printf("\nData at frame %d, from page: %d, offset %d, PID: %d\n", frameNumber, entry->pageNumber, entry->offset, accessedData);
    printf("Frame ID: %d\n", memory[frameNumber].frameNumber);
    hits++;
    totalAccesses++;
    return frameNumber;
}


void insertFrame(PageEntry *entry, Frame *memory, Process *process) {
    int i, j = -1;
    for (i = NUM_FRAMES - 1; i >= 0; i--) {
        if (memory[i].valid == 0) {
            j = i;

        }
        // add the outer page index and then the pid
        if (memory[i].pageNumber == entry->pageNumber && memory[i].outerIndex == entry->outerIndex && memory[i].pid == entry->pid) {
            entry->frameNumber = i;
            entry->valid = 1;
            memory[i].offset[entry->offset] = entry->offset;
            accessMemory(entry, memory);
            return;
        }
    }

    if (j != -1) {
        memory[j].frameNumber = j;
        memory[j].pageNumber = entry->pageNumber;
        memory[j].pid = entry->pid;
        memory[j].valid = 1;
        memory[j].offset[entry->offset] = entry->offset;
        memory[j].outerIndex = entry->outerIndex;
        entry->frameNumber = j;
        printf(GREEN);
        printf("Page %d successfully allocated into memory in frame: %d\n", entry->pageNumber, memory[j].frameNumber);
        hits++;
        printf(RESET);
        
    }
    else {
        j = rand() % NUM_FRAMES;
        Frame removedFrame = memory[j];
        memory[j].frameNumber = j;
        memory[j].pageNumber = entry->pageNumber;
        memory[j].pid = entry->pid;
        memory[j].valid = 1;
        memory[j].offset[entry->offset] = entry->offset;
        memory[j].outerIndex = entry->outerIndex;
        entry->frameNumber = j;
        removeFromFrame(removedFrame, process);
        pageFaults ++;
        printf(RED);
        printf("Memory is full, removed page %d added: %d\n",removedFrame.pageNumber, entry->pageNumber);
        // totalAccesses++;
        printf(RESET);
    }
    totalAccesses++; 
}

void printStatistics() {
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

void removeFromFrame(Frame remove, Process *process) {

    PageEntry *entry = &(process->table->innerPageTables[remove.outerIndex].entries[remove.pageNumber]);
    entry->frameNumber = -1;

}

int countFreeFrames(Frame *memory) {
    int sum = 0;
    for (int i = NUM_FRAMES - 1; i >= 0; i--) {
        if (memory[i].valid == 0) {
            sum++;
        }
     }
     return sum;
}

// Function to create a new frame
Frame *createFrame() {
    Frame *frames = (Frame *)malloc(NUM_FRAMES * sizeof(Frame));
    if (frames == NULL) {
        printf("Memory allocation failed\n");
        pageFaults ++;
        exit(1);
    }
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i].pid = -1;
        frames[i].pageNumber = -1;
        frames[i].frameNumber = i;
        frames[i].valid = 0;
        frames[i].outerIndex = -1;
        frames[i].offset = (int *)malloc(PAGE_SIZE * sizeof(int));
    }
    return frames;
}

void releaseFrame(Frame *frame) {
    free(frame);
}
