#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node ** array;
    unsigned int size;
    priority_t min_priority;
    priority_t prioririty;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

// Returns the higher priority between the two 
static priority_t higher_prio(priority_t a, priority_t b) {
    return a < b ? a : b;
}

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->next = NULL;
    new_node->elem = e;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

static priority_t pqueue_actual_peek_priority(pqueue q) {
    priority_t peek_prio;

    for(unsigned int i = 0; i<=q->min_priority; ++i) {
        if(q->array[i] != NULL) {
            peek_prio = i;
            break;
        }
    }

    return peek_prio;
}

static bool invrep(pqueue q) {
    // Pqueue value shouldn't be null unless destroyed
    bool valid = q!=NULL;
    struct s_node *curr;

    // Check size corresponds to the actual amount of elements
    unsigned int actual_size = 0;
    if(valid) {
        for(unsigned int i = 0; i<=q->min_priority; ++i) {
            curr = q->array[i];
            while(curr != NULL) {
                ++actual_size;
                curr = curr->next;
            }
        }
        valid = actual_size == q->size;
    }

    // Check that peek priority corresponds to the actual peek priority, unless the pqueue is empty
    if(valid && actual_size > 0 ) {
      valid = q->prioririty == pqueue_actual_peek_priority(q);
    }
    return valid;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    // Peek priority is initially a bigger number than any possible priority
    q->prioririty = min_priority+1;
    q->min_priority = min_priority;
    q->array = malloc(sizeof(struct s_node*) * (min_priority+1));
    for(unsigned int i=0; i<=min_priority; i++) {
        q->array[i] = NULL;
    }
    assert(invrep(q));
    assert(pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, 
priority_t priority) {
    assert(invrep(q));
    assert(priority <= q->min_priority);

    struct s_node *new_node = create_node(e);
    
    if(q->array[priority] == NULL) {
        q->array[priority] = new_node;
    } else {
        // Get the queue for the given priority
        struct s_node *curr = q->array[priority];
        // Insert the element at the end of the queue
        while(curr->next != NULL) {
            curr = curr->next;
        } 
        curr->next = new_node;
    }
    ++q->size;
    q->prioririty = higher_prio(priority, q->prioririty);

    assert(invrep(q));
    assert(!pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem peek;
    for(unsigned int i = 0; i<=q->min_priority; ++i) {
        if(q->array[i] != NULL) {
            peek = q->array[i]->elem;
            break;
        }
    }

    return peek;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->prioririty;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t peek_prio = q->prioririty;
    struct s_node *killme = q->array[q->prioririty];
    q->array[peek_prio] = q->array[q->prioririty]->next;
    destroy_node(killme);
    --q->size;

    // Update prioririty
    // If the dequeued queue is empty, then prioririty will be min_priority + 1
    while(q->prioririty<=q->min_priority && q->array[q->prioririty] == NULL ) { // "prioririty is valid and it's corresponding queue is empty"
      ++(q->prioririty);
    }

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *killme;
    for(unsigned int i = 0; i<=q->min_priority; ++i) {
        while(q->array[i] != NULL) {
            killme = q->array[i];
            q->array[i] = q->array[i]->next;
            destroy_node(killme);
        }
    }
    free(q->array);
    free(q);
    q = NULL;
    return q;
}