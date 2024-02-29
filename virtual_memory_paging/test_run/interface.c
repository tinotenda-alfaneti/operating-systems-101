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
    printf("|*|----------WELCOME----------|*|\n");
    printf("|*|-------------TO------------|*|\n");
    printf("*--SIMULATION MEMORY MANEGMENT--*\n");
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

int requestMoreMemory() {
    int more_resources;
    printf("Enter the number of the process that will request for more resources: ");
    scanf("%d", &more_resources);

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


int main() {
    header();

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

    if(requestMoreMemory() == -1){
        printf("Error occurred. Please try again.\n");
        requestMoreMemory();
    }

    simulateProcessesRun(allProcesses, num_processes);

    printBorder();
    printf("*------------EXECUTION FINISHED EXITING------------*\n");
    printBorder();

    freeProcesses();

    return 0;
}
