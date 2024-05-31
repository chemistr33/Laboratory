#ifndef _OGLIST_H_
#define _OGLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Opaque Data Structures
 */

typedef struct onode_ onode_t;
typedef struct olist_ olist_t;

/**
 * Ingeration Macros
 */

#define MAKE_NODE(node)                             \
do {                                                \
    node = (onode_t *)calloc(1, sizeof(onode_t));   \
    node->next = NULL;                              \
    node->prev = NULL;                              \
} while (0)

#define INIT_LIST(list)                             \
do {                                                \
    list = (olist_t *)calloc(1, sizeof(olist_t));   \
    list->head = NULL;                              \
    list->tail = NULL;                              \
    list->printfn = NULL;                           \
    list->freefn = NULL;                            \
    list->comparefn= NULL;                          \
    list->keyfn = NULL;                             \
    list->ctrlword = 1;                             \
} while (0)

/**
 * Traversal Macros
 */

#define TRAVERSE_FWD(list, node, temp)              \
for(node = GET_HEAD(list), temp = GET_NEXT(node);   \
    node != NULL;                                   \
    node = temp, temp = GET_NEXT(node))

#define TRAVERSE_REV(list, node, temp)              \
for(node = GET_TAIL(list), temp = GET_PREV(node);   \
    node != NULL;                                   \
    node = temp, temp = GET_PREV(node))

/**
 * Access Macros
 */

// returns pointer to library node data (app data structure)
#define GET_DATA(node) (node->data)

// returns pointer to next library node
#define GET_NEXT(node) (node->next)

// returns pointer to prev library node
#define GET_PREV(node) (node->prev)

// returns head of list
#define GET_HEAD(list) (list->head)

// returns tail of list
#define GET_TAIL(list) (list->tail)

// returns integer count of nodes in library linked list, range = [0, 65535]
#define GET_LENGTH(list)        (((list->ctrlword)>>16) &(0x0000FFFF))

// returns 1: emtpy, 0: not empty
#define IS_LIST_EMPTY(list)     ((list->ctrlword)       &(0x00000001))

// returns 1: sorted, 0: not sorted 
#define IS_LIST_SORTED(list)    ((list->ctrlword)       &(0x00000002))

// returns the address of structure housing the member
#define GET_CONTAINER(node, type, member) \
((type *)((char *)(node) - (char *)(&((type *)0)->member)))

// returns address (offset) of member within structure
#define GET_OFFSET(type, member) \
((char *)(&((type *)0)->member))

/**
 * Registration Macros
 */

#define REG_PRINTFN(list, fn) (list->printfn = fn)
#define REG_FREEFN(list, fn) (list->freefn = fn)
#define REG_COMPAREFN(list, fn) (list->comparefn = fn)
#define REG_KEYFN(list, fn) (list->keyfn = fn)

#define PURGE_REGISTRATIONS(list)                   \
do {                                                \
    list->printfn = NULL;                           \
    list->freefn = NULL;                            \
    list->comparefn = NULL;                         \
    list->keyfn = NULL;                             \
} while (0)

/**
 * Insertion Functions
 */

onode_t *push(olist_t *list, onode_t *node);
onode_t *append(olist_t *list, void *data);
onode_t *ins_after(olist_t *list, void *ref, void *data);
onode_t *ins_before(olist_t *list, void *ref, void *data);
onode_t *ins_sorted(olist_t *list, void *data, int (*comparefn)(const void *, const void *));

/**
 * Delete Functions
 */

onode_t *pop(olist_t *list);
onode_t *pop_tail(olist_t *list);
onode_t *del_node(olist_t *list, void *ref);
onode_t *free_node(olist_t *list, void *ref);
onode_t *free_list(olist_t *list);

/**
 * Search Functions
 */

onode_t *search_linear(olist_t *list, void *key, int (*comparefn)(const void *,const void *));

/**
 * Sort Functions
 */

void sort_bub(olist_t *list, int (*comparefn)(const void *,const void *));
void sort_merge(olist_t *list, int (*comparefn)(const void *,const void *));

/**
 * Helper Macros
 */



#endif