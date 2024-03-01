#include "interface.h"
#include "process.h"
#include "simulation.h"

int *processesIDs = NULL;
Process *allProcesses = NULL;
int num_processes = 0;
int more_resources = 0;


void printBorder() {
    printf("+***********************************************************+\n");
}

void header(){
    printBorder();
    printf("|*|------------------------WELCOME-------------------------|*|\n");
    printf("|*|--------------------------TO----------------------------|*|\n");
    printf("*----------------SIMULATION MEMORY MANEGMENT-----------------*\n");
    printBorder();
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

void automatedPages(int numPages) {
    allProcesses = (Process *)malloc(num_processes * sizeof(Process));
    for (int i = 0; i < num_processes; i++) {
        allProcesses[i] =  *createProcess(processesIDs[i], numPages);
    }
}

void moreResources(){
    int more_resources;
    printf("Enter the number of the process that will request for more resources: ");
    scanf("%d", &more_resources);
    requestMoreMemory(more_resources);
}

void requestMoreMemory(int more_resources) {
    if (more_resources <= 0 || more_resources > num_processes) {
        printf("Invalid process number.                            |\n");
        printf("Please enter a number between 1 and %d.            |\n", num_processes);
        return -1;
    }
        
        printf("| Process %d will request for more resources  |\n", processesIDs[more_resources - 1]);
       
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
        printf("Exceeded maximum number of processes. Exiting...\n");
        return 1;
    }

    num_processes = NUM_PROCESSES;
 
    createProcesses();
    enterNumPages();
    printProcesses();
    if (num_processes != 1) {
         moreResources();
    }
   

    simulateProcessesRun(allProcesses, num_processes);

}

// automated GUI

void automatedSystem(){
    int NUM_PROCESSES = 5; 
    int NUM_PAGES = 2;   
    int more_resources = 3; 

    num_processes = NUM_PROCESSES;

    // Allocate memory for processes IDs
    createProcesses();

    // Allocate memory for allProcesses
    allProcesses = (Process *)malloc(num_processes * sizeof(Process));
    if (allProcesses == NULL) {
        printf("Memory allocation failed.\n");
        free(processesIDs);
        exit(1);
    }

    automatedPages(NUM_PAGES);
    requestMoreMemory(more_resources);

    printProcesses();

    simulateProcessesRun(allProcesses, num_processes);

    // Free allocated memory
    free(allProcesses);
}



void seletSystem(int value) {
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

int main() {
    header();
    
    int SYSTEMTYPE;
    
    printf("Do you want the system to be \n 1). Manual\n 2). Automated \n");
    scanf("%d", &SYSTEMTYPE);
    seletSystem(SYSTEMTYPE);

    printBorder();
    printf("*------------EXECUTION FINISHED EXITING------------*\n");
    printBorder();

    freeProcesses();

    return 0;
}
