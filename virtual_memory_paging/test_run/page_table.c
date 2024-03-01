#include "header/page_table.h"

OuterPageTable* initializePageTable(int pid) {
    OuterPageTable *outerPageTable = (OuterPageTable*)malloc(sizeof(OuterPageTable));
    if (outerPageTable == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    outerPageTable->innerPageTables = (InnerPageTable*)malloc(INNER_TABLE_SIZE * sizeof(InnerPageTable));
    if (outerPageTable->innerPageTables == NULL) {
        // Handle memory allocation failure
        free(outerPageTable);
        return NULL;
    }

    // Initialize outer page table
    for (int i = 0; i < OUTER_TABLE_SIZE; ++i) {
        InnerPageTable *innerPageTable = &(outerPageTable->innerPageTables[i]);
        innerPageTable->entries = (PageEntry*)malloc(INNER_TABLE_SIZE * sizeof(PageEntry));
        if (innerPageTable->entries == NULL) {
            // Handle memory allocation failure
            // Free allocated memory before returning
            for (int j = 0; j < i; ++j) {
                free(outerPageTable->innerPageTables[j].entries);
            }
            free(outerPageTable->innerPageTables);
            free(outerPageTable);
            return NULL;
        }

        // Initialize inner page table
        for (int j = 0; j < INNER_TABLE_SIZE; ++j) {
            PageEntry *pageEntry = &(innerPageTable->entries[j]);
            pageEntry->pid = pid;
            pageEntry->pageNumber = j; // Page numbers 0 to 15
            pageEntry->frameNumber = -1; // Initialize frame number to -1
            pageEntry->valid = 0; // Assuming initially all entries are invalid
            pageEntry->offset = -1;
            pageEntry->outerIndex = -1;
        }
    }

    return outerPageTable;
}

// Function to free the memory allocated for the page table
void freePageTable(OuterPageTable *outerPageTable) {
    if (outerPageTable == NULL) {
        return;
    }

    for (int i = 0; i < OUTER_TABLE_SIZE; ++i) {
        free(outerPageTable->innerPageTables[i].entries);
    }
    free(outerPageTable->innerPageTables);
    free(outerPageTable);
}