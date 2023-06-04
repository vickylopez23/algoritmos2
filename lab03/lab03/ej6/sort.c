/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool b;
    b= x->rank <= y->rank;
    return b;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}


void swap (player_t a[],unsigned int i, unsigned int j){
    player_t aux=a[i];
    a[i]=a[j];
    a[j]=aux;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int i,j,ppiv;
    ppiv=izq;
    i=izq+1;
    j=der;

    while (i<=j){
        if (goes_before(a[i],a[ppiv])){
            i++;
        }
        else if (goes_before(a[ppiv],a[j])){
            --j;
        }
        else if (goes_before(a[ppiv],a[i]) && goes_before(a[j],a[ppiv])){
            swap(a,i,j);
        }
    }
    swap(a,ppiv,j);
    ppiv=j;

    return ppiv;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der>izq){
        ppiv=partition(a,izq,der);
        if (ppiv>0){
            quick_sort_rec(a,izq,ppiv-1);
        }
        if (der>ppiv){
            quick_sort_rec(a,ppiv+1,der);   
        }
    }
    
}

void quick_sort(player_t a[], unsigned int length) {    
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

void sort (player_t a[], unsigned int lenght){
    quick_sort (a,lenght);
}




//Si funciona mas rapido la version con punteros


//Los swap con punteros son mas rapidos, ya que a un puntero le pasas una direccion de memoria, y ya sabe a donde esta parado
//en cambio el swap con variables son mas lentos

//Es necesario usar el destroy ya que ahora estamos trabajando en el heap, entonces hay que destruir 
//la memoria que pedimos, asi no quedan memory leeks