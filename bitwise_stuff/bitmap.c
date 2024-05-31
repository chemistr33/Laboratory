#include "bitmap.h"
#include <limits.h>
#include <string.h>

/**
 * @ passes n_bits for the desired bit-width of the array
 * @ returns a pointer to the array
 * Description:
 * The bitmap structure pointer is allocated with malloc
 * The array size is always one byte larger than the number,
 * of bits requested, hence (n+7)/8.
 * Once calculated, the bitmap->bit_arr is allocated and initialized,
 * using calloc.
 */
bitmap_t *bitmap_create(int n_bits){
    bitmap_t *bitmap = (bitmap_t *)malloc(sizeof(bitmap_t));
    bitmap->arr_size = (n_bits + 7) / 8;
    bitmap->bit_arr = (char *)calloc(bitmap->arr_size, sizeof(char));
    return bitmap;
}

/**
 * Sets up a for-loop, that iterates through the number of bits,
 * calculated as bytes * 8 = bits. Note the unused extra bits at,
 * the end that may be unused/underutilized. Calloc left those,
 * zero earlier.
 */
void bitmap_print(bitmap_t *bitmap){
    for(int i = 0; i < bitmap->arr_size * 8; i++){
        printf("%d", (bitmap->bit_arr[i / 8] >> (i % 8)) & 1);
    }
    printf("\n");
}

void bitmap_set_bit(bitmap_t *bitmap, int index){
    bitmap->bit_arr[index/8] |= 1 << (index % 8);
}

void bitmap_unset_bit(bitmap_t *bitmap, int index){
    bitmap->bit_arr[index/8] &= ~(1 << (index % 8));
}

int bitmap_is_bit_set(bitmap_t *bitmap, int index) {
    return (bitmap->bit_arr[index / 8] >> (index % 8)) & 1;
}

void bitmap_clear(bitmap_t *bitmap){
    memset(bitmap->bit_arr, 0, bitmap->arr_size);
}

void bitmap_free(bitmap_t *bitmap){
    free(bitmap->bit_arr);
    free(bitmap);
}

bool bitmap_is_full(bitmap_t *bitmap) {
    if (!bitmap) {
        printf("Null bitmap pointer. exiting...\n");
        return false;
    }
    for (int i = 0; i < bitmap->arr_size; i++) {
        if (~bitmap->bit_arr[i]) {
          return false;
        }
    }
    return true;
}

bool bitmap_pattern_match(bitmap_t *bitmap, 
                          char *binary_string, 
                          int n_bits,
                          int *i) {
    int j, k;
    for (*i = 0; *i <= bitmap->arr_size * 8 - n_bits; (*i)++) {
        for (j = 0, k = *i; j < n_bits; j++, k++) {
            if ((bitmap->bit_arr[k / 8] & (1 << (k % 8))) != (binary_string[j] - '0')) {
                break;
            }
        }
        if (j == n_bits) {
            return true;
        }
    }
    return false;
}

/**
 * MSB-first bitmap version
 */
#if 0
bool bitmap_pattern_match(bitmap_t *bitmap, char *binary_string, int n_bits, int *i) {
    int j, k;
    for (*i = bitmap->arr_size * 8 - n_bits; *i >= 0; (*i)--) {
        for (j = 0, k = *i; j < n_bits; j++, k++) {
            if ((bitmap->bit_arr[k / 8] & (1 << (7 - k % 8))) != (binary_string[j] - '0')) {
                break;
            }
        }
        if (j == n_bits) {
            return true;
        }
    }
    return false;
}
#endif 
