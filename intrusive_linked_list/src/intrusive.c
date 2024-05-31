#include "../inc/intrusive.h"
/**
 * Null-Check Macro
 */

// null check for fcts returning void
#define NULL_CHECK(ptr) if(ptr == NULL) return;

// null check for fcts returning non-void
#define NULL_CHECK_RET(ptr, ret) if(ptr == NULL) return ret;

/**
 * initialization function definition
 */

// initializes a list_t structure
// list: pointer to the list_t structure to initialize
// freefn: pointer to a function that frees the data of a node
// compfn: pointer to a function that compares two keys
// printfn: pointer to a function that prints the data of a node
// note: if freefn, compfn, or printfn are not needed, pass NULL
void list_init(list_t *list,
                      void (*freefn)(void *data),
                      int (*compfn)(const void *key1, const void *key2),
                      void (*printfn)(const void *data))
{
    list->head = NULL;
    list->tail = NULL;
    list->freefn = freefn;
    list->compfn = compfn;
    list->printfn = printfn;
}                      

/**'
 * registration function definitions
 */

// registers a function to free the data of a node
void reg_freefn(list_t *list, void (*freefn)(void *data)){
    NULL_CHECK(list);
    NULL_CHECK(freefn);
    list->freefn = freefn;
}
// registers a function to compare two keys
void reg_compfn(list_t *list, int (*compfn)(const void *key1, const void *key2)){
    NULL_CHECK(list);
    NULL_CHECK(compfn);
    list->compfn = compfn;
}
// registers a function to print the data of a node
void reg_printfn(list_t *list, void (*printfn)(const void *data)){
    NULL_CHECK(list);
    NULL_CHECK(printfn);
    list->printfn = printfn;
}

/**
 * access function definitions
 */

// list_head - get the head of the list
// @list: list to get the head
// @return: head of the list
node_t *list_head(list_t *list){
    NULL_CHECK_RET(list, NULL);
    return list->head;
}

// list_tail - get the tail of the list
// @list: list to get the tail
// @return: tail of the list
node_t *list_tail(list_t *list){
    NULL_CHECK_RET(list, NULL);
    return list->tail;
}

// list_length - get the length of the list
// @list: list to get the length
// @return: length of the list
unsigned int list_length(list_t *list){
    NULL_CHECK_RET(list, -1);
    return list->length;
}


/**
 * insertion function definitions
 */

// ins_head - insert a new node at the head of the list
// @list: list to insert the node
// @node: node to be inserted
void ins_head(list_t *list, node_t *node){
    NULL_CHECK(list);
    NULL_CHECK(node);
    if(list->head == NULL){
        list->head = node;
        list->tail = node;
        node->next = NULL;
        node->prev = NULL;
    }else{
        node->next = list->head;
        node->prev = NULL;
        list->head->prev = node;
        list->head = node;
    }
    list->length++;
}

