#include "header/process.h"
#include "header/addressing.h"
#include "header/simulation.h"
#include "header/frame.h"
#include "header/colors.h"

#define OUTER_TABLE_SIZE 4
#define INNER_TABLE_SIZE 4

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

void printProcessTable(Process *process) {
    printf("\n\t\tPAGE TABLE\n");
    printf(YELLOW);
    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
    printf("| Page Number | Frame Num   | Outer Index | Offset      | PID | Valid |\n");
    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
    printf(RESET);

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
        if (entry->frameNumber != -1) {
            printf("| %11d | %s%11d%s | %11d | %11d | %3d | %5d |\n",
               entry->pageNumber, GREEN, entry->frameNumber, RESET, entry->outerIndex, entry->offset, entry->pid, entry->valid);
        } else {
            printf("| %11d | %s%11d%s | %11d | %11d | %3d | %5d |\n",
               entry->pageNumber, RED, entry->frameNumber, RESET, entry->outerIndex, entry->offset, entry->pid, entry->valid);
        }

    }

    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
}