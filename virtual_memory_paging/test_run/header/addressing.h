#ifndef ADDRESSING_H
#define ADDRESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OUTER_TABLE 8
#define INNER_TABLE 4

unsigned int generateRandomAddress();
uint32_t* getRandomPages(int numPages);
void getIndices(uint32_t address, uint32_t *indicesArr);

#endif