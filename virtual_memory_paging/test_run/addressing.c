#include "header/addressing.h"

// Define the bit masks for extracting level indices and offset
uint32_t outerMask = 0xF00;  
uint32_t innerMask = 0x0F0;  
uint32_t offsetMask = 0x00F;  // mask for offset

// Function to extract level indices and offset from a 32-bit hexadecimal address
void getIndices(uint32_t address, uint32_t *indicesArr) {
    
    // Extract level indices and offset using bit masking
    indicesArr[0] = (address & outerMask) >> OUTER_TABLE; // Level 0 index
    indicesArr[1] = (address & innerMask) >> INNER_TABLE; // Level 1 index
    indicesArr[2] = address & offsetMask;         // Offset
}

// Function to generate a random 32-bit hexadecimal address
unsigned int generateRandomAddress() {
    
    // Seed the random number generator
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    long long current_time_nsec = current_time.tv_sec * 1000000000LL + current_time.tv_nsec;
    
    srand(current_time_nsec);

    // Generate a random hexadecimal address
    unsigned int address = 0;
    for (int i = 0; i < 3; ++i) {
        address <<= 4; // Shift left by 4 bits
        if (i == 2) {
            address |= rand() % 16;   
        } else {
            address |= rand() % 4; // Generate a random nibble (3-bit hexadecimal digit)
        }
        
    }

    return address;
}

uint32_t* getRandomPages(int numPages) {
    uint32_t* requestedPages = (uint32_t*)malloc(numPages*sizeof(uint32_t));

    for (int i = 0; i < numPages; i++) {
        requestedPages[i] = generateRandomAddress();
    }
    return requestedPages;
}
