#include "../inc/intrusive.h"

// app specific data structure
typedef struct app_data_ {
    int num;
    char *str;
    node_t node;
} app_data_t;

/**
 * Callback Functions
 */

// app-specific freefn
void app_freefn(void *data)
{
    app_data_t *app_data = (app_data_t *)data;
    free(app_data->str);
    free(app_data);
}

// // app-specific int compfn
// int app_compfn(const void *key1, const void *key2)
// {
//     app_data_t *app_data1 = (app_data_t *)key1;
//     app_data_t *app_data2 = (app_data_t *)key2;
//     return app_data1->num - app_data2->num;
// }

int app_compfn(const void *key1, const void *key2)
{
    app_data_t *app_data1 = (app_data_t *)container_of(key1, app_data_t, node);
    app_data_t *app_data2 = (app_data_t *)container_of(key2, app_data_t, node);

    if(app_data1->num < app_data2->num)
        return -1;
    else if(app_data1->num > app_data2->num)
        return 1;
    else
        return 0;
}


// app-specific char * compfn
int app_strcompfn(const void *key1, const void *key2)
{
    app_data_t *app_data1 = (app_data_t *)key1;
    app_data_t *app_data2 = (app_data_t *)key2;
    return strcmp(app_data1->str, app_data2->str);
}

// app-specific printfn
void app_printfn(const void *data)
{
    app_data_t *app_data = (app_data_t *)data;
    printf("\t|------------------------------\\\n");
    printf("\t|app_data: %p\t|\n", (void *)app_data);
    printf("\t|num: %d, str: %s\t|\n", app_data->num, app_data->str);
    printf("\t|------------------------------/\n");
}

// print list_t structure status macro
#define PRINT_LIST_STATUS(list)                               \
    printf("\t|- - - - - - - - - - - - - - - -\\\n");         \
    printf("\t|List name: \t\"%s\"\t|\n", #list);             \
    printf("\t|&list: \t%p\t|\n", list);                      \
    printf("\t|list_length: \t\t%d\t|\n", list_length(list)); \
    printf("\t|freefn: \t%p\t|\n" , list->freefn);            \
    printf("\t|compfn: \t%p\t|\n" , list->compfn);            \
    printf("\t|printfn: \t%p\t|\n", list->printfn);           \
    printf("\t|head: \t\t%p\t|\n", list->head);             \
    printf("\t|tail: \t\t%p\t|\n", list->tail);             \
    printf("\t|Macro-Call Line #: \t%d\t|\n", __LINE__);      \
    printf("\t|- - - - - - - - - - - - - - - -/\n");                  

// new line macro
#define _NL_ puts("\n");

int main(int argc, char *argv[])
{
    list_t *applist = (list_t *)malloc(sizeof(list_t));

    // initialize list
    list_init(applist, app_freefn, app_compfn, app_printfn);

    app_data_t *appnode1 = (app_data_t *)malloc(sizeof(app_data_t));
    appnode1->num = 100;
    appnode1->str = strdup("Hello #1");
    appnode1->node.next = NULL;
    appnode1->node.prev = NULL;


    app_data_t *appnode2 = (app_data_t *)malloc(sizeof(app_data_t));
    appnode2->num = 200;
    appnode2->str = strdup("Hello #2");
    appnode2->node.next = NULL;
    appnode2->node.prev = NULL;


    app_data_t *appnode3 = (app_data_t *)malloc(sizeof(app_data_t));
    appnode3->num = 100;
    appnode3->str = strdup("Hello #3");
    appnode3->node.next = NULL;
    appnode3->node.prev = NULL;

printf("head: %p\n", list_head(applist));    
printf("tail: %p\n", list_tail(applist));    
printf("length: %d\n", list_length(applist));

ins_tail(applist, &appnode1->node);
ins_tail(applist, &appnode2->node);
ins_tail(applist, &appnode3->node);

app_data_t *cursor;
intrusive_for_each(cursor, applist, node){

    app_printfn(cursor);
}

printf("head: %p\n", list_head(applist));    
printf("tail: %p\n", list_tail(applist));    
printf("length: %d\n", list_length(applist));


ins_before(applist, &appnode1->node, &appnode2->node);
 
 
printf("\nhead: %p\n", list_head(applist));    
printf("tail: %p\n", list_tail(applist));    
 
cursor = NULL;
intrusive_for_each(cursor, applist, node){

    app_printfn(cursor);
}
 return 0;
}


