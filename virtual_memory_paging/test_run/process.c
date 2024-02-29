#include "process.h"
#include "addressing.h"
#include "simulation.h"
#include "frame.h"

#define OUTER_TABLE_SIZE 16
#define INNER_TABLE_SIZE 16

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

void printProcessTable(Process *process) {
    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
    printf("| Page Number | Frame Num   | Outer Index | Offset      | PID | Valid |\n");
    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");

    uint32_t indicesArr[3];

    for (int i = 0; i < process->numPages; ++i) {
        getIndices(process->requestedPages[i], indicesArr);

        PageEntry *entry = &(process->table->innerPageTables[(int)indicesArr[0]].entries[(int)indicesArr[1]]);
        printf("| %11d | %11d | %11d | %11d | %3d | %5d |\n",
               entry->pageNumber, entry->frameNumber, entry->outerIndex, entry->offset, entry->pid, entry->valid);
    }

    printf("+-------------+-------------+-------------+-------------+-----+-------+\n");
}

void addProcessPagesToMemory(Request *request, int *memory, Process *processes) {

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

void printMemory(Frame *memory) {
    printf("\n\t\tMEMORY\n");
    printf("+-------+---------+--------+--------+\n");
    printf("| Frame | Process |  Page  |  Outer |\n");
    printf("|  Num  |   ID    |  Num   |  Index |\n");
    printf("+-------+---------+--------+--------+\n");
    
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].valid == 0) {
            printf("|%7d|   Empty |        |        |\n", i);
        } else {
            printf("|%7d|%9d|%8d|%8d|\n", i, memory[i].pid, memory[i].pageNumber, memory[i].outerIndex);
        }
        printf("+-------+---------+--------+--------+\n");
    }
}

//TEST

// int main() {

//     int numPages = 9;

//     Process *proc = createProcess(12, numPages);
// 	printf("Process ID: %d\n", proc->pID);

//     // Generate a random address
//     unsigned int address;

//     uint32_t indicesArr[3]; // Array to store level indices and offset
    
// 	//initialize memory
// 	Frame *memory = createFrame(8);


// 	// //print the different pages to be requested by the process
//     // for (int i = 0; i < numPages; i++) {
// 	//     address = proc->requestedPages[i];

// 	//     // Extract level indices and offset from the address
//     // 	getIndices(address, indicesArr);

//     //     // Print the random address in hexadecimal format
//     //     printf("\n\nRandom Address: 0x%04X\n", address);
// 	//     // Print the results
//     // 	printf("OUTER_TABLE index: (hex) 0x%01X (dec) %lu\n", indicesArr[0], (unsigned long)indicesArr[0]);
//     // 	printf("PAGE NUMBER: (hex) 0x%01X (dec) %lu\n", indicesArr[1], (unsigned long)indicesArr[1]);
//     // 	printf("Offset: (hex) 0x%02X (dec) %lu\n\n", indicesArr[2], (unsigned long)indicesArr[2]);
// 	// sleep(1);
//     // }

// 	//adding process pages to memory test
// 	addProcessPagesToMemory(proc, memory);

// 	// Print process table
//     printProcessTable(proc);

//     // Print memory
//     printMemory(memory);

// 	printProcessTable(proc);
//     return 0;

// }