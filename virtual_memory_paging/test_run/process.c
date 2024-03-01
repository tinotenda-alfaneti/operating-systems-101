#include "header/process.h"
#include "header/addressing.h"
#include "header/simulation.h"
#include "header/frame.h"
#include "header/colors.h"
#include "header/print.h"

#define OUTER_TABLE_SIZE 4
#define INNER_TABLE_SIZE 4

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