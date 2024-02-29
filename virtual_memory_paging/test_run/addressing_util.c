#include "addressing.h"

// Define the bit masks for extracting level indices and offset
uint32_t outerMask = 0xF000;  
uint32_t innerMask = 0x0F00;  
uint32_t offsetMask = 0x00FF;  // mask for offset

// Function to extract level indices and offset from a 32-bit hexadecimal address
void getIndices(uint32_t address, uint32_t *indicesArr) {
    
    // Extract level indices and offset using bit masking
    indicesArr[0] = (address & outerMask) >> OUTER_TABLE; // Level 0 index
    indicesArr[1] = (address & innerMask) >> INNER_TABLE; // Level 1 index
    indicesArr[2] = address & offsetMask;         // Offset
}

// Function to generate a random 32-bit hexadecimal address
unsigned int generateRandomAddress(int i) {
    
    // Seed the random number generator
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    long long current_time_nsec = current_time.tv_sec * 1000000000LL + current_time.tv_nsec;
    
    srand(current_time_nsec);

    // Generate a random hexadecimal address
    unsigned int address = 0;
    for (int i = 0; i < 4; ++i) {
        address <<= 4; // Shift left by 4 bits
        address |= rand() % 16; // Generate a random nibble (4-bit hexadecimal digit)
    }

    return address;
}

uint32_t* getRandomPages(int numPages) {
    uint32_t* requestedPages = (uint32_t*)malloc(numPages*sizeof(uint32_t));

    for (int i = 0; i < numPages; i++) {
        requestedPages[i] = generateRandomAddress(i);
        // sleep(1);
    }
    return requestedPages;
}

//TODO: COMMENT OUT AFTER TESTING
// int main() {
//     // Generate a random address
//     unsigned int address;

//     uint32_t indicesArr[3]; // Array to store level indices and offset
    
//     for (int i = 0; i < 5; i++) {
// 	    address = generateRandomAddress();

// 	    // Extract level indices and offset from the address
//     	getIndices(address, indicesArr);

//         // Print the random address in hexadecimal format
//         printf("Random Address: 0x%04X\n", address);
// 	    // Print the results
//     	printf("OUTER_TABLE index: (hex) 0x%02X (dec) %lu\n", indicesArr[0], (unsigned long)indicesArr[0]);
//     	printf("PAGE NUMBER: (hex) 0x%02X (dec) %lu\n", indicesArr[1], (unsigned long)indicesArr[1]);
//     	printf("Offset: (hex) 0x%02X (dec) %lu\n", indicesArr[2], (unsigned long)indicesArr[2]);
// 	sleep(1);
//     }
//     return 0;
// }
