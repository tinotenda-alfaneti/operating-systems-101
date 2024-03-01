#include "header/simulation.h"
#include "header/addressing.h"
#include "header/colors.h"

void shuffle(Request *items, int num_items)
{
    if (num_items > 1) {
        srand(time(NULL));
        for (int i = 0; i < num_items; i++){
          int j = rand() % (num_items);
          Request tmp =items[j];
          items[j] = items[i];
          items[i] = tmp;
        }
    }
}

void printRequestQueue(Request *list_of_requests, int total_requests) {
    printf("\nRequest Queue:\n");
    printf("+-----------------+------------+\n");
    printf("| REQUEST ADDRESS | PROCESS ID |\n");
    printf("+-----------------+------------+\n");

    for(int r = 0; r < total_requests; r++) {
        printf("|   0x%04X        |     %3d    |\n", list_of_requests[r].address, list_of_requests[r].process_id);
    }

    printf("+-----------------+------------+\n");
}

void printMemory(Frame *memory) {
    printf("\n\t\tMEMORY\n");
    printf(YELLOW);
    printf("+-------+---------+--------+--------+\n");
    printf("| Frame | Process |  Page  |  Outer |\n");
    printf("|  Num  |   ID    |  Num   |  Index |\n");
    printf("+-------+---------+--------+--------+\n");
    printf(RESET);
    
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].valid == 0) {
            printf("|%7d|   %sEmpty%s                   |\n", i, RED, RESET);
        } else {
            printf("|%7d|%9d|%8d|%8d|\n", i, memory[i].pid, memory[i].pageNumber, memory[i].outerIndex);
        }
        printf("+-------+---------+--------+--------+\n");
    }
}
void addProcessPagesToMemory(Request *request, Frame *memory, Process *processes) {

	uint32_t indicesArr[3];
	getIndices(request->address, indicesArr);

	int outerIdx = (int)indicesArr[0];
	int pageNum = (int)indicesArr[1];
	int offset = (int)indicesArr[2];

	PageEntry *entry = &(processes[request->process_id % 100].table->innerPageTables[outerIdx].entries[pageNum]);
	entry->outerIndex = outerIdx;
	entry->offset = offset;

	insertFrame(entry, memory, processes);
        

}


void simulateProcessesRun(Process processes[], int NUMBER_OF_PROCESSES, int reqProcess){
    
    int sum = 0;

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        sum += processes[i].numPages;
    }
    int total_requests = sum;

    Request *list_of_requests = (Request*)malloc(sum * sizeof(Request));

     for(int i = 0; i < NUMBER_OF_PROCESSES; i ++){
        for(int j=0; j < processes[i].numPages; j++){
            sum--; 
            if(sum < 0){
                break;
            }
            Request* new_request = (Request*)malloc(sizeof(Request));
            new_request->address = processes[i].requestedPages[j];
            new_request->process_id = processes[i].pID;
            list_of_requests[sum] = *new_request;            
        }
        if(sum == 0){
                break;
            }
    }

    shuffle(list_of_requests, total_requests);
    printRequestQueue(list_of_requests, total_requests);

    //initialize memory
	Frame *memory = createFrame(8);
    printMemory(memory);

    for(int i = 0; i < total_requests; i++){
        int index = list_of_requests[i].process_id % 100;
        printf("\n\n%sREQUEST %d to address 0x%04X from %d%s\n", BLUE, i + 1, list_of_requests[i].address, list_of_requests[i].process_id, RESET);
        addProcessPagesToMemory(&list_of_requests[i], memory, processes);
        printProcessTable(&processes[index]);   
    }
    
    requestMoreMemory(&processes[reqProcess], 3);
    

    printMemory(memory);

    printStatistics();
 
    }