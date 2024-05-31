/**
 * @file   glue.c
 * @author Fransys
 * @path:  src/glue.c
 */
#include "glue_internal.h"

/**
 * Function Definitions
 */

// create new list
glist_t *glist_init()
{
    // null check
    glist_t *list = (glist_t *)malloc(sizeof(glist_t));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->print_fn = NULL;
    list->comp_fn = NULL;

    return list;
}

// create new node with data
gnode_t *gnode_spawn(void *data)
{
    // null check
    gnode_t *node = (gnode_t *)malloc(sizeof(gnode_t));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

// add node next, update head and tail if necessary
void glist_add_next(glist_t *list, gnode_t *base, gnode_t *newnode)
{
    // null check
    if (list == NULL || base == NULL || newnode == NULL) {
        return;
    }

    // add node
    newnode->next = base->next;
    newnode->prev = base;
    base->next = newnode;

    // update head and tail
    if (newnode->next == NULL) {
        list->tail = newnode;
    } else {
        newnode->next->prev = newnode;
    }

    // update list length
    list->length++;
}

// add node prev, update head and tail if necessary
void glist_add_prev(glist_t *list, gnode_t *base, gnode_t *newnode)
{
    // null check
    if (list == NULL || base == NULL || newnode == NULL) {
        return;
    }

    // add node
    newnode->next = base;
    newnode->prev = base->prev;
    base->prev = newnode;

    // update head and tail
    if (newnode->prev == NULL) {
        list->head = newnode;
    } else {
        newnode->prev->next = newnode;
    }

    // update list length
    list->length++;
}

// add last, update head and tail if necessary
void glist_add_last(glist_t *list, gnode_t *newnode)
{
    // null check
    if (list == NULL || newnode == NULL) {
        return;
    }

    // add node
    newnode->next = NULL;
    newnode->prev = list->tail;

    // update head and tail
    if (list->tail == NULL) {
        list->head = newnode;
    } else {
        list->tail->next = newnode;
    }

    list->tail = newnode;

    // update list length
    list->length++;
}

// add first, update head and tail if necessary
void glist_add_first(glist_t *list, gnode_t *newnode)
{
    // null check
    if (list == NULL || newnode == NULL) {
        return;
    }

    // add node
    newnode->next = list->head;
    newnode->prev = NULL;

    // update head and tail
    if (list->head == NULL) {
        list->tail = newnode;
    } else {
        list->head->prev = newnode;
    }

    list->head = newnode;

    // update list length
    list->length++;
}


// remove node, update head and tail if necessary
void glist_remove_node(glist_t *list, gnode_t *node)
{
    // null check
    if (list == NULL || node == NULL) {
        return;
    }

    // update head and tail
    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    // update list length
    list->length--;

    // free node
    free(node);
}

// remove first node, update head and tail if necessary
// wrap in free() 
gnode_t *glist_remove_first(glist_t *list)
{
    // null check
    if (list == NULL) {
        return NULL;
    }

    // get first node
    gnode_t *node = list->head;

    // check if head is valid
    if (node == NULL || node->next == NULL) {
        return NULL;
    }

    // update head and tail
    if (node->next == NULL) {
        list->tail = NULL;
    } else {
        node->next->prev = NULL;
    }

    list->head = node->next;

    // update list length
    list->length--;

    return node;
}

// remove last node, update head and tail if necessary
// wrap in free()
gnode_t *glist_remove_last(glist_t *list)
{
    // null check
    if (list == NULL) {
        return NULL;
    }

    // get last node
    gnode_t *node = list->tail;

    // check if tail is valid
    if (node == NULL || node->prev == NULL) {
        return NULL;
    }

    // update head and tail
    if (node->prev == NULL) {
        list->head = NULL;
    } else {
        node->prev->next = NULL;
    }

    list->tail = node->prev;

    // update list length
    list->length--;

    return node;
}

// delete node list, free app-specific data
void glist_delete(glist_t *list)
{
    // null check
    if (list == NULL) {
        return;
    }

    // free nodes
    gnode_t *node = list->head;
    while (node != NULL) {
        gnode_t *next = node->next;
        if (list->free_fn != NULL) {
            list->free_fn(node->data);
        }
        free(node);
        node = next;
    }

    // free list
    free(list);
}

// get length of list
unsigned int glist_length(glist_t *list)
{
    // null check
    if (list == NULL) {
        return 0;
    }

    return list->length;
}
