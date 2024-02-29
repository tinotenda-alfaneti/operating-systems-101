#include "interface.h"

Process *processes = NULL;
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
    processes = (Process*)malloc(MAX_PROCESSES * sizeof(Process));
    if (processes == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < num_processes; i++) {
        processes[i].id = 100 + i;
    }
}

void freeProcesses() {
    free(processes);
}

void enterNumPages() {
    for (int i = 0; i < num_processes; i++) {
        printf("Enter number of pages for process %d (ID: %d): ", i + 1, processes[i].id);
        scanf("%d", &processes[i].num_pages);
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
        
        printf("| Process %d will request for more resources  |\n", processes[more_resources - 1].id);
       
}


void printProcesses() {
    printf("\nProcesses:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d (ID: %d) - Pages: %d\n", i + 1, processes[i].id, processes[i].num_pages);
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

    printBorder();
    printf("*------------EXECUTION FINISHED EXITING------------*\n");
    printBorder();

    freeProcesses();

    return 0;
}
