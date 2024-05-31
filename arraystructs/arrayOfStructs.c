#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct obj {
    int num;
    char letter;
    char name[20];
}obj_t;

char* 
randomString(char *arr)
{
    int l=20;
    char charset[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+";
    for(int i=0; i<l; i++)
    {
       arr[i] = charset[rand() % l];
    }
return arr;
}

int main() {
    int i=0;
    char buf[20];
    srand(time(0));
    
    // Declare an array of struct pointers, named 'objs' 
    obj_t *(objs[10]);

    // Allocate each struct pointer 
    for(int i=0;i<10;i++){
        objs[i]=malloc(sizeof(obj_t));
    }
   
    // initialize each struct's members 
    for(int i=0; i<10; i++){
    objs[i]->num = i+1;
    objs[i]->letter = i+67;
    strcpy((objs[i]->name), randomString(buf));
    }
    
    // print each struct
    for(int i=0; i<10; i+=2){
    printf("|-----------------------|\t|-----------------------|\n");
    printf("|<%s>|\t\t<%s>\n",objs[i]->name,objs[i+1]->name);
    printf("|\t<%c>|\t\t\t\t<%c>\n",objs[i]->letter,objs[i+1]->letter);
    printf("|\t<%d>|\t\t\t\t<%d>\n",objs[i]->num,objs[i+1]->num);
    printf("|-----------------------|\t|-----------------------|\n\n");
    }

return 0;
}
