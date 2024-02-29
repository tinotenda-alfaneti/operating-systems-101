#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#define MEMORY_SIZE 100

// Define a structure for the frame
typedef struct {
    int pid;
    int pageNumber;   
    int frameNumber;
    int valid;
} Frame;


