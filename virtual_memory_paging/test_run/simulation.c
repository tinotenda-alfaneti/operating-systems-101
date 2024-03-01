#include "header/simulation.h"
#include "header/addressing.h"
#include "header/colors.h"

#define MORE_MEM (rand() % (PAGE_SIZE * 3))

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

int requestMoreMemory(Process *process, int additionalMemory, Frame *memory) {
    printf("\nProcess %d is requesting %s%d%s...", process->pID, BLUE, additionalMemory, RESET);

    int additionalPages = additionalMemory / PAGE_SIZE;
    if ((additionalMemory % PAGE_SIZE) != 0) additionalPages += 1;

    int freeFrames = countFreeFrames(memory);

    if (process->numPages + additionalPages > freeFrames) {
        printf("\n%sMemory request denied. Maximum number of requests reached.%s\n", RED, RESET);
        addProcessPagesToMemory(process, memory, 2);
        return -1;
    } else {
        printf("\n%sMemory request for %d additional pages granted.%s\n", GREEN, additionalPages, RESET);
        // Allocate memory and update process details accordingly
        process->requestedPages = realloc(process->requestedPages, (process->numPages + additionalPages) * sizeof(uint32_t));
        uint32_t *additionalPagesArray = getRandomPages(additionalPages);

        for (int i = 0; i < additionalPages; i++) {
            process->requestedPages[process->numPages + i] = additionalPagesArray[i];
        }

        process->numPages += additionalPages;

        printf("\npage table after being granted more resources\n");
        printProcessTable(process);
        addProcessPagesToMemory(process, memory, -1);
        return 1;
    }
}


void addProcessPagesToMemory(Process *process, Frame *memory, int needMemory) {

	uint32_t indicesArr[3];

    if (needMemory == 1) {
        requestMoreMemory(process, MORE_MEM, memory);
        return;
    } else if (needMemory == 2) {
        return;
    }

    for (int i = 0; i < process->numPages; i++) {

        getIndices(process->requestedPages[i], indicesArr);

        int outerIdx = (int)indicesArr[0];
        int pageNum = (int)indicesArr[1];
        int offset = (int)indicesArr[2];

        PageEntry *entry = &(process->table->innerPageTables[outerIdx].entries[pageNum]);
        entry->outerIndex = outerIdx;
        entry->offset = offset;
        
        insertFrame(entry, memory, process);

    }

}


void simulateProcessesRun(Process *processes, int NUMBER_OF_PROCESSES, int reqProcess){

    //initialize memory
	Frame *memory = createFrame();
    printMemory(memory);

    for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
        printf("\n\n%sCURRENT PROCCESS RUNNING: PID=%d %s\n", BLUE, processes[i].pID, RESET);
        printRequestQueue(processes[i]);
        if (i == reqProcess) {
            addProcessPagesToMemory(&processes[i], memory, 1);
        } else {
            addProcessPagesToMemory(&processes[i], memory, -1);
        }
        
        printProcessTable(&processes[i]);
        printMemory(memory);

        //Memory deallocation
        releaseFrame(memory);
        memory = createFrame();   
    }
    
    // requestMoreMemory(&processes[reqProcess], 3, memory);
    

    printMemory(memory);

    printStatistics();
 
    }