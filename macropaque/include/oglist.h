#ifndef _OGLIST_H_
#define _OGLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/**
 * Opaque Data Structures
 */

typedef struct onode_ onode_t;
typedef struct olist_ olist_t;

/**
 * Ingeration Macros
 */

void init_list(olist_t **);
#define INIT_LIST(list) init_list(&list)                            

/**
 * Traversal Macros
 */

#define TRAVERSE_FWD(list, node, temp) \
    for ((node) = GET_HEAD(list), (temp) = ((node) != NULL) ? GET_NEXT(node) : NULL; \
         (node) != NULL; \
         (node) = (temp), (temp) = ((temp) != NULL) ? GET_NEXT(temp) : NULL)

/**
 * Access Macros
 */
// returns pointer to list head 
onode_t **get_head(olist_t *list);
#define GET_HEAD(list) (*(get_head(list)))

// returns pointer to list tail 
onode_t *get_tail(olist_t *list);
#define GET_TAIL(list) (get_tail(list))

// returns pointer to next library node
onode_t *get_next(onode_t *node);
#define GET_NEXT(node) (get_next(node))

// returns pointer to prev library node
onode_t *get_prev(onode_t *node);
#define GET_PREV(node) (get_prev(node))

// returns integer length of list
int get_length(olist_t *list);
#define GET_LENGTH(list) (get_length(list))

// increments list count by one
#define INC_LIST(list)  (inc_list(list))

// decrements list count by 1
#define DEC_LIST(list)  (dec_list(list))

// set list to not-empty
#define LIST_NOT_EMPTY(list) (list_not_empty(list))

/**
 * Registration Macros
 */
#define REG_PRINTFN(list, fn) reg_printfn(list,fn)
void reg_printfn(olist_t *list, void (*printfn)(void *));

void reg_freefn(olist_t *list, void (*freefn)(void *));
#define REG_FREEFN(list, fn) reg_freefn(list, fn)

void reg_comparefn(olist_t *list, int(*comparefn)(void *, void *));
#define REG_COMPAREFN(list, fn) reg_comparefn(list, fn)

void reg_keyfn(olist_t *list, onode_t *(*keyfn)(void *key));
#define REG_KEYFN(list, fn) reg_keyfn(list, fn)

/**
 * Insertion Functions
 */

onode_t *ins_head(olist_t *list, onode_t **node);
onode_t *ins_tail(olist_t *list, onode_t *node);
onode_t *ins_after(olist_t *list, onode_t *ref, onode_t *node);
onode_t *ins_before(olist_t *list, onode_t *ref, onode_t *node);
onode_t *ins_sorted(olist_t *list, onode_t **node,
                    int (*comparefn)(const void *, const void *));

/**
 * Deletion Functions
 */

onode_t *pop_head(olist_t *list);
onode_t *pop_tail(olist_t *list);
onode_t *pop_node(olist_t *list, onode_t *node);
void free_node(olist_t *list, onode_t *node);
void free_list(olist_t *list);

/**
 * Search Functions
 */

onode_t *search_linear(olist_t *list, void *key, int (*comparefn)(const void *,const void *));

/**
 * Sort Functions
 */

void sort_bub(olist_t *list, int (*comparefn)(const void *,const void *));
void sort_merge(olist_t *list, int (*comparefn)(const void *,const void *));

#endif

