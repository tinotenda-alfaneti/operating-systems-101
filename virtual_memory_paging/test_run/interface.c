#include "header/interface.h"
#include "header/process.h"
#include "header/simulation.h"
#include "header/colors.h"

int *processesIDs = NULL;
Process *allProcesses = NULL;
int num_processes = 0;
int more_resources = 0;


void printBorder() {
    printf("+***********************************************************+\n");
}

void header(){
    printf(YELLOW);
    printBorder();
    printf("*----------------------------WELCOME------------------------*\n");
    printf("*------------------------------TO---------------------------*\n");
    printf("*-------------------MEMORY MANAGEMENT SIMULATION------------*\n");
    printBorder();
    printf(RESET);
}

void createProcesses() {
    processesIDs = (int*)malloc(MAX_PROCESSES * sizeof(int));
    if (processesIDs == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < num_processes; i++) {
        processesIDs[i] = 100 + i;
    }
}

void freeProcesses() {
    free(processesIDs);
}

void enterNumPages() {
    allProcesses = (Process *)malloc(num_processes * sizeof(Process));
    for (int i = 0; i < num_processes; i++) {
        int numPages = 0;
        printf("Enter number of pages for process %d (ID: %d): ", i + 1, processesIDs[i]);
        scanf("%d", &numPages);

        allProcesses[i] =  *createProcess(processesIDs[i], numPages);
    }
}

void automatedPages(int *numPages) {
    allProcesses = (Process *)malloc(num_processes * sizeof(Process));
    for (int i = 0; i < num_processes; i++) {
        allProcesses[i] =  *createProcess(processesIDs[i], numPages[i]);
    }
}

void moreResources(){
    int more_resources;
    printf("Enter the number of the process that will request for more resources: ");
    scanf("%d", &more_resources);
    moreMemoryRequest(more_resources);
}

int moreMemoryRequest(int more_resources) {
    if (more_resources <= 0 || more_resources > num_processes) {
        printf(RED);
        printf("Invalid process number.                            |\n");
        printf("Please enter a number between 1 and %d.            |\n", num_processes);
        printf(RESET);
        return -1;
    }
        
        printf("| Process %d will request for more resources  |\n", processesIDs[more_resources - 1]);
        return 1;
       
}

void printProcesses() {
    printf("\nProcesses:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d (ID: %d) - Pages: %d\n", i + 1, processesIDs[i], allProcesses[i].numPages);
    }
}

// manual GUI
void manualSystem(){

    int NUM_PROCESSES;
    printf("Enter number of processes you want to run: ");
    scanf("%d", &NUM_PROCESSES);

    if (NUM_PROCESSES > MAX_PROCESSES) {
        printf("%sExceeded maximum number of processes. Exiting...%s\n", RED, RESET);
        return;
    }

    num_processes = NUM_PROCESSES;
 
    createProcesses();
    enterNumPages();
    printProcesses();
    if (num_processes != 1) {
         moreResources();
    }
   

    simulateProcessesRun(allProcesses, num_processes, more_resources);

}

// automated GUI

void automatedSystem(){
    int NUM_PROCESSES = 5; 
    int NUM_PAGES[5] = {1,2,3,4,5};   
    int more_resources = 1; 

    num_processes = NUM_PROCESSES;

    // Allocate memory for processes IDs
    createProcesses();

    // Allocate memory for allProcesses
    allProcesses = (Process *)malloc(num_processes * sizeof(Process));
    if (allProcesses == NULL) {
        
        printf("Memory allocation failed.\n");
        free(processesIDs);
    }

    automatedPages(NUM_PAGES);

    moreMemoryRequest(more_resources);

    printProcesses();

    simulateProcessesRun(allProcesses, num_processes, more_resources);

    // Free allocated memory
    free(allProcesses);
}



void selectSystem(int value) {
    switch(value) {
        case 1:
            manualSystem();
            break;
        case 2:
            automatedSystem();
            break;
        default:
            printf("Invalid option\n");
            break;
    }
    return;
}

int main(int argc, char *argv[]) {
    header();
    
    int SYSTEMTYPE;
    
    if (argc == 2) {
        SYSTEMTYPE = atoi(argv[1]);
    } else {

        printf("Do you want the system to be \n 1). Manual\n 2). Automated \n");
        scanf("%d", &SYSTEMTYPE);

    }


    selectSystem(SYSTEMTYPE);

    printf(YELLOW);
    printBorder();
    printf("*------------------EXECUTION FINISHED EXITING---------------*\n");
    printBorder();
    printf(RESET);

    freeProcesses();

    return 0;
}
