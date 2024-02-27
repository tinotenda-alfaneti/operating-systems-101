#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

//Define the bit shift for each level
#define OUTER_TABLE 12
#define INNER_TABLE 8

unsigned int generateRandomAddress();
uint32_t* getRandomPages(int numPages);