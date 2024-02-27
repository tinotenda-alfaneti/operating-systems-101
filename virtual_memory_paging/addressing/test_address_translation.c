// #include <stdio.h>
// #include <stdint.h>

// /* demo of bit masking and shifting */
// int main(int argc, char **argv) {

//   uint32_t Page;
//   uint32_t offset;
  
//   /* Suppose that we have a three level page table:
//    * Level 0:  8 bits, mask: 0xFF000000, shift: 24
//    * Level 1:  8 bits, mask: 0x00FF0000, shift: 16
//    * Level 2:  8 bits, mask: 0x0000FF00, shift: 8
//    * {0xFF000000, 0x00FF0000, 0x0000FF00}
//    * {24, 16, 8}
//    * offset is 32 - (8 + 8 + 8) = 8 bits
//    * {0x000000FF}
//    * page size is 2^8 = 255 bytes
//    */

//   int Address = 0xFe98f989;

//   /* Suppose we are interested in the level 1 page table index:
//    * We would have to construct a bit mask where the following bits
//    * are set:
//    *
//    * 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 
//    * 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//    * ===============================================================
//    * 1 1 1 1|1 1 1 1|0 0 0 0|0 0 0 0|0 0 0 0|0 0 0 0|0 0 0 0|0 0 0 0 
//    * or in hexadecimal:
//    *    F   |   F   |   0   |   0   |   0   |   0   |   0   |   0
//    *
//    * You will have to construct this in an algorithmic fashion, for
//    * demonstration purposes we'll just use a constant.
//    */
//   int	Mask = 0x0000FF00;
//   int offsetMask = 0x000000FF;

//   /* Note that since we stored Address as an int instead of an
//    * unsigned int, when we print in decimal we think that this is an
//    * negative number if bit 31 is set.  When printing in hexadecimal,
//    * all numbers are assumed unsigned and it won't make any
//    * difference.  (If we had declared this as an unsigned int, it
//    * would have printed as positive integer.)
//    */
//   printf("Address:\t0x%08x (%lu)\n", Address, (unsigned long)Address);

//   /* Pull out the relevant bits by bit-wise and */
//   Page = Mask & Address;
//   printf("After masking:\t0x%08x\n", Page);
//   offset = offsetMask & Address;
//   printf("After offset masking:\t0x%08x\n", offset);

//   /* Shift right by the relevant number of bits */
//   Page = Page >> 8;
//   printf("Page number = (%lu)\n", (unsigned long)Page);
//   printf("Page number = 0x%x\n", Page);
//   printf("Offset number = (%lu)\n", (unsigned long)offset);
// }
