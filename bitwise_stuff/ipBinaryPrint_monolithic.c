#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void print_bit_pattern(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
}

int main() {
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
    print_bit_pattern(ip);
    printf("\n");

    return 0;
}
