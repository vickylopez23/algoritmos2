#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size; 
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses){
    float priority = 0.0;
    priority = 0.3 * (average_grade/MAX_GRADE) + 0.7 * (approved_courses/TOTAL_COURSES);
    return priority;
}



static struct s_node *create_node(pstack_elem e,
                                  float average_grade,
                                  unsigned int approved_courses){

    struct s_node *new_node = NULL;

    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = calculate_priority (average_grade,approved_courses);
    new_node->next = NULL;
  

    return new_node;
}

static struct s_node *destroy_node(struct s_node *node){
    assert(node != NULL);

    node->next = NULL;
    free (node);
    node = NULL;
    

    assert(node == NULL);
    return node;
}




static bool invrep(pstack s){
    bool b = true;
    unsigned int aux_size = 0;
    struct s_node *count = s->front;
    struct s_node *aux = NULL;

    while (count != NULL){          //count the size
        ++aux_size;
        count = count->next;
    }

    if (s->front == NULL){          // if stack is a empty
        b = true;
    }
    else if (s->front->next == NULL){       //if stack has a one elem
        b = true;
    }           
    else{                                   //if stack has a more of one lemento
        aux = s->front;
        while (aux ->next != NULL && b){    
           b = b && aux->priority >= aux->next->priority;
           aux = aux->next;
        }
    }
    

    return s!=NULL && b && aux_size == s->size;
}

pstack pstack_empty(void){
    pstack s = malloc (sizeof (struct s_pstack));

    s->front = NULL;
    s->size = 0;
   
    return s;
}

pstack pstack_push(pstack s,
                   pstack_elem e,
                   float average_grade,
                   unsigned int approved_courses){
    assert(invrep(s));

    struct s_node *new_node = create_node (e,average_grade,approved_courses);

    if (s->front == NULL){                      //if stack is empty
        s->front = new_node;
    }
    else{                                       //if stack isnt empty
        struct s_node *post = s->front;         //pointer to next
        struct s_node *pre = NULL;              //pointer to prev

        while (post->next != NULL && new_node->priority < post->priority){
            pre = post;
            post = post->next;
        }
        
        if (s->front->priority <= new_node->priority){      //insert in the first place
            new_node->next = post;
            s->front = new_node;
        }
        else if (new_node->priority >= post->priority){  //insert betwenn of extrems
            new_node->next = post;
            pre->next = new_node;   
        }
        else{                               //insert last
            post->next =new_node;
        }
    }

    ++s->size; 
    return s;
}

bool pstack_is_empty(pstack s){
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s){
    assert(invrep(s) && !pstack_is_empty(s));

    return s->front->elem;
}

float pstack_top_average_grade(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    return s->front->average_grade;
}

unsigned int pstack_top_approved_courses(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    return s->front->approved_courses;
}

float pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    return s->front->priority;
}

unsigned int pstack_size(pstack s){
    assert(invrep(s));
    return s->size;
}

pstack pstack_copy(pstack s){
    assert(invrep(s));

    pstack new_s = pstack_empty ();
    struct s_node *aux = s->front;

    while (aux != NULL){
        new_s = pstack_push (new_s , aux->elem, aux->average_grade, aux->approved_courses);
        aux = aux->next;
    }

    return new_s;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    struct s_node *kill = NULL;

    kill = s->front;
    s->front = kill->next;
    kill = destroy_node (kill);

    --s->size;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));

    struct s_node *kill = NULL;

    while (s->front != NULL){
        kill = s->front;
        s->front = kill->next;
        kill = destroy_node (kill);
    }    

    free (s);
    s = NULL;
    assert(s == NULL);
    return s;
}