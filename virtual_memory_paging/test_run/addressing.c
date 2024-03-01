#include "header/addressing.h"

// Function to extract level indices and offset from a 32-bit hexadecimal address
void getIndices(uint32_t address, uint32_t *indicesArr) {
    
    // Extract level indices and offset using bit masking
    indicesArr[0] = (address & 0xF00) >> OUTER_TABLE; // Extract Level 0 index by masking and shifting
    indicesArr[1] = (address & 0x0F0) >> INNER_TABLE; // Extract Level 1 index by masking and shifting
    indicesArr[2] = address & 0x00F;         // Extract Offset by masking
}

// Function to generate a random 32-bit hexadecimal address
unsigned int generateRandomAddress() {
    
    // Seed the random number generator with current time in nanoseconds
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    long long current_time_nsec = current_time.tv_sec * 1000000000LL + current_time.tv_nsec;
    
    srand(current_time_nsec);

    // Generate a random hexadecimal address
    unsigned int address = 0;
    for (int i = 0; i < 3; ++i) {
        address <<= 4; // Shift left by 4 bits for each iteration
        if (i == 2) {
            address |= rand() % 16;   // For the last nibble, use random value between 0 and 15
        } else {
            address |= rand() % 4; // Generate a random value between 0 and 3 for the index
        }
        
    }

    return address;
}

// Function to generate an array of random 32-bit hexadecimal addresses
uint32_t* getRandomPages(int numPages) {
    uint32_t* requestedPages = (uint32_t*)malloc(numPages*sizeof(uint32_t));

    for (int i = 0; i < numPages; i++) {
        requestedPages[i] = generateRandomAddress();
    }
    return requestedPages;
}
