#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Stream aka Serialized Buffer
 */
typedef struct serialized_buffer{
    char *b;
    int size;
    int next;
} ser_buff_t;

// Default size of the buffer
#define BUFFER_DEFAULT_SIZE 1024

/**
 * Initialize the buffer
 * @param b , buffer to be initialized
 * @return  , void
 * @note    , This function will allocate memory for the buffer
 *            and initialize it. */ 
void init_serialized_buffer (ser_buff_t **b){
    (*b) = (ser_buff_t *)calloc(1, sizeof(ser_buff_t));
    (*b)->b = calloc(1, BUFFER_DEFAULT_SIZE);
    (*b)->size = BUFFER_DEFAULT_SIZE;
    (*b)->next = 0;
}

void serialize_data(ser_buff_t *buff, char *data, int nbytes){
    
    int available_bytes = buff->size - buff->next;
    char isResize = 'n';

    // If buffer isn't big enough to hold the data, resize it.
    while(available_bytes < nbytes){
        buff->size *= 2;
        available_bytes = buff->size - buff->next;
        isResize = 'y';
    }

    // If buffer is big enough, copy the data and return.
    if(isResize == 'n'){
        memcpy((char *)buff->b + buff->next, data, nbytes);
        buff->next += nbytes;
        return;
    }

    // If buffer isn't big enough, resize it and copy the data.
    buff->b = realloc(buff->b, buff->size);
    memcpy((char *)buff->b + buff->next, data, nbytes);
    buff->next += nbytes;
    return;

}

void de_serialize_data(char *dest, ser_buff_t *buff, int size){
    memcpy(dest, (char *)buff->b + buff->next, size);
    buff->next += size;
}








int main() {


    return 0;
}