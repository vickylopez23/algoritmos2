#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
   struct s_node **array;
   unsigned int size;
   priority_t priority;
   priority_t max_priority;
   
};

struct s_node {
  struct s_node * next;
  pstack_elem elem;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    new_node=  malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem=e;
    new_node->next= NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool res = s != NULL;
    if (res) {
        priority_t i = 0;
        while (i <= s->max_priority) {
            struct s_node *c = s->array[i];
            while (c != NULL) {
                c = c->next;
            }
            i++;
        }
    }
    return res;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof (struct s_pstack));
    s->array =malloc(sizeof (struct s_node)*max_priority); //creo el array de punteros a nodos multiplicando el tamaño de un puntero por la cantidad de prioridades
    s->size = 0;
    s->priority = 0; //
    s->max_priority = max_priority;
    for(unsigned int i=0; i<=max_priority; i++) {
        s->array[i] = NULL;
    }
    return s;
}


pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));

    struct s_node *new_node = create_node(e);
    struct s_node *c = s->array[priority];

    if (c == NULL) {
        s->array[priority] = new_node; // If there are no elements at this priority, the new node becomes the first
    } else {
        while (c->next != NULL) {
            c = c->next; // If there are elements at this priority, traverse the list until the last node
        }
        c->next = new_node; // The last node points to the new node
    }

    s->size++;

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}


bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return  s->size == 0;
   
}


pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    // Find the first non-empty priority level
    priority_t i = s -> priority;
    while (i <= s->max_priority && s->array[i] == NULL) {
        i++;
    }
    s->priority = i;
    return s->array[i]->elem;

}



    


priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->priority;
    return true;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *c = s->array[s->priority];
    s->array[s->priority] = c->next; //el primer nodo de la lista de la prioridad actual pasa a ser el siguiente

    destroy_node(c);
    s->size--;

    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    for(unsigned int i=0; i<=s->max_priority; i++) {
        struct s_node *c = s->array[i];
        while(c != NULL) {
            struct s_node *aux = c;
            c = c->next;
            destroy_node(aux);
        }
    }
    free(s->array);
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