// ins_tail - insert a new node at the tail of the list
// @list: list to insert the node
// @node: node to be inserted
void ins_tail(list_t *list, node_t *node){
    NULL_CHECK(list);
    NULL_CHECK(node);
    if(list->tail == NULL){
        list->head = node;
        list->tail = node;
        node->next = NULL;
        node->prev = NULL;
    }else{
        node->next = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
}
//###################################################################
// ins_after - insert a new node after the given node
// @list: list to insert the node
// @node: node to be inserted
// @prev: node to insert after
// void ins_after(list_t *list, node_t *node, node_t *prev){
//     NULL_CHECK(list);
//     NULL_CHECK(node);
//     NULL_CHECK(prev);
//     if(prev->next == NULL){
//         list->tail = node;
//     }else{
//         prev->next->prev = node;
//     }
//     node->next = prev->next;
//     node->prev = prev;
//     prev->next = node;
//     list->length++;
// }
void ins_after(list_t *list, node_t *ref, node_t *node){
    // return if list, ref, or node is null
    if (!list || !ref || !node){
        return;
    } 
    // case 0 - ref = node
    if(ref == node){
        puts("#intrusive.so: use ins_head or ins_tail first.");
        return;
    }
    // case 0 - ref has next pointer 
    if(ref->next){
        node->next = ref->next;
        node->prev = ref;
        ref->next->prev = node;
        ref->next = node;
        list->length++;
    } 
    // case 1 - ref has null next pointer (ref is tail pointer)
    else {
        node->prev = ref;
        ref->next = node;
        list->tail = node;
        list->length++;
    }
}
//###################################################################
// void ins_before(list_t *list, node_t *ref, node_t *node){
//     // return if list, ref, or node is null
//     if (!list || !ref || !node){
//         return;
//     }
//     // case 0 - ref = node
//     if(ref == node){
//         puts("#intrusive.so: use ins_head or ins_tail first.");
//         return;
//     }
//     // case 1 - ref has prev pointer
//     if(ref->prev){
//         node->prev = ref->prev;
//         node->next = ref;
//         ref->prev->next = node;
//         ref->prev = node;
//         list->length++;
//     }
//     // case 2 - ref has null prev pointer (ref is head pointer)
//     else {
//         node->next = ref;
//         ref->prev = node;
//         list->head = node;
//         list->length++;
//     }
// }
void ins_before(list_t *list, node_t *new_node, node_t *existing_node) {
    NULL_CHECK(list);
    NULL_CHECK(new_node);
    NULL_CHECK(existing_node);

    if (list->head == NULL) {
        fprintf(stderr, "Error: existing_node not found in list.\n");
        return;
    }

    if (list->head == existing_node) {
        ins_head(list, new_node);
        return;
    }

    new_node->next = existing_node;
    new_node->prev = existing_node->prev;
    existing_node->prev->next = new_node;
    existing_node->prev = new_node;

    list->length++;
}

//##################################################################

// ins_sorted - insert a new node in sorted order
// @list: list to insert the node
// @node: node to be inserted
// void ins_sorted(list_t *list, node_t *node){
//     NULL_CHECK(list);
//     NULL_CHECK(node);
//     node_t *curr = list->head;
//     while(curr != NULL && list->compfn(node, curr) > 0){
//         curr = curr->next;
//     }
//     if(curr == NULL){
//         ins_tail(list, node);
//     }else{
//         ins_before(list, node, curr);
//     }
// }
// void ins_sorted(list_t *list, node_t *node){
//     NULL_CHECK(list);
//     NULL_CHECK(node);

//     node_t *curr = list->head;

//     while(curr != NULL) {
//         void *curr_data = container_of(curr, void, node);
//         void *node_data = container_of(node, void, node);
//         if(list->compfn(node_data, curr_data) <= 0) {
//             break;
//         }

//         curr = curr->next;
//     }
//     if(curr == NULL) {
//         ins_tail(list, node);
//     } else {
//         ins_before(list, node, curr);
//     }
// }
// void ins_sorted(list_t *list, node_t *node){
//     NULL_CHECK(list);
//     NULL_CHECK(node);

//     node_t *curr = list->head;

//     while(curr != NULL) {
//         app_data_placeholder_t *curr_data = container_of(curr, app_data_placeholder_t, node);
//         app_data_placeholder_t *node_data = container_of(node, app_data_placeholder_t, node);
//         if(list->compfn(node_data, curr_data) <= 0) {
//             break;
//         }

//         curr = curr->next;
//     }
//     if(curr == NULL) {
//         ins_tail(list, node);
//     } else {
//         ins_before(list, node, curr);
//     }
// }
void ins_sorted(list_t *list, node_t *node){
    NULL_CHECK(list);
    NULL_CHECK(node);

    node_t *curr = list->head;

    while(curr != NULL) {
        app_data_placeholder_t *curr_data = container_of(curr, app_data_placeholder_t, node);
        app_data_placeholder_t *node_data = container_of(node, app_data_placeholder_t, node);
        int comp_result = list->compfn(node_data, curr_data);
        printf("Comparing new node (%p) with current node (%p): %d\n", (void *)node_data, (void *)curr_data, comp_result);
 
        if(comp_result < 0) {
            break;
        }

        curr = curr->next;
    }
    if(curr == NULL) {
        ins_tail(list, node);
    } else {
        ins_before(list, curr, node);
    }

}


/**
 * deletion function definitions
 */

// pop_head - delete the head of the list
// @list: list to delete the head
// @return: head of the list
// note: does not free the node
node_t *pop_head(list_t *list){
    NULL_CHECK_RET(list, NULL);
    node_t *node = list->head;
    if(list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
    }else{
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    list->length--;
    return node;
}

// pop_tail - delete the tail of the list
// @list: list to delete the tail
// @return: tail of the list
// note: does not free the node
node_t *pop_tail(list_t *list){
    NULL_CHECK_RET(list, NULL);
    node_t *node = list->tail;
    if(list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
    }else{
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    list->length--;
    return node;
}

// pop_node - delete the given node
// @list: list to delete the node
// @node: node to be deleted
// note: does not free the node
void pop_node(list_t *list, node_t *node){
    NULL_CHECK(list);
    NULL_CHECK(node);
    if(node->prev == NULL){
        list->head = node->next;
    }else{
        node->prev->next = node->next;
    }
    if(node->next == NULL){
        list->tail = node->prev;
    }else{
        node->next->prev = node->prev;
    }
    list->length--;
}

// free_node - free the given node
// @list: list to free the node
// @node: node to be freed
// note: this function must be used with _safe traversal macros!
void free_node(list_t *list, node_t *node){
    NULL_CHECK(list);
    NULL_CHECK(node);
    NULL_CHECK(list->freefn); 
    pop_node(list, node);
    list->freefn(node);
}
// free_list - free the list
// @list: list to be freed
void free_list(list_t *list){
    NULL_CHECK(list);
    NULL_CHECK(list->freefn);
    node_t *curr = list->head;
    while(curr != NULL){
        node_t *next = curr->next;
        list->freefn(curr);
        curr = next;
    }
    free(list);
}

/**
 * search functions
 */

// linear_search - search for a node in the list
// @list: list to search
// @key: key to search for
// @return: node if found, NULL otherwise
node_t *linear_search(list_t *list, const void *key){
    NULL_CHECK_RET(list, NULL);
    NULL_CHECK_RET(key, NULL);
    node_t *curr = list->head;
    while(curr != NULL && list->compfn(key, curr) != 0){
        curr = curr->next;
    }
    return curr;
}

// binary_search - search for a node in the list
// @list: list to search
// @key: key to search for
// @return: node if found, NULL otherwise
node_t *binary_search(list_t *list, const void *key){
    NULL_CHECK_RET(list, NULL);
    NULL_CHECK_RET(key, NULL);
    node_t *curr = list->head;
    node_t *last = list->tail;
    while(curr != NULL && last != NULL && curr != last && curr->next != last){
        node_t *mid = curr;
        for(int i = 0; i < (list->length / 2); i++){
            mid = mid->next;
        }
        int cmp = list->compfn(key, mid);
        if(cmp == 0){
            return mid;
        }else if(cmp < 0){
            last = mid->prev;
        }else{
            curr = mid->next;
        }
    }
    return NULL;
}

/**
 * sort functions
 */

// bubble_sort - sort the list using bubble sort
// @list: list to sort
void bubble_sort(list_t *list){
    NULL_CHECK(list);
    node_t *curr = list->head;
    while(curr != NULL){
        node_t *next = curr->next;
        while(next != NULL){
            if(list->compfn(curr, next) > 0){
                node_t *tmp = next->next;
                pop_node(list, next);
                ins_before(list, next, curr);
                next = tmp;
            }else{
                next = next->next;
            }
        }
        curr = curr->next;
    }
}

