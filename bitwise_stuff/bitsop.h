#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BITSOP_
#define _BITSOP_

/**
 *  CSEpracticals Bitwise Assignment
 *  Ben Stocks 2023
 */

/**
 * Question 1
 */
void print_binary_nibbles(uint32_t num) {
  // Loop through the nibbles (4-bit groups) in num
  for (int i = 28; i >= 0; i -= 4) {
    // Extract the current nibble using a mask and bit shift
    uint8_t nibble = (num & (0xf << i)) >> i;

    // Print the nibble in binary
    for (int j = 3; j >= 0; j--) {
      printf("%d", (nibble & (1 << j)) >> j);
    }
    printf(" ");
  }
  printf("\n");
}

/**
 * Question 2
 */
#define SET_BIT(n, flag) (n) |= (flag)

/**
 * Question 3
 */
#define UNSET_BIT(n, flag) (n) &= ~(flag)

/**
 * Question 4
 */
#define IS_BIT_TRUE(n, flag) (n) & (flag)

/**
 * Question 5
 */
#define TOGGLE_BIT(n, flag) (n) ^= (flag)

/**
 * Question 6
 */
#define COMPLEMENT(n) (~n)

/**
 * Question 7
 */
uint8_t count_bit_set(uint32_t n) {

  uint8_t count = 0;

  for (int i = 0; i < 32; i++) {
    if (n & (1 << i)) {
      count++;
    }
  }
  return count;
}

/**
 * Question 8
 */
uint32_t rotate_bits_right(uint32_t n, uint8_t k) {
  // Mask out the bits that will be rotated out of the number
  uint32_t mask = (1 << k) - 1;
  uint32_t rotated_bits = n & mask;

  // Shift the bits in n right by k units
  n >>= k;

  // Shift the rotated bits left by (32 - k) units and OR them back into n
  n |= rotated_bits << (32 - k);

  // Return the rotated number
  return n;
}

/**
 * Question 9
 */
void print_bit_pattern_bytes(uint32_t num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 8 == 0) {
      printf(" ");
    }
  }
}
void print_ip_address_masked_asbytes(void) {
  // Prompt the user for the IP address and mask
  char input[20];
  printf("Enter IP address and mask (e.g. xxx.xxx.xxx.xxx/xx): ");
  scanf("%s", input);

  // Split the input string into IP address and mask components
  char *token = strtok(input, ".");
  uint8_t ip1 = atoi(token);
  token = strtok(NULL, ".");
  uint8_t ip2 = atoi(token);
  token = strtok(NULL, ".");
  uint8_t ip3 = atoi(token);
  token = strtok(NULL, "/");
  uint8_t ip4 = atoi(token);
  token = strtok(NULL, "\0");
  uint8_t mask = atoi(token);

  // Convert the IP address to a single uint32_t
  uint32_t ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;

  // Apply the mask to the IP address
  ip = ip & (0xffffffff << (32 - mask));

  // Print the resulting IP address in bit pattern
  printf("Resulting IP address: ");
  print_bit_pattern_bytes(ip);
  printf("\n");
}
/**
 * Question 10
 */
uint32_t extract_bits(uint32_t num, int p, int q) {
  // Create a mask of the form 111...1000...000
  uint32_t mask = ~0;
  mask = mask << (q + 1);  // set bits [q+1, 31] to 0
  mask = mask >> (31 - p); // set bits [0, p-1] to 0
  return (num & mask);     // apply the mask to the original number
}

/**
 * Question 11
 */
bool isPowerOfTwo(uint32_t n) { return (n && !(n & (n - 1))); }

#endif
