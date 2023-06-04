#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack
{
    unsigned int size;
    struct s_node **array;
};

struct s_node
{
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



/*En la representación, e1 es el primer elemento de la pila y p1 tiene la mayor prioridad. En realidad la
propiedad fundamental es que p1 ≥ p2 ≥ ... ≥ pN (notar que aquí la prioridad representada con 1 es la
mayor prioridad, y números más bajos establecen prioridades más bajas). Además, si siempre se usa la
misma prioridad, el TAD pstack debe comportarse exactamente igual a una pila común (LIFO: last input,
first output).*/
static bool invrep(pstack s) {
    bool res = s != NULL;
    if (res) {
        // Verifica que el tamaño de la pila sea correcto
        res = s->size != 0;

        // Verifica la propiedad fundamental de la pila de prioridades
        for (unsigned int i = 1; i < s->size; i++) {
            float currPriority = s->array[i]->priority;
            float prevPriority = s->array[i - 1]->priority;
            res = currPriority >= prevPriority;
            if (!res) {
                break;
            }
        }
    }
    return res;
}

pstack pstack_empty(void) {
    pstack s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    
    s->size = 0;
    s->array = NULL;
    
    return s;
}

pstack pstack_push(pstack s,
                   pstack_elem e,
                   float average_grade,
                   unsigned int approved_courses) {
    assert(invrep(s));
    
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    s->array = realloc(s->array, sizeof(struct s_node*) * (s->size + 1));
    assert(s->array != NULL);
    
    s->array[s->size] = new_node;
    s->size++;
    
    assert(invrep(s));
    return s;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    return s->array[s->size - 1]->elem;
}

float pstack_top_average_grade(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    return s->array[s->size - 1]->average_grade;
}

unsigned int pstack_top_approved_courses(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    return s->array[s->size - 1]->approved_courses;
}

float pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    return s->array[s->size - 1]->priority;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    struct s_node *pop_node = s->array[s->size - 1];
    s->array = realloc(s->array, sizeof(struct s_node*) * (s->size - 1));
    assert(s->array != NULL);
    
    destroy_node(pop_node);
    s->size--;
    
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    
    for (unsigned int i = 0; i < s->size; i++) {
        destroy_node(s->array[i]);
    }
    free(s->array);
    free(s);
    s = NULL;
    
    assert(s == NULL);
    return s;
}
