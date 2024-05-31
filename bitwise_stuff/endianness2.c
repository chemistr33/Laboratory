#include <endian.h>
#include <stdio.h>

int main() {
    if (__BYTE_ORDER == __LITTLE_ENDIAN) {
        printf("\nLittle-endian\n");
    } else if (__BYTE_ORDER == __BIG_ENDIAN) {
        printf("\nBig-endian\n");
    }
    return 0;
}

