#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#ifndef _OGLIST_INTERNAL_H_
#define _OGLIST_INTERNAL_H_
#include "../include/oglist.h"

// Internal node structure definition
typedef struct onode_ {
    struct onode_ *next;
    struct onode_ *prev;
} onode_t;

// Internal list structure definition
/* 
 * b0         1 = Empty     0 = Not Empty
 * b1         1 = Sorted    0 = Not Sorted
 * b2:b15     Reserved for future use
 * b16:b31    2-byte unsigned integer for length
*/
typedef struct olist_ {
    onode_t *head;
    onode_t *tail;
    void (*printfn)(void *);
    void (*freefn)(void *);
    int (*comparefn)(void *, void *);
    onode_t *(*keyfn)(void *);
    uint32_t ctrlword;
} olist_t;

#endif

