/**
 *@file _ogbase.c
 *@brief Base functions for the ogbase library 
 *@path oglist/src/_ogbase.c
 */
#include "oglist_internal.h"

/**
 * Insert Functions
 */

onode_t *push(olist_t *list, onode_t *node){

//  auto variable(s) 
    onode_t *_newnode;

//  null check
    if(!(list||node)){ return 0; }

//  case: empty list
    if(IS_LIST_EMPTY(list)){
        list->head = node;
        list->tail = node;
        
    }



}





