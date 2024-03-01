#include "header/process.h"
#include "header/addressing.h"
#include "header/simulation.h"
#include "header/frame.h"

#define OUTER_TABLE_SIZE 16
#define INNER_TABLE_SIZE 16

Process *createProcess(int pID, int numPages)
{
	Process* p = (Process*)malloc(sizeof(Process));
	p->requestedPages = (uint32_t*)malloc(numPages*sizeof(uint32_t));
	p->pID = pID;
	p->requestedPages = getRandomPages(numPages);
	p->table = initializePageTable(pID);
	p->numPages = numPages;
	return p;
}

int requestMoreMemory(Process *process, int additionalPages) {
    printf("\nProcess %d is requesting more resources...", process->pID);
    if (process->numPages + additionalPages > MAX_REQUESTS) {
        printf("\nMemory request denied. Maximum number of requests reached.\n");
        return -1;
    } else {
        printf("\nMemory request for %d additional pages granted.\n", additionalPages);
        // Allocate memory and update process details accordingly
        process->requestedPages = realloc(process->requestedPages, (process->numPages + additionalPages) * sizeof(uint32_t));
        uint32_t *additionalPagesArray = getRandomPages(additionalPages);
        for (int i = 0; i < additionalPages; i++) {
            process->requestedPages[process->numPages + i] = additionalPagesArray[i];
        }
        process->numPages += additionalPages;
        printf("\npage table after being granted more resources\n");
        printProcessTable(process);
        return 1;
    }
}

void printProcessTable(Process *process) {
    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
    printf("| Page Number | Frame Num   | Outer Index | Offset      | PID | Valid |\n");
    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");

    uint32_t indicesArr[3];

    for (int i = 0; i < process->numPages; ++i) {
        getIndices(process->requestedPages[i], indicesArr);
        int pageNumber = (int)indicesArr[1];
        int outerIndex = (int)indicesArr[0];
        int offset = (int)indicesArr[2];

        PageEntry *entry = &(process->table->innerPageTables[(int)indicesArr[0]].entries[pageNumber]);
        entry->pageNumber = pageNumber;
        entry->outerIndex = outerIndex;
        entry->offset = offset;
        printf("| %11d | %11d | %11d | %11d | %3d | %5d |\n",
               entry->pageNumber, entry->frameNumber, entry->outerIndex, entry->offset, entry->pid, entry->valid);
    }

    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
}