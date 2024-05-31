#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct node {
    struct node *prev;
    struct node *next;
} Node;

typedef struct asds {
    int value;
    char *str;
    Node node;
} Asds;

void init_list(Node *list) {
    list->next = list;
    list->prev = list;
}

void append_node(Node *list, Node *node) {
    node->next = list->next;
    node->prev = list;
    list->next->prev = node;
    list->next = node;
}

void prepend_node(Node *list, Node *node) {
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
}

void remove_from_list(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void print_list(Node *list) {
    Node *current = list->next;
    int count = 0;
    while (current != list) {
        Asds *data = container_of(current, Asds, node);
        printf("(%d): node address: %p\tvalue: %d\tstr: %s\n",
                ++count, 
                data,
                data->value,
                data->str
              );
        current = current->next;
    }
    puts("");
}

void sort_list(Node *list) {
    Node sorted;
    init_list(&sorted);

    Node *current = list->next;
    while (current != list) {
        Node *next = current->next;
        Asds *cur_data = container_of(current, Asds, node);
        Node *sorted_current = sorted.next;
        while (sorted_current != &sorted) {
            Asds *sorted_data = container_of(sorted_current, Asds, node);
            if (cur_data->value <= sorted_data->value) {
                break;
            }
            sorted_current = sorted_current->next;
        }
        remove_from_list(current);
        prepend_node(sorted_current, current);
        current = next;
    }

    list->next = sorted.next;
    list->prev = sorted.prev;
    list->next->prev = list;
    list->prev->next = list;
}

Node *search_list(Node *list, int value) {
    Node *current = list->next;
    while (current != list) {
        Asds *data = container_of(current, Asds, node);
        if (data->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

size_t size(Node *list) {
    size_t count = 0;
    Node *current = list->next;
    while (current != list) {
        count++;
        current = current->next;
    }
    return count;
}

void reverse(Node *list) {
    if (list->next == list || list->next->next == list) {
        // List is empty or has only one node, no need to reverse
        return;
    }

    Node *current = list->next;
    do {
        Node *temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    } while (current != list);

    Node *temp = list->next;
    list->next = list->prev;
    list->prev = temp;
}

int main() {

    system("clear");
    Node list;
    init_list(&list);

    Asds one =   {.value = 10,   .str = "alpha"    , .node = {0}};
    Asds two =   {.value = 200,   .str = "bravo"   , .node = {0}};
    Asds three = {.value = 80,   .str = "charlie"  , .node = {0}};
    Asds four =  {.value = 50,   .str = "delta" , .node = {0}};
    Asds five =  {.value = 70,   .str = "echo", .node = {0}};

    append_node(&list, &one.node);
    append_node(&list, &two.node);
    append_node(&list, &three.node);
    append_node(&list, &four.node);
    append_node(&list, &five.node);

    puts("### Printing original list...\n");
    print_list(&list);

    sort_list(&list);

    puts("### Printing integer sorted list...\n");
    print_list(&list);

    puts("### Printing result of searching for node with 80 value...\n");
    printf("node address: %p \n\n", 
            container_of(search_list(&list, 80), Asds, node));

    puts("### Printing list size...\n");
    printf("List size: %ld\n\n", size(&list));

    reverse(&list);


    puts("### Printing reversed list...\n");
    print_list(&list);

return 0;
}