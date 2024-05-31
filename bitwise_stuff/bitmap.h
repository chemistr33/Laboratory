#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef BITMAP_H
#define BITMAP_H

/**
 * Bitmap Data Structure
 */

typedef struct bitmap_{
    char *bit_arr;
    int arr_size;
} bitmap_t;

/**
 * Bitmap iteration macro
 */
#define ITERATE_BITMAP_BEGIN(bitmap_ptr, bit_state) \
    for (int i = 0; i < (bitmap_ptr->arr_size * 8); i++) { \
        bit_state = (bitmap_ptr->bit_arr[i / 8] & (1 << (i % 8))) != 0;

#define ITERATE_BITMAP_END(bitmap_ptr, bit_state) \
    }

/**
 * API Functions
 */
bitmap_t *bitmap_create(int n_bits);
void bitmap_print(bitmap_t *bitmap);
void bitmap_set_bit(bitmap_t *bitmap, int index);
void bitmap_unset_bit(bitmap_t *bitmap, int index);
int bitmap_is_bit_set(bitmap_t *bitmap, int index);
void bitmap_clear(bitmap_t *bitmap);
void bitmap_free(bitmap_t *bitmap);

bool bitmap_is_full(bitmap_t *bitmap);



#endif