/**
 * @file   glue2.c
 * @author Fransys
 * @path:  src/glue2.c
 */
#include "glue_internal.h" 
#include "../include/glue.h"

// print list status
void glist_status(glist_t * list)
{
    // null check
    if (list == NULL) {
        printf("List: NULL\n");
        return;
    }
    // print member data
    printf("--------------------\n"); 
    printf("Head: %p\n", list->head);
    printf("Tail: %p\n", list->tail);
    printf("print_fn: %p\n", list->print_fn);
    printf("comp_fn: %p\n", list->comp_fn);
    printf("keymatch_fn: %p\n", list->keymatch_fn);
    printf("Length: %u\n", list->length);
    printf("--------------------\n"); 
}

// register comparison function
void glist_register_comp_fn(glist_t *list, int (*comp_fn)(void * , void *))
{
    // null check
    if (list == NULL || comp_fn == NULL) {
        return;
    }

    list->comp_fn = comp_fn;
}

// sort list
void glist_sort(glist_t *list)
{
    
}


// insert node into list in order, update head and tail if necessary
// assumes list is sorted
void glist_priority_insert( glist_t *list, 
                            gnode_t *newnode, 
                            int (*comp_fn)(void * , void *))
{

}

// register keymatch search function
void glist_register_keymatch_fn(glist_t *list, gnode_t *(*keymatch_fn)(glist_t *, void *))
{
    // null check
    if (list == NULL || keymatch_fn == NULL) {
        return;
    }

    list->keymatch_fn = keymatch_fn;
}

// search list for node with matching key
// returns node if found, NULL if not found
gnode_t *glist_keymatch_search(glist_t *list, void *key)
{

}


// register print function
void glist_register_print_fn(glist_t *list, void (*print_fn)(void *))
{
    // null check
    if (list == NULL || print_fn == NULL) {
        return;
    }

    list->print_fn = print_fn;
}

// print node data
void gnode_print(glist_t *list, gnode_t *node)
{
}

// register free function
void glist_register_free_fn(glist_t *list, void (*free_fn)(void *))
{
    // null check
    if (list == NULL || free_fn == NULL) {
        return;
    }

    list->free_fn = free_fn;
}




#if 0
// helper macro for use in the loop 
#define BASE(nodeptr) ((nodeptr)->next) 

// place code between these two macros to iterate through a list
// in practice you'll have already made a temp pointer named curr for `nodeptr`

#define ITERATE_NODES_BEGIN(lstptr, struct_type, ptr) \
{                                                     \
    gnode_t *_gnode = NULL, *_next = NULL;            \
    for(_gnode = BASE(lstptr); _gnode; _gnode = _next)\
    {                                                 \
        _next = _gnode->next;                         \
        ptr = CONTAINER_OF(_gnode, struct_type, node);

#define ITERATE_NODES_END }} 
#endif


