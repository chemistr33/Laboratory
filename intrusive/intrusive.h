#ifndef ___INTRUSIVE_H___
#define ___INTRUSIVE_H___
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>


typedef struct node{
    struct node *next;
    struct node *prev;
} Node;









#endif