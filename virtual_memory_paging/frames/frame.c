#include "frame.h"

Frame memory[MEMORY_SIZE]; // Array to simulate memory

int accessMemory(int frameNumber, int offset) {
    if (frameNumber < 0 || frameNumber >= MEMORY_SIZE) {
        printf("Invalid frame number\n");
        return -1;
    }

    if (memory[frameNumber].valid == 0) {
        printf("Frame %d is not allocated\n", frameNumber);
        return -1;
    }

    // Accessing data from memory
    int accessedData = memory[frameNumber].pid; // Example: accessing PID stored in the frame
    printf("Data at frame %d, offset %d: %d\n", frameNumber, offset, accessedData);
    printf("Frame ID: %d\n", memory[frameNumber].frameNumber);
    return frameNumber;
}


void insertFrame(Frame frame) {
    int i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].valid == 0) {
            memory[i] = frame;
            printf("Frame successfully allocated into memory for PID: %d\n", frame.pid);
            return;
        }
    }
    printf("Memory is full, cannot insert frame for PID: %d\n", frame.pid);
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

int main() {
    // Test code
    Frame *frames = createFrame(10); // Creating 10 frames
    Frame frame1 = {1, 0, 0, 1}; // Sample frame
    insertFrame(frame1);
    accessMemory(0, 0); 
    releaseFrame(frames); // Releasing frames
    return 0;
}
