#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct s_list {
    list_elem elem;
    struct s_list * next;   
};


list empty(){
    list l= NULL;
    
    return l;
}


list addl (list l, list_elem e){
    list new= malloc (sizeof (struct s_list));
    new->elem=e;
    new->next=NULL;
    if (l==NULL){           //si lista es vacia
        l=new;
    }
    else{                   //si no es vacia
        new->next=l;
        l=new;
    }

    return l;
}

list destroy(list l){
    list kill;
    while (l!=NULL){       //itero hasta el final
        kill = l;
        l = kill -> next;
        free(kill);             //elimino todos los nodos
    }
    free(l);
    l=NULL;
    return l;
}



bool is_empty(list l){
    return l == NULL;
}

list_elem head(list l){
    assert(!is_empty(l));
    return l->elem;
}

list tail (list l){
    assert(!is_empty(l));
    list kill=l;
    l=kill->next;
    free(kill);

    return l;
}


list addr(list l, list_elem e){
    list new= malloc (sizeof (struct s_list));
    new->elem=e;
    new->next=NULL;
    if (l==NULL){           //si lista es vacia
        l=new;
    }
    else{                   //si no es vacia
        list aux=l;
        while(aux->next!=NULL){     //itero hasta el ultimo
            aux=aux->next;
        }
        aux->next=new;
    }
    return l;

}


list_elem length (list l){
    list_elem size=0;
    list aux=l;

    while (aux!=NULL){
        ++size;
        aux=aux->next;
    }
    return size;
}


list concat (list l, list l1){
    list aux1=NULL;
    if(l==NULL){
        l=l1;
    }
    else{
        list aux=l;
        while (aux->next!=NULL){        //itero hasta el final de "l"
            aux=aux->next;
        }
        aux1=l1;

        while (aux1!=NULL){             //itero hasta el final de "l1"
            list new= malloc (sizeof(struct s_list));   //voy creando nodos a medida que tengo un nuevo elemento de "l1"
            new->elem=aux1->elem;
            new->next=NULL;
            aux=new;
            aux1=aux1->next;
        }
    }
    return l;
}



list_elem index (list l, list_elem n){
    assert(length(l)>n);
    list aux=l;
    list_elem res;
    for (int i=0; i<n; ++i){        //itero hasta n-1, ya que indice empieza en 0
        aux=aux->next;
    }
    res=aux->elem;

    return res;
}


list take (list l, list_elem n){
    list aux=l;
    for (int i=0; i<n; ++i){            //itero hasta n-1, ya que indice empieza en 0
        aux=aux->next;
    }
    while (aux!=NULL){                  //elimino los restantes
        list kill=aux;
        aux=aux->next;
        free(kill);
    }
    return l;
}


list drop (list l , list_elem n){
    list kill=l;
    for (int i=0; i<n; ++i){        //elimino los n-1 primeros
        kill=l;
        l=kill->next;
        free(kill);
    }

    return l;
}


list copy_list (list l1){
   list l_aux=empty();
    list aux=l1;
    list pre;

    while (aux!=NULL){
        list new= malloc (sizeof(struct s_list));
        new->elem=aux->elem;
        new->next=NULL;
        if(l_aux==NULL){
            l_aux=new;
        }
        else{
            pre->next=new;
        }
        pre=new;
        aux=aux->next;
    }
    return l_aux;
}