// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// // Function to generate a random 32-bit hexadecimal address
// unsigned int generateRandomAddress() {
//     // Seed the random number generator
//     srand(time(NULL));

//     // Generate a random hexadecimal address
//     unsigned int address = 0;
//     for (int i = 0; i < 8; ++i) {
//         printf("Iteration %d:\n", i + 1);
        
//         printf("Before shifting: \n");
//         printf("Decimal: %u\n", address);
//         printf("Binary : ");
//         printBinary(address);
//         printf("\nHexadecimal: 0x%08X\n", address);
        
//         address <<= 4; // Shift left by 4 bits
        
//         printf("After shifting: \n");
//         printf("Decimal: %u\n", address);
//         printf("Binary : ");
//         printBinary(address);
//         printf("\nHexadecimal: 0x%08X\n", address);

//         unsigned int nibble = rand() % 16; // Generate a random nibble (4-bit hexadecimal digit)
//         printf("Random nibble generated: 0x%X\n", nibble);
        
//         address |= nibble; // Combine with address
//         printf("After combining: \n");
//         printf("Decimal: %u\n", address);
//         printf("Binary : ");
//         printBinary(address);
//         printf("\nHexadecimal: 0x%08X\n\n", address);
//     }

//     return address;
// }

// // Function to print the binary representation of an unsigned integer
// void printBinary(unsigned int num) {
//     if (num > 1) {
//         printBinary(num / 2);
//     }
//     printf("%u", num % 2);
// }

// int main() {
//     // Generate a random address
//     unsigned int address = generateRandomAddress();

//     // Print the random address in hexadecimal format
//     printf("Final Random Address: \n");
//     printf("Decimal: %u\n", address);
//     printf("Binary : ");
//     printBinary(address);
//     printf("\nHexadecimal: 0x%08X\n", address);

//     return 0;
// }
