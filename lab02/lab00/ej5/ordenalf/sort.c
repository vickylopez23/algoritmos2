#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int piv = izq;
    unsigned int i=izq+1u,j=der;
    while (i <= j){
        if(fstring_less_eq(a[i],a[piv])){
            i = i+1u;
        }else if(fstring_less_eq(a[piv],a[j])){
            j = j-1u;
        }else if(fstring_less_eq(a[piv], a[i]) && fstring_less_eq(a[j], a[piv])){
            swap(a,i,j);
        }
    }
    swap(a,piv,j);
    piv = j;
    return piv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    if (der > izq){
        int piv = partition(a, izq, der);
        if (piv > 0){
            quick_sort_rec(a, izq, piv - 1);
        }
        quick_sort_rec(a, piv + 1, der);
    }   
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


