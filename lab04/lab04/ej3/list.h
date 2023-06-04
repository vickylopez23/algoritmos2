
#include <stdbool.h>

typedef struct s_list *list;
typedef int list_elem;

//Constructors

//Create a empty list
list empty();

//Add elem "e" to the left  of list "l"
list addl (list l, list_elem e);

//Free memory
list destroy (list l);


//Operations

//Return true if list "l" is empty
bool is_empty(list l);


//{- PRE: not is_empty(l) -}
//Return the first elem  of list "l"
list_elem head(list l);


//{- PRE: not is_empty(l) -}
//Remove the first elem of list "l"
list tail (list l);


//Add elem "e" to the right of list "l"
list addr(list l, list_elem e);


//Return the size of list "l"
list_elem length (list l);


//Add the list l1 a finish the list l
list concat (list l, list l1);


//{- PRE: length(l)>n -}
//Return the element "n" of list "l"
list_elem index (list l, list_elem n);

//Return the list "l" with the elemts up to "n"
list take (list l, list_elem n);


//Remove the first "n" elemts of list "l"
list drop (list l , list_elem n);


//Copy the list "l"
list copy_list (list l1);