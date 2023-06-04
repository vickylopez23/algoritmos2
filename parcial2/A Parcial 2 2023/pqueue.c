#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *front;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};

static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float calc_priority = 0;
    calc_priority = 0.5 * (average_grade/MAX_GRADE) + 
                    0.5 * (approved_courses/TOTAL_COURSES);
    if (calc_priority > 1) {
        calc_priority = 1;
    }
    else if (calc_priority < 0) {
        calc_priority = 0;
    }
    return calc_priority;
}

static struct s_node *create_node(pqueue_elem e,
                                  float average_grade,
                                  unsigned int approved_courses){
    struct s_node *new_node = malloc (sizeof (struct s_node));
    
    assert(new_node != NULL);
    
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->next = NULL;
    new_node->priority = calculate_priority (average_grade,approved_courses);
    

    return new_node;
}

static struct s_node *destroy_node(struct s_node *node){
    assert(node != NULL);
    //node->next = NULL;
    free (node);
    node = NULL;

    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q){
   bool inv_rep = false;
    unsigned int actual_size = 0;
    float priority_before = 1;
    struct s_node * temporal = q->front;

    inv_rep = (q != NULL); // the queue exists
    
    while (temporal != NULL) {
        inv_rep = inv_rep && (priority_before >= temporal->priority);
        temporal = temporal->next;
        actual_size = actual_size + 1;
    } // the queue has a priority order
    
    inv_rep = inv_rep && (q->size == actual_size); 
    // the queue size is correct

    return inv_rep;
}


pqueue pqueue_empty(void){
    pqueue q= malloc (sizeof (struct s_pqueue));
    
    q->size = 0;
    q->front = NULL;

    assert(invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q,
                      pqueue_elem e,
                      float average_grade,
                      unsigned int approved_courses){
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);

    if (q->front == NULL){                  //if queue is empty
        q->front = new_node;
    }else{                                  //if queue isnt empty
        struct s_node *post = q->front;
        struct s_node *pre = NULL;
        while (post->next != NULL && new_node->priority <= post->priority){
            pre = post;
            post = post->next;
        }
        if (q->front->priority < new_node->priority){      //insert in the first place
            new_node->next = q->front;
            q->front = new_node;
        }
        else if (post->priority < new_node->priority){     //insert between of extrems
            new_node->next = post;
            pre->next = new_node;
        }else{                                              //insert last
            post->next = new_node;
        }
    }

    ++q->size;
   
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q){
    assert(invrep(q));
   
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q){
    assert(invrep(q) && !pqueue_is_empty(q));

    return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q){
    assert(invrep(q) && !pqueue_is_empty(q));
    

    return q->front->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q){
    assert(invrep(q) && !pqueue_is_empty(q));

    return q->front->approved_courses;
}

float pqueue_peek_priority(pqueue q){
    assert(invrep(q) && !pqueue_is_empty(q));
    
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q){
    assert(invrep(q));
   
   return q->size;
}

pqueue pqueue_copy(pqueue q){
    assert(invrep(q));
    pqueue new_q = pqueue_empty();  
    struct s_node *aux = q->front;

    while (aux != NULL){
        new_q = pqueue_enqueue (new_q, aux->elem ,aux->average_grade, aux->approved_courses);
        aux = aux->next;
    }

    new_q->size = q->size;
    return new_q;
}

pqueue pqueue_dequeue(pqueue q){
    assert(invrep(q));
    struct s_node *kill = NULL;

    kill = q->front;
    q->front = kill->next;
    kill = destroy_node(kill);

    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q){
    assert(invrep(q));
    struct s_node *kill = NULL;
    while (q->front != NULL){
        kill = q->front;
        q->front = kill->next;
        kill = destroy_node(kill);
    }
    free (q);

    q = NULL;

    assert(q == NULL);
    return q;
}