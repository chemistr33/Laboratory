/**
 * intrusive.h - intrusive linked list implementation
 */
#ifndef __INTRUSIVE_H____
#define __INTRUSIVE_H____

// the usual suspects...
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/**
 * node structure
 */

typedef struct node_ {
    struct node_ *next;
    struct node_ *prev;
} node_t;


// Placeholder for user's custom data type
typedef struct {
    node_t node;
} app_data_placeholder_t;

/**
 * list structure
 */

typedef struct list_ {
    node_t *head;
    node_t *tail;
    unsigned int length;
    void (*freefn)(void *data);
    int (*compfn)(const void *key1, const void *key2);
    void (*printfn)(const void *data);
} list_t;

/**
 * initialization function
 */

// list_init - initialize a list
// @list:   list to be initialized
// @freefn: function to free the data
// @compfn: function to compare the data
// @printfn: function to print the data
void list_init( 
                list_t *list,
                void (*freefn)(void *data),
                int (*compfn)(const void *key1, const void *key2),
                void (*printfn)(const void *data)
              );
/**
 * macros
 */

// container_of - get the container of a node
// @ptr: pointer to the node
// @type: type of the container
// @member: name of the node in the container
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

/**
 * registration functions
 */

// reg_freefn - register a free function for the list
// @list: list to register the free function
// @freefn: function to free the data
void reg_freefn(list_t *list, void (*freefn)(void *data));

// reg_compfn - register a compare function for the list
// @list: list to register the compare function
// @compfn: function to compare the data
void reg_compfn(list_t *list, int (*compfn)(const void *key1, const void *key2));

// reg_printfn - register a print function for the list
// @list: list to register the print function
// @printfn: function to print the data
void reg_printfn(list_t *list, void (*printfn)(const void *data));

/**
 * access functions
 */

// list_head - get the head of the list
// @list: list to get the head
// @return: head of the list
node_t *list_head(list_t *list);

// list_tail - get the tail of the list
// @list: list to get the tail
// @return: tail of the list
node_t *list_tail(list_t *list);

// list_length - get the length of the list
// @list: list to get the length
// @return: length of the list
unsigned int list_length(list_t *list);


/**
 * insertion functions
 */

// ins_head - insert a new node at the head of the list
// @list: list to insert the node
// @node: node to be inserted
void ins_head(list_t *list, node_t *node);

// ins_tail - insert a new node at the tail of the list
// @list: list to insert the node
// @node: node to be inserted
void ins_tail(list_t *list, node_t *node);


//###################################################################
void ins_after(list_t *list, node_t *ref, node_t *node);


//###################################################################
void ins_before(list_t *list, node_t *ref, node_t *node);

// ins_sorted - insert a new node in sorted order
// @list: list to insert the node
// @node: node to be inserted
// @typename: name of the user-defined structure, use quotes around "typename"
void ins_sorted(list_t *list, node_t *node);

/**
 * deletion functions
 */

// pop_head - delete the head of the list
// @list: list to delete the head
// @return: head of the list
// note: does not free the node
node_t *pop_head(list_t *list);

// pop_tail - delete the tail of the list
// @list: list to delete the tail
// @return: tail of the list
// note: does not free the node
node_t *pop_tail(list_t *list);

// pop_node - delete the given node
// @list: list to delete the node
// @node: node to be deleted
// note: does not free the node
void pop_node(list_t *list, node_t *node);

// free_node - free the given node
// @list: list to free the node
// @node: node to be freed
// note: this function must be used with _safe traversal macros!
void free_node(list_t *list, node_t *node);

// free_list - free the list
// @list: list to be freed
void free_list(list_t *list);

/**
 * traversal macros 
 */

// intrusive_for_each - iterate over a list
// @pos:  user-defined structure to use as a loop cursor 
// @list: list_t structure to iterate over
// @member: name of the node_t meber within the user-defined structure
#define intrusive_for_each(pos, list, member) \
    for (pos = container_of((list)->head, typeof(*pos), member); \
        &((pos)->member) != NULL; \
         pos = container_of(pos->member.next, typeof(*pos), member))

// intrusive_for_each_safe - iterate over a list safe against removal of list entry
// @pos:  user-defined structure to use as a loop cursor
// @temp: another user-defined structure to use as temporary storage
// @list: list_t structure to iterate over
// @member: name of the node_t member within the user-defined structure
// #define intrusive_for_each_safe(pos, temp, list, member) \
//     for (pos = container_of((list)->head, typeof(*pos), member), \
//          temp = container_of(pos->member.next, typeof(*pos), member); \
//          &pos->member != (list)->tail; \
//          pos = temp, temp = container_of(temp->member.next, typeof(*temp), member))

// intrusive_for_each_reverse - iterate backwards over a list
// @pos:  user-defined structure to use as a loop cursor
// @list: list_t structure to iterate over
// @member: name of the node_t member within the user-defined structure
#define intrusive_for_each_reverse(pos, list, member) \
    for (pos = container_of((list)->tail, typeof(*pos), member); \
         &pos->member != NULL; \
         pos = container_of(pos->member.prev, typeof(*pos), member))
// (list)->head; 
// intrusive_for_each_reverse_safe - iterate backwards over a list safe against removal of list entry
// @pos:  user-defined structure to use as a loop cursor
// @temp: another user-defined structure to use as temporary storage
// @list: list_t structure to iterate over
// @member: name of the node_t member within the user-defined structure
#define intrusive_for_each_reverse_safe(pos, temp, list, member) \
    for (pos = container_of((list)->tail, typeof(*pos), member), \
         temp = container_of(pos->member.prev, typeof(*pos), member); \
         &pos->member != (list)->head; \
         pos = temp, temp = container_of(temp->member.prev, typeof(*temp), member))

/**
 * search functions
 */

// linear_search - search for a node in the list
// @list: list to search
// @key: key to search for
// @return: node if found, NULL otherwise
node_t *linear_search(list_t *list, const void *key);

// binary_search - search for a node in the list
// @list: list to search
// @key: key to search for
// @return: node if found, NULL otherwise
node_t *binary_search(list_t *list, const void *key);

/**
 * sort functions
 */

// bubble_sort - sort the list using bubble sort
// @list: list to sort
void bubble_sort(list_t *list);

// // merge_sort - sort the list using merge sort
// // @list: list to sort
// inline void merge_sort(list_t *list);

#endif