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

/* Internal list structure definition
 * b0         1 = Empty     0 = Not Empty
 * b1         1 = Sorted    0 = Not Sorted
 * b2:b15     Reserved for future use
 * b16:b31    2-byte unsigned integer for length */
typedef struct olist_ {
    onode_t *head;
    onode_t *tail;
    void (*printfn)(void *);
    void (*freefn)(void *);
    int (*comparefn)(void *, void *);
    onode_t *(*keyfn)(void *);
    uint32_t ctrlword;
} olist_t;

// Opaque list initialization function
inline void init_list(olist_t **list); 

/**
 * Access Functions
 */

// // returns pointer to library node data (app data structure)
// #define GET_DATA(node) (node->data)

// returns pointer to list head
onode_t **get_head(olist_t *list);

// returns pointer to list tail
inline onode_t *get_tail(olist_t *list);

// returns pointer to next library node
inline onode_t *get_next(onode_t *node);

// returns pointer to prev library node
inline onode_t *get_prev(onode_t *node);

// returns integer count of nodes in library linked list, range = [0, 65535]
inline int get_length(olist_t *list);

// increments list count by 1
void inc_list(olist_t *list);

// decrements list count by 1
void dec_list(olist_t *list);

// unset flag b0 to 0 for not-empty
void list_not_empty(olist_t *list);

// returns 1: empty, 0: not empty
#define IS_LIST_EMPTY(list)     ((list->ctrlword)&(0x00000001))

// returns 1: sorted, 0: not sorted 
#define IS_LIST_SORTED(list)    ((list->ctrlword)&(0x00000002))

// returns the address of structure housing the member
#define GET_CONTAINER(node, type, member) \
((type *)((char *)(node) - (char *)(&((type *)0)->member)))

// returns address (offset) of member within structure
#define GET_OFFSET(type, member) \
((char *)(&((type *)0)->member))


#endif

