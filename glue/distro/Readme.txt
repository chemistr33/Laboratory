


Callback functions you'll need to develop & register in application code:
-------------------------------------------------------------------------

1.) A function capable of printing the user-specific data structure, i.e. it 
knows all the different data types, capable of handling strings.

-> void (*print_fn)(void *);

2.) A comparison function that is able to compare the data members stored 
in two different nodes. String functions for strings, comparison logic
for numbers. That sort of thing.

-> int (*comp_fn)(void *, void *);

3.) A keymatch function that casts the generic library's (void *) key to the 
appropriate type of the search key specified by the user. Ex.) if searching
for whether a number matches, the void* would get cast to an int*.

-> gnode_t *(*keymatch_fn)(glist_t *, void *);

4.) A free function that free's any pointers stored in the app-specific
data structure.

void (*free_fn)(void *);

export LD_LIBRARY_PATH=/home/fransys/prog/C/Laboratory/glue/lib/
