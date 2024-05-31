#include "../include/oglist.h"

// app-specific data structure
typedef struct x_{
    int num;
    char alph;
    onode_t *onode; 
} x_t;

// app-specific free function callback
void xfreefn(void *app_struct){
    // return if app struct is null
    if(!app_struct)
        return;

    // free app-specific data structure
    free(app_struct);
}

// app-specific print function callback
void xprint(void *app_struct){
    // return if app_struct is null
    if(!app_struct)
        return;

    // print members
    x_t *_app_struct = (x_t *)app_struct;
    printf("[%p]\tnum: %d\talph: %c\n", 
        _app_struct,
         _app_struct->num,
          _app_struct->alph
          );
}

int main(){

olist_t *xlist=NULL;
INIT_LIST(xlist);

x_t *xa = malloc(sizeof(x_t));
x_t *xb = malloc(sizeof(x_t));
x_t *xc = malloc(sizeof(x_t));
xa->num=1;
xa->alph='a';
xa->onode = NULL;
xb->num=2;
xb->alph='b';
xb->onode = NULL;
xc->num=3;
xc->alph='c';
xc->onode = NULL;

ins_head(xlist, &(xa->onode));
printf("xa: %p\n", GET_HEAD(xlist));


REG_PRINTFN(xlist, xprint);


 return 0;
}