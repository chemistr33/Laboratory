/**
 * @file   glue2.c
 * @author B3n
 * -> Implementation hidden here behind "compiler firewall"
 * -> Contains hidden structure definitions
 */
#include "glue.h"
#include "glue.c"

// insert node into list in order
void glist_priority_insert( glist_t *list, 
                            gnode_t *newnode, 
                            int (*comp_fn)(void * , void *))
{
    // null check
    if (list == NULL || newnode == NULL) {
        return;
    }

    // empty list
    if (list->head == NULL) {
        list->head = newnode;
        list->tail = newnode;
        list->length++;
        return;
    }

    // insert at head
    if (comp_fn(newnode->data, list->head->data) < 0) {
        newnode->next = list->head;
        list->head->prev = newnode;
        list->head = newnode;
        list->length++;
        return;
    }

    // insert at tail
    if (comp_fn(newnode->data, list->tail->data) > 0) {
        newnode->prev = list->tail;
        list->tail->next = newnode;
        list->tail = newnode;
        list->length++;
        return;
    }

    // insert in middle
    gnode_t *curr = list->head;
    while (curr != NULL) {
        if (comp_fn(newnode->data, curr->data) < 0) {
            newnode->next = curr;
            newnode->prev = curr->prev;
            curr->prev->next = newnode;
            curr->prev = newnode;
            list->length++;
            return;
        }
        curr = curr->next;
    }
}



#if 0
// insert node into list in order
void glist_priority_insert( glist_t *list, 
                            gnode_t *newnode, 
                            int (*comp_fn)(void * , void *));

// register compare function
void glist_register_compare_fn(glist_t *list, int (*comp_fn)(void * , void *));

// keymatch search function
gnode_t *glist_keymatch_search(glist_t *list, void *key, int (*comp_fn)(void *, void *));

// print node data
void gnode_print(gnode_t *node, void (*print_fn)(void *));

// print list data
void glist_print(glist_t *list, void (*print_fn)(void *));

// register print function
void glist_register_print_fn(glist_t *list, void (*print_fn)(void *));

// register free function
void glist_register_free_fn(glist_t *list, void (*free_fn)(void *));

/**
 * Macro Definitions
 */

// empty list check macro
// returns 1 if empty, 0 if not
#define IS_LIST_EMPTY(nodeptr) \
    (((nodeptr)->next == 0) && ((nodeptr->prev == 0)));

// node exists macro
// returns 1 if exists, 0 if not
#define IS_NODE_IN_LIST(nodeptr) \
    (((nodeptr)->next != 0) && ((nodeptr)->prev != 0));

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
#define ITERATE_NODES_END(nodestart, nodeptr) }}

////////////////////////////

#endif
