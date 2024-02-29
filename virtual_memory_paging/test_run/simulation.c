#include "simulation.h"

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

void simulateProcessesRun( Process processes[], int NUMBER_OF_PROCESSES){
    //list to be shuffled instead of a linked list
    int sum = 0;


    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        sum += processes[i].numPages;
    }
    int total_requests = sum;
    printf("the total number of processes is %d \n", sum);

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
    printf("\nAfter Shuffle\n");
    for(int r = 0; r < total_requests; r++){
        printf("REQUEST ADDRESS: (hex) 0x%04X PROCESS_ID %d\n", list_of_requests[r].address, list_of_requests[r].process_id);
    }

    //initialize memory
	Frame *memory = createFrame(8);

    for(int i = 0; i < total_requests; i++){
        int index = list_of_requests[i].process_id % 100;
        addProcessPagesToMemory(&processes[index], memory);
        printProcessTable(&processes[index]);   
    }
    

    printMemory(memory);
 
    }

    //TEST 
// int main() {

//     int numPages = 2;

//     Process *proc1= createProcess(100, numPages);
//     Process *proc2 = createProcess(101, numPages);
//     Process *proc3 = createProcess(102, numPages);
//     // Process *proc4 = createProcess(16, numPages);
// 	printf("-----------------------FOUND PROCESS ID HERE -------------------");

//     Process processes[3];
//     processes[0] = *proc1;
//     processes[1] = *proc2;
//     processes[2] = *proc3;
//     // processes[3] = *proc4;
    

//     //simulation
//     simulateProcessesRun(processes, 3);

//     return 0;


// }

