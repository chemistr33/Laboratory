/**
 *@file _ogbase.c
 *@brief Base functions for the ogbase library 
 *@path oglist/src/_ogbase.c
 */
#include "oglist_internal.h"

/**
 * Insert Functions
 */


onode_t *ins_head(olist_t *list, onode_t **node) {
    // return if list or node is null
    if(!list || !node || (*node) != NULL) {
        return NULL;
    } 
    //  case 0 - list is empty
    if(IS_LIST_EMPTY(list))
    {
        list->head = (*node);
        list->tail = (*node);
        LIST_NOT_EMPTY(list);        
        INC_LIST(list);
        return (*node);
    }
    //  case 1 - list is not empty
    else {
        (*node)->next = list->head;
        list->head->prev = (*node);
        list->head = (*node);
        INC_LIST(list);
        return (*node);
    }
}



onode_t *ins_tail(olist_t *list, onode_t *node) {
    // return if list or node is null
    if (!list || !node){
        return NULL;
    }
    // case 0 - list is empty
    if (IS_LIST_EMPTY(list)) {
        list->tail = node;
        list->head = node;
        LIST_NOT_EMPTY(list);
        INC_LIST(list);
        return node;
    }
    // case 1 - list not empty
    else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        INC_LIST(list);
        return node;
    }
}

onode_t *ins_after(olist_t *list, onode_t *ref, onode_t *node){
    // return if list or node is null
    if (!list || !ref || !node){
        return NULL;
    } 
    // case 0 - ref has next pointer 
    if(ref->next){
        node->next = ref->next;
        node->prev = ref;
        ref->next->prev = node;
        ref->next = node;
        INC_LIST(list);
        return node;
    } 
    // case 1 - ref has null next pointer (ref is tail pointer)
    else {
        node->prev = ref;
        ref->next = node;
        list->tail = node;
        INC_LIST(list);
        return node;
    }
}

onode_t *ins_before(olist_t *list, onode_t *ref, onode_t *node){
    // return if list, ref, or node is null
    if (!list || !ref || !node){
        return NULL;
    }
    // case 0 - ref has prev pointer
    if(ref->prev){
        node->prev = ref->prev;
        node->next = ref;
        ref->prev->next = node;
        ref->prev = node;
        INC_LIST(list);
        return node;
    }
    // case 1 - ref has null prev pointer (ref is head pointer)
    else {
        node->next = ref;
        ref->prev = node;
        list->head = node;
        INC_LIST(list);
        return node;
    }
}

onode_t *ins_sorted(olist_t *list,
                    onode_t **node,
                    int (*comparefn)(const void *, const void *))
{
    // return if list, node, or callback is null
    if(!list || !node || !comparefn){
        return NULL;
    }    
    // case 0 - list is empty
    if (IS_LIST_EMPTY(list)){
        return ins_head(list, (node));
    }
    // case 1 - traverse list for correct position
    onode_t *curr, *tmp;
    TRAVERSE_FWD(list, curr, tmp){
        
        int comparison = comparefn(node, curr);
        
        if(comparison<0){
            return ins_before(list, node, curr);
        }
    }
    // case 2 - insert at tail
    return ins_tail(list, node);
}

/**
 * deletion functions
 */

onode_t *pop_head(olist_t *list){
    // return if list or head is null
    if(!list || !list->head || !list->tail){
        return NULL;
    }
    
    onode_t *capture_pop = list->head;
    // case 0 - list has only one node
    if(!list->head->next){
        list->head = NULL;
        list->tail = NULL;
    }
    // case 1 - list has more than one node
    else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    
    capture_pop->next = NULL;
    DEC_LIST(list);
    return capture_pop;
}

onode_t *pop_tail(olist_t *list){
    // return if list or head is null
    if(!list || !list->head || !list->tail){
        return NULL;
    }
    
    onode_t *capture_pop = list->tail;
    // case 0 - list has only one node
    if(list->head == list->tail){
        list->tail = NULL;
        list->head = NULL;
    }
    // case 1 - list has more than one node
    else {
       list->tail = list->tail->prev;
       list->tail->next = NULL;
    }

    capture_pop->prev = NULL;
    DEC_LIST(list);
    return capture_pop;
}

