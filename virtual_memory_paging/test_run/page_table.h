#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTER_TABLE_SIZE 16
#define INNER_TABLE_SIZE 16

typedef struct {
    int pid;
    int pageNumber;   
    int frameNumber;
    int valid;\
    int offset;
    int outerIndex;
} PageEntry;

typedef struct {
    PageEntry *entries;
} InnerPageTable;

typedef struct {
    InnerPageTable *innerPageTables;
} OuterPageTable;

OuterPageTable* initializePageTable(int pid);