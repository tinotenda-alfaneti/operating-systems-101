#ifndef __process_h_
#define __process_h_

#include "page_table.h"

typedef struct _Process { 
  int pID;
  int prob; // for requesting another page
  uint32_t  *requestedPages;
  OuterPageTable *table; 
  int numPages;
}Process;

#endif
