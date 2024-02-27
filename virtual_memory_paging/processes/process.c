#include "process.h"
#include "addressing.h"

#define OUTER_TABLE_SIZE 16
#define INNER_TABLE_SIZE 16
#define MEMORY_SIZE 8 // Number of frames in memory

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

void printProcessTable(Process *process)
{
	printf("\nProcess pID: %d\n", process->pID);
	printf("Current Pages: %d\n", process->numPages);

	uint32_t indicesArr[3];

	for (int i = 0; i < process->numPages; ++i) {

		getIndices(process->requestedPages[i], indicesArr);

		PageEntry *entry = &(process->table->innerPageTables[(int)indicesArr[0]].entries[(int)indicesArr[1]]);
		printf("Page Number: %d||Frame Number: %d||PID: %d||Valid: %d\n",
			entry->pageNumber, entry->frameNumber, entry->pid, entry->valid);
		
	}
}

void addProcessPagesToMemory(Process *process, int *memory) {
    int i;
    int writtenPages = 0;

    for (i = 0; i < process->numPages; i++) {
        uint32_t indicesArr[3];
        getIndices(process->requestedPages[i], indicesArr);

        PageEntry *entry = &(process->table->innerPageTables[(int)indicesArr[0]].entries[(int)indicesArr[1]]);

        if (entry->frameNumber == -1) {
            // Find an empty frame in memory
            int emptyFrame = -1;
            for (int j = 0; j < MEMORY_SIZE; j++) {
                if (memory[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            if (emptyFrame != -1) {
                // Update page entry with frame number
                entry->frameNumber = emptyFrame;
				entry->pageNumber = (int) indicesArr[1];
                entry->valid = 1; // Mark as valid
				entry->pid = process->pID;
                // Update memory with page number
                memory[emptyFrame] = entry->pageNumber;
                writtenPages++;
            } else {
                printf("Memory is full\n");
            }
        } else {
            printf("Collision: Page %d of process %d is already in memory\n", entry->pageNumber, process->pID);
        
        }
    }

    if (writtenPages == process->numPages)
        printf("Page added successfully\n");
    else
        printf("Error allocating memory\n");
}

void printMemory(int *memory) {
    printf("\nMemory:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == -1) {
            printf("%2d: Empty\n", i);
        } else {
            printf("%2d: Page %d\n", i, (int)memory[i]);
        }
    }
}

int main() {

    int numPages = 5;

    Process *proc = createProcess(12, numPages);
	printf("Process ID: %d\n", proc->pID);

    // Generate a random address
    unsigned int address;

    uint32_t indicesArr[3]; // Array to store level indices and offset
    
	//initialize memory
	int memory[MEMORY_SIZE];
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = -1; // Initialize memory with -1 (empty)
    }


	//print the different pages to be requested by the process
    for (int i = 0; i < numPages; i++) {
	    address = proc->requestedPages[i];

	    // Extract level indices and offset from the address
    	getIndices(address, indicesArr);

        // Print the random address in hexadecimal format
        printf("\n\nRandom Address: 0x%04X\n", address);
	    // Print the results
    	printf("OUTER_TABLE index: (hex) 0x%01X (dec) %lu\n", indicesArr[0], (unsigned long)indicesArr[0]);
    	printf("PAGE NUMBER: (hex) 0x%01X (dec) %lu\n", indicesArr[1], (unsigned long)indicesArr[1]);
    	printf("Offset: (hex) 0x%02X (dec) %lu\n\n", indicesArr[2], (unsigned long)indicesArr[2]);
	sleep(1);
    }

	//adding process pages to memory test
	addProcessPagesToMemory(proc, memory);

	// Print process table
    printProcessTable(proc);

    // Print memory
    printMemory(memory);

	printProcessTable(proc);
    return 0;

}