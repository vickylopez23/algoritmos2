#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = izq;
    unsigned int i= izq+1;
    unsigned int j= der;
    
    while(i<=j){
        if(goes_before(a[ppiv],a[i]) && goes_before(a[j],a[ppiv])){ // si el elemento de la izquierda es mayor que el pivote y el elemento de la derecha es menor que el pivote
            swap(a,i,j); // intercambio los elementos
            ++i; // sumo uno a i
            --j; // resto uno a j
        }else{
            if(goes_before(a[i],a[ppiv])){ // si el elemento a la izquierda es menor que el pivote
                ++i;
            }
            if(goes_before(a[ppiv],a[j])){ // si el elemento a la derecha es mayor que el pivote
                --j;
            }
        }
    }
    // dejando el pivot en una posición más central
    swap(a,ppiv,j);
    // señalando la nueva posición del pivot
    // ppiv=j;
    return j;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = partition(a,izq,der); // calculo el pivote
    if(ppiv>izq) {  // si el pivote es mayor que la posicion izquierda
        quick_sort_rec(a, izq, ppiv-1); // ordeno la parte izquierda del array
    }
    if(ppiv<der) {
        quick_sort_rec(a, ppiv+1, der);   // ordeno la parte derecha del array
    }

}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1); // ordeno el array 
}