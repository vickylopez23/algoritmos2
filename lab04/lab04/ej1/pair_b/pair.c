#include "pair.h"
#include <stdio.h>
#include <stdlib.h>


pair_t pair_new(int x, int y){
    pair_t pair= malloc (sizeof(struct s_pair_t));
    pair->fst=x;
    pair->snd=y;

    return pair;
    
}


int pair_first(pair_t p){
    return p->fst;
}


int pair_second(pair_t p){
    return p->snd;
}



pair_t pair_swapped(pair_t p){
    int aux=p->fst;
    p->fst=p->snd;
    p->snd=aux;

    return p;
}


pair_t pair_destroy(pair_t p){
    free(p);
    return p;
}