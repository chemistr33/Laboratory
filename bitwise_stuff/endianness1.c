#include <stdio.h>
#include <stdlib.h>

int machine_endianness_type() {
    unsigned short int a = 1;
    char first_byte = *((char *)&a);
    if (first_byte == 0)
        return 0;
    else if(first_byte ==1)
        return 1;
}

int main() {
    printf("Endianness of this machine ==> %d\n",
            machine_endianness_type());
return 0;
}