#include "../include/glue.h"

/*******************************
 * App-Specific Data Structures
 *******************************/

typedef struct datax 
{
    unsigned int id;
    char *name;
} datax_t;

typedef struct datay
{
    float fnum;
    char alph;
} datay_t;

/**************************
 * App-Specific Functions
 **************************/
 
 // create datax object
datax_t *create_datax(unsigned int id, char *name)
{
    datax_t *data = (datax_t *)malloc(sizeof(datax_t));
    if (data == NULL) {
        return NULL;
    }
    data->id = id;
    data->name = name;
    return data;
}

// create datay object
datay_t *create_datay(float fnum, char alph)
{
    datay_t *data = (datay_t *)malloc(sizeof(datay_t));
    if (data == NULL) {
        return NULL;
    }
    data->fnum = fnum;
    data->alph = alph;
    return data;
}

/***********************
 * Print/Free Functions
 ***********************/

// print datax object
void print_datax(datax_t *data)
{
    printf("id: %d, name: %s\n", data->id, data->name);
}

// print datay object
void print_datay(datay_t *data)
{
    printf("fnum: %f, alph: %c\n", data->fnum, data->alph);
}

// free datax object
void free_datax(datax_t *data)
{
    free(data);
}

// free datay object
void free_datay(datay_t *data)
{
    free(data);
}

/***********************
 * Comparison Functions
 **********************/

// compare datax objects by id field
// returns 0 if equal, -1 if datax1 < datax2, 1 if datax1 > datax2
int compare_datax_id(datax_t *datax1, datax_t *datax2)
{
    if (datax1->id == datax2->id) {
        return 0;
    }
    else if (datax1->id < datax2->id) {
        return -1;
    }
    else {
        return 1;
    }
}

// compare datax objects by name field
// returns 0 if equal, -1 if datax1 < datax2, 1 if datax1 > datax2
int compare_datax_name(datax_t *datax1, datax_t *datax2)
{
    return strcmp(datax1->name, datax2->name);
}


// compare datay objects by fnum field
// returns 0 if equal, -1 if datay1 < datay2, 1 if datay1 > datay2
int compare_datay_fnum(datay_t *datay1, datay_t *datay2)
{
    if (datay1->fnum == datay2->fnum) {
        return 0;
    }
    else if (datay1->fnum < datay2->fnum) {
        return -1;
    }
    else {
        return 1;
    }
}

// compare datay objects by alph field
// returns 0 if equal, -1 if datay1 < datay2, 1 if datay1 > datay2
int compare_datay_alph(datay_t *datay1, datay_t *datay2)
{
    if (datay1->alph == datay2->alph) {
        return 0;
    }
    else if (datay1->alph < datay2->alph) {
        return -1;
    }
    else {
        return 1;
    }
}

/*********************
 * Keymatch Functions
 ********************/


// keymatch datax objects by id field
// returns 1 if equal, 0 if not equal
int keymatch_datax_id(datax_t *datax1, datax_t *datax2)
{
    if (datax1->id == datax2->id) {
        return 1;
    }
    else {
        return 0;
    }
}

// keymatch datax objects by name field
// returns 1 if equal, 0 if not equal
int keymatch_datax_name(datax_t *datax1, datax_t *datax2)
{
    if (strcmp(datax1->name, datax2->name) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// keymatch datay objects by fnum field
// returns 1 if equal, 0 if not equal
int keymatch_datay_fnum(datay_t *datay1, datay_t *datay2)
{
    if (datay1->fnum == datay2->fnum) {
        return 1;
    }
    else {
        return 0;
    }
}

// keymatch datay objects by alph field
// returns 1 if equal, 0 if not equal
int keymatch_datay_alph(datay_t *datay1, datay_t *datay2)
{
    if (datay1->alph == datay2->alph) {
        return 1;
    }
    else {
        return 0;
    }
}

int main()
{
    printf("First trial run...\n\n\n");

    glist_t *listx = glist_init();
    glist_t *listy = glist_init();
    glist_status(listx);
    glist_status(listy);

    return 0;
}