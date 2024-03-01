#include "header/simulation.h"
#include "header/addressing.h"
#include "header/colors.h"
#include "header/print.h"

#define MORE_MEM (rand() % (PAGE_SIZE * 3))

int requestMoreMemory(Process *process, int additionalMemory, Frame *memory) {
    printf("\nProcess %d is requesting %s%d%s units...", process->pID, BLUE, additionalMemory, RESET);

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

    for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
        printf("\n\n%sCURRENT PROCCESS RUNNING: PID=%d %s\n", BLUE, processes[i].pID, RESET);
        printRequestQueue(processes[i]);
        if (i == reqProcess - 1) {
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
    
    printf("\n\nDONE SIMULATION\n\n");

    printStatistics();
 
    }