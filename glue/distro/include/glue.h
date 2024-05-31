/*!
 * @file:   glue.h
 * @author: Fransys 
 * @path:   include/glue.h
 * -> "Glue-Style" doubly-linked list implementation.
 * -> Inspired by the linux kernel list implementation.
 * -> Featuring opaque structures and macros.
 */
#ifndef _GLUE__
#define _GLUE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Opaque Structure Definitions
 */

// Node
typedef struct _gnode gnode_t;

// List
typedef struct _glist glist_t;

/**
 * Function Prototypes
 */

// create new list
glist_t *glist_init();

// create new node
gnode_t *gnode_spawn(void *data);

// add node next
void glist_add_next(glist_t *list, gnode_t *base, gnode_t *newnode);

// add node prev
void glist_add_prev(glist_t *list, gnode_t *base, gnode_t *newnode);

// remove node
void glist_remove_node(glist_t *list, gnode_t *node);

// remove first node
gnode_t *glist_remove_first(glist_t *list);

// remove last node
gnode_t *glist_remove_last(glist_t *list);

// add last
void glist_add_last(glist_t *list, gnode_t *newnode);

// add first
void glist_add_first(glist_t *list, gnode_t *newnode);

// delete node list
void glist_delete(glist_t *list);

// get list count
unsigned int glist_length(glist_t *list);

// insert node into list in order
void glist_priority_insert( glist_t *list, 
                            gnode_t *newnode, 
                            int (*comp_fn)(void * , void *));

// register comparison function
void glist_register_compare_fn(glist_t *list, int (*comp_fn)(void * , void *));

// register keymatch search function
void glist_register_keymatch_fn(glist_t *list, gnode_t *(*keymatch_fn)(glist_t *, void *));

// keymatch search function
gnode_t *glist_keymatch_search(glist_t *list, void *key);

// print node data
void gnode_print(glist_t *, gnode_t *node);

// print list data
void glist_print(glist_t *list);

// register print function
void glist_register_print_fn(glist_t *list, void (*print_fn)(void *));

// register free function
void glist_register_free_fn(glist_t *list, void (*free_fn)(void *));

// print list structure member data: hex address of head, tail, callback functions, and int length
void glist_status(glist_t *list);

/**
 * Macro Definitions
 */

// empty list check macro
// returns 1 if empty, 0 if not
#define IS_LIST_EMPTY(nodeptr) \
    (((nodeptr)->next == 0) && ((nodeptr->prev == 0)))

// node exists macro
// returns 1 if exists, 0 if not
#define IS_NODE_IN_LIST(nodeptr) \
    (((nodeptr)->next != 0) && ((nodeptr)->prev != 0))

// offset of macro
// returns offset of member in structure
#define OFFSET_OF(structure_name, member) ((size_t) &((structure_name *)0)->member);

// member of macro
// returns pointer to structure containing member
#define CONTAINER_OF(fn_name, structure_name, field_name)                               \
    static inline structure_name *fn_name(gnode_t *node)                                \
    {                                                                                   \
        return (structure_name *)((char *)node - OFFSETOF(structure_name, field_name)); \
    }

// get data from node using offset
// returns pointer to data
#define GET_DATA_FROM_OFFSET(nodeptr, offset) \
(void *) ((char *)nodeptr - offset);

////////////////////////////
/* delete-safe loop macro */
////////////////////////////

// helper macro for use in the loop 
#define BASE(nodeptr) ((nodeptr)->next) 

// place code between these two macros to iterate through a list
// in practice you'll have already made a temp pointer named curr for `nodeptr`
#define ITERATE_NODES_BEGIN(nodestart, nodeptr) \
    gnode_t *_nodeptr = NULL;                   \
    nodeptr = BASE(nodestart);                  \
    for(; nodeptr != NULL; nodeptr = _nodeptr)  \
    {                                           \
        _nodeptr = nodeptr->next;               

// closes loop
#define ITERATE_NODES_END(nodestart, nodeptr) }

#endif