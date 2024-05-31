/**
 * @file: glue_internal.h
 * @author: Fransys
 * @path: src/glue_internal.h
 */
#ifndef _GLUE_INTERNAL_H__
#define _GLUE_INTERNAL_H__
#include "../include/glue.h"

/**
 * Structure Definitions
 */
// node
struct _gnode {
    void *data;
    struct _gnode *next;
    struct _gnode *prev;
};

// list
struct _glist {
    struct _gnode *head;
    struct _gnode *tail;
    unsigned int length;
    void (*print_fn)(void *);
    int (*comp_fn)(void *, void *);
    gnode_t *(*keymatch_fn)(glist_t *, void *);
    void (*free_fn)(void *);
};

#endif // _GLUE_INTERNAL_H__