onode_t *pop_node(olist_t *list, onode_t *node){
    // return if list or node is null
    if(!list || !node){
        return NULL;
    }

    // case 0 - list has only one node
    if(!list->head->next){
        return pop_head(list);
    }

    // case 1 - node is head
    if(list->head == node){
        return pop_head(list);
    }
    // case 2 - node is tail
    if(list->tail == node){
        return pop_tail(list);
    }
    
    // case 3 - list has more than one node, node is non-terminal node
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = NULL;
    node->prev = NULL;
    DEC_LIST(list);
 return node;
}

void free_node(olist_t *list, onode_t *node){
    // return if list or node is null
    if(!list || !node){
        return;
    }

    // case 0 - free function was registered by user
    if(list->freefn){
        list->freefn(node);
    }
    // case 1 - no free function was registered by user
    else {
        free(node);
    }
}

void free_list(olist_t *list){
    // return if list or node is null
    if(!list)
        return;
    
    onode_t *curr;
    // traverse list free'ing nodes
    TRAVERSE_FWD(list, list->head, curr){
        free_node(list,curr);
    }

    // free the list itself
    free(list);
}

inline void reg_printfn(olist_t *list, void (*printfn)(void *)){
    if(list == NULL){
        return;
    }else{list->printfn = printfn;}
}

inline void reg_freefn(olist_t *list, void (*freefn)(void *)){
    list->freefn = freefn;
}

inline void reg_comparefn(olist_t *list, int (*comparefn)(void *, void *)){
    list->comparefn = comparefn;
}

inline void reg_keyfn(olist_t *list, onode_t *(*keyfn)(void *key)){
    list->keyfn = keyfn;
}

// returns pointer to list head
onode_t **get_head(olist_t *list){
    if(!list){
        puts("No list!\n");
        return NULL;
    }
    return &(list->head);
}

// returns pointer to list tail
onode_t *get_tail(olist_t *list){
    if(!list)
        return NULL;

    return list->tail;
}

// returns pointer to next library node
onode_t *get_next(onode_t *node){
    if(!node)
        return NULL;

    return node->next;
}

// returns pointer to prev library node
onode_t *get_prev(onode_t *node){
    if(!node)
        return NULL;

    return node->prev;
}

// returns length of list
int get_length(olist_t *list){
return (((list->ctrlword)>>16) &(0x0000FFFF));
}


void inc_list(olist_t *list){
    do {                                                                    
    uint32_t tmp    = (list)->ctrlword;                                     
    uint32_t count  = (list)->ctrlword>>16;                                 
    assert(                                                                 
            count < UINT16_MAX &&                                           
            "List count cannot exceed 65,535 nodes in length"               
          );                                                                
    count += 1;                                                             
    tmp = ((count << 16) | (tmp & 0x0000FFFF));                             
    (list)->ctrlword = tmp;                                                 
    } while (0);
}

void dec_list(olist_t *list){
    do {                                                                    
    uint32_t tmp    = (list)->ctrlword;                                     
    uint32_t count  = (list)->ctrlword>>16;                                 
    assert(                                                                 
            count > 0 &&                                                    
            "List count cannot be less than zero"                           
          );                                                                
    count -= 1;                                                             
    tmp = ((count << 16) | (tmp & 0x0000FFFF));                             
    (list)->ctrlword = tmp;                                                 
    } while (0);
}

void list_not_empty(olist_t *list){
    do {                                                
    uint32_t value   = (list)->ctrlword;                
    uint32_t nth_bit = 0;                               
    value &= ~(1 << nth_bit);                           
    } while(0);
}

inline void init_list(olist_t **list)
{                             
   *list = (olist_t *)calloc(1, sizeof(olist_t));   
   (*list)->head = NULL;                              
   (*list)->tail = NULL;                              
   (*list)->printfn = NULL;                           
   (*list)->freefn = NULL;                            
   (*list)->comparefn= NULL;                          
   (*list)->keyfn = NULL;                             
   (*list)->ctrlword = 1;
}
