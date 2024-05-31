#include "bitsop.h"
#include <stdint.h>

extern void print_binary_nibbles(uint32_t num); 
extern uint8_t count_bit_set(uint32_t n);
extern uint32_t rotate_bits_right(uint32_t n, uint8_t k);
extern void print_ip_address_masked_asbytes(void);
extern void print_bit_pattern_bytes(uint32_t num);
int main(){

system("clear");
uint32_t var = 41;

print_binary_nibbles(var);
printf("%d is the number of set bits.\n",count_bit_set(var));
puts("");
var = rotate_bits_right(var, 4);
printf("After rotating right by 4 positions, var equals:\n");
print_binary_nibbles(var);
puts("####################################################");
print_ip_address_masked_asbytes();
return 0;
}