#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 #include <stdbool.h>


struct _s_stack {
    stack_elem elem;
    stack next;
    unsigned int size;
};

//crea una pila vacia
stack stack_empty(){
    stack s = NULL;
    return s;
}

//inserta un elemento en la pila
stack stack_push(stack s, stack_elem e){
    stack p = NULL;
    p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    s = p;
    return s;
}

//Operations

//Remueve el elemento de la pila
stack stack_pop(stack s){
    assert(s != NULL);
    stack p = NULL;
    p = s;
    s = s->next;
    free(p);
    return s;
}

//retorna el tamaño de la pila
unsigned int stack_size(stack s){
   return s->size;
}

//Returns the top element of the stack
stack_elem stack_top(stack s){
    assert(s != NULL);
    return s -> elem;
}

//Checks if the stack is empty
bool stack_is_empty(stack s){
    return s == NULL;
}

//convierte la pila en un array
stack_elem *stack_to_array(stack s){
    unsigned int len = stack_size(s)-1u; //le resto 1 porque el array empieza en 0//
    stack q = NULL; //creo una pila auxiliar//
    stack_elem* array = NULL; //creo un array//
    q = s; //igualo la pila auxiliar a la pila original//
    array = calloc(stack_size(s), sizeof(stack_elem)); //reservo memoria para el array//
    while(!stack_is_empty(q)){ //recorro la pila//
        array[len] = stack_top(q); //agrego el elemento de la pila al array//
        q = q -> next; //avanzo en la pila//
        len--;
    }
    free(q);
    return array;
}

//Destroys the stack
stack stack_destroy(stack s){
    stack q = NULL;
    q = s; //igualo la pila auxiliar a la pila original//
    while(s != NULL){
        q = s; //igualo la pila auxiliar a la pila original//
        s = s -> next;
        free(q); //libero la memoria de la pila//
    }
    return s;
}

