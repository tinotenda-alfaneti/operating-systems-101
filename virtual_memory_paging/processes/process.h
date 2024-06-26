#ifndef __process_h_
#define __process_h_

#include "page_table.h"

typedef struct { 
  int pID;
  int prob; // for requesting another page
  uint32_t  *requestedPages;
  OuterPageTable *table; 
  int numPages;
}Process;
Process *createProcess(int pID, int numPages);
void printProcessTable(Process *process);

#endif
