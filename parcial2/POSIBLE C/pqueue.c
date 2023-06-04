#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node **array;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};

static float calculate_priority(float average_grade, unsigned int approved_courses) {
    // Implementa la lógica para calcular la prioridad del nodo
    // Puedes usar la fórmula que corresponda a tu aplicación
    // y ajustarla según tus necesidades
    return average_grade * approved_courses;
}

static struct s_node *create_node(pqueue_elem e, float average_grade, unsigned int approved_courses) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = calculate_priority(average_grade, approved_courses);
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pqueue q) {
    bool res = q != NULL;
    if (res) {
        // Verifica que el tamaño de la cola sea correcto
        res = q->size >= 0;

        // Verifica la propiedad fundamental de la cola de prioridades
        for (int i = 1; i < q->size; i++) {
            float currPriority = q->array[i]->priority;
            float prevPriority = q->array[i - 1]->priority;
            res = currPriority >= prevPriority;
            if (!res) {
                break;
            }
        }
    }
    return res;
}


pqueue pqueue_empty(void) {
    pqueue q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    q->array = NULL; // Inicializa el array a NULL, se asignará memoria dinámicamente en pqueue_enqueue
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, float average_grade, unsigned int approved_courses) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);

    // Incrementa el tamaño de la cola
    q->size++;

    // Reasigna memoria para el array de nodos con el nuevo tamaño
    q->array = realloc(q->array, sizeof(struct s_node *) * q->size);

    // Inserta el nuevo nodo en la posición correcta según su prioridad
    int i = q->size - 1;
    while (i > 0 && new_node->priority < q->array[i - 1]->priority) {
        q->array[i] = q->array[i - 1];
        i--;
    }
    q->array[i] = new_node;

    assert(invrep(q));
    return q;
}

unsigned int pqueue_peek_approved_courses(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->array[0]->approved_courses;
}

float pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->array[0]->priority;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *kill = q->array[0];
    
    // Desplaza los nodos restantes hacia arriba
    for (int i = 0; i < q->size - 1; i++) {
        q->array[i] = q->array[i + 1];
    }

    // Decrementa el tamaño de la cola
    q->size--;

    // Reasigna memoria para el array de nodos con el nuevo tamaño
    q->array = realloc(q->array, sizeof(struct s_node *) * q->size);

    // Libera el nodo desencolado
    destroy_node(kill);

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));

    // Libera cada nodo
    for (int i = 0; i < q->size; i++) {
        destroy_node(q->array[i]);
    }

    // Libera el array y la cola de prioridades
    free(q->array);
    free(q);

    return NULL; // Retorna NULL para indicar que la cola se ha destruido
}
