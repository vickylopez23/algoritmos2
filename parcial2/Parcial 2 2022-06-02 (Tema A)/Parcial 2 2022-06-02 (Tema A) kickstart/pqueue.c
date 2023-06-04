#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
   struct s_node *front;
   unsigned int size;
   
};

struct s_node {
   pqueue_elem elem1;
   unsigned int prio;
   struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem1=e;
    new_node->prio=priority;
    new_node->next=NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next=NULL;
    free(node);
    node=NULL;
    assert(node == NULL);
    return node;
}



static bool invrep(pqueue q) {
    unsigned int actual_size = 0;
    // Para empezar, el valor de la pila no debería ser nulo;
    bool valid = (q != NULL);

    struct s_node *p = q->front; //apunto al primer nodo de la pila
    while(valid && p != NULL) {
      // Mantenga un registro del tamaño
      ++actual_size;
      // Comprobar la validez del pedido
      valid = p->next == NULL || p->prio <= p->next->prio; //si el nodo siguiente es nulo o la prioridad del nodo actual es menor o igual a la prioridad del nodo siguiente
      p = p->next;
    }

    return valid && q->size == actual_size;
    return true;
}


pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->front = NULL;
    q->size=0;
    invrep(q);
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    // Node izquierdo
    struct s_node *left;
    // Node derecho
    struct s_node *right;
    left = NULL;    //apunto al primer nodo de la pila
    right = q->front; //apunto al primer nodo de la pila

    while(right != NULL && new_node->prio >= right->prio) { //si el nodo siguiente es nulo o la prioridad del nodo actual es menor o igual a la prioridad del nodo siguiente
      left = right; //apunto al primer nodo de la pila
      right = right->next; //apunto al primer nodo de la pila
    }

    if(left == NULL) { // si el nodo izquierdo es nulo
      // agregar al frente
      new_node->next = right;
      q->front = new_node; //apunto al primer nodo de la pila
    } else {
      //agregar en medio
      left->next = new_node;
      new_node->next = right;
    }

    ++q->size;

    return q;
}


bool pqueue_is_empty(pqueue q) {
    return q->size == 0;
}
pqueue_elem pqueue_peek(pqueue q) {
    return q->front->elem1;
}

unsigned int pqueue_peek_priority(pqueue q) {
    return q->front->prio;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q));
    struct s_node *killme = q->front;
    q->front = q->front->next;
    destroy_node(killme);
    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node = q->front;
    while (node != NULL) {
        struct s_node *killme=node; //guarda el nodo a eliminar
        node = node->next;
        killme = destroy_node(killme); //elimina el nodo
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
    

}
