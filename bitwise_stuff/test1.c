#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define A (1<<0)
#define B (1<<1)
#define C (1<<2)
#define D (1<<3)
#define E (1<<4)
#define F (1<<5)
#define G (1<<6)
#define H (1<<7)

#define SET_BIT(n,flag)     \
    (n) |= (flag)

#define UNSET_BIT(n, flag)  \
    (n) &= ~(flag)

#define ISTRUE_BIT(n, flag) \
    (n) & (flag)

#define TOGGLE_BIT(n, flag) \
    (n) ^= (flag)


int main(){

    u_int8_t r = 0;

    /*@   1<<0 evaluates to 1, which goes to the LSB 
     *@  position of the unsigned byte. 
      @
      */


    printf("r bit 0 set...\n");
    SET_BIT(r, A);
    printf("r = %d \n",r);
   
    printf("r bit 0 unset...\n");
    UNSET_BIT(r, A); 
    printf("r = %d \n",r);
    
    printf("r bit 5 set...\n");
    SET_BIT(r, E);
    printf("r = %d \n",r);
    
    printf("r bit 5 unset...\n");
    UNSET_BIT(r, E);
    printf("r = %d \n",r);
    
    printf("r bit 7 set...\n");
    SET_BIT(r, H);
    printf("r = %d \n",r);
    
    printf("r bit 7 unset...\n");
    UNSET_BIT(r, H);
    printf("r = %d \n",r);
    
    printf("r bits 0 through 7 set...\n");
    SET_BIT(r, A);
    SET_BIT(r, B);
    SET_BIT(r, C);
    SET_BIT(r, D);
    SET_BIT(r, E);
    SET_BIT(r, F);
    SET_BIT(r, G);
    SET_BIT(r, H);
    printf("r = %d \n",r);
    
    return 0;
}