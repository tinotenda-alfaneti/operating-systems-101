#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10 // Maximum number of processes
#define MAX_PAGES 100    // Maximum number of pages per process

typedef struct {
    int id;
    int num_pages;
} Process;

