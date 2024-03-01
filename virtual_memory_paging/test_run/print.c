#include "header/print.h"
#include "header/addressing.h"

void printMemory(Frame *memory) {
    printf("\n\t\tMEMORY\n");
    printf(YELLOW);
    printf("+-------+---------+--------+--------+\n");
    printf("| Frame | Process |  Page  |  Outer |\n");
    printf("|  Num  |   ID    |  Num   |  Index |\n");
    printf("+-------+---------+--------+--------+\n");
    printf(RESET);
    
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (memory[i].valid == 0) {
            printf("|%7d|   %sEmpty%s                   |\n", i, RED, RESET);
        } else {
            printf("|%7d|%9d|%8d|%8d|\n", i, memory[i].pid, memory[i].pageNumber, memory[i].outerIndex);
        }
        printf("+-------+---------+--------+--------+\n");
    }
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

void printRequestQueue(Process process) {
    printf("\n\t\tREQUEST QUEUE\n");
    printf(YELLOW);
    printf("+-----------------+-----------+\n");
    printf("| REQUEST ADDRESS |PROCESS ID |\n");
    printf("+-----------------+-----------+\n");
    printf(RESET);

    for(int r = 0; r < process.numPages; r++) {
        printf("|   0x%03X        |     %3d    |\n", process.requestedPages[r], process.pID);
    }

    printf("+-----------------+-----------+\n");
}