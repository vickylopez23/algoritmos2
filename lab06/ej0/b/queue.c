#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    struct s_node *first;
    unsigned int size;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
   
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q=NULL;
    q = malloc(sizeof(struct s_queue)); // 
    q->first = NULL;//
    assert(invrep(q) && queue_is_empty(q));
    return q;
}



queue queue_enqueue(queue q, queue_elem e)
{
  assert(invrep(q));
  struct s_node* new_node = create_node(e);
  if (q->first == NULL) { 
    q->first = new_node; //el primero es el nuevo
  } else {
    struct s_node* p = q->first; //p es el primero
    while (p->next != NULL) {  //mientras el siguiente no sea null
      p = p->next; //pasa al siguiente
    } 
    p->next = new_node; //el siguiente es el nuevo
  }
  assert(invrep(q) && !queue_is_empty(q));
  return q;
}


bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
   return q->size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;

}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem); //TODO: cambiar por el tipo de dato que sea
        node = node->next; //pasa al siguiente
        if (node != NULL) { 
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}
//que elimina de la cola el n-ésimo elemento, siendo queue_disscard(q, 0) equivalente a
//queue_dequeue(q).
queue queue_disscard(queue q, unsigned int n){
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node *node=q->first;
    if(n==0){
        q->first = q->first->next;
        node = destroy_node(node);
    }else{
        for(int i=0;i<n-1;i++){
            node=node->next;
        }
        struct s_node *killme=node->next;
        node->next=node->next->next;
        killme = destroy_node(killme);
    }
    assert(invrep(q));
    return q;
    
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
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
// gcc -Wall -Werror -Wextra -pedantic -std=c99 -c queue_helpers.c queue.c 