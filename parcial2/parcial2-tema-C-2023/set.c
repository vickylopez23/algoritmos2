#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct s_node {
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node *node_t;

struct s_set {
    unsigned int size;
    node_t first;
};

static bool invrep(set s) {
    unsigned int c = 0;
    node_t current = s->first;

    while (current != NULL) {
        c++;
        current = current->next;
    }

    return c == s->size;
}

static struct s_node *create_node(set_elem e) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static void *destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

/* CONSTRUCTORS */

set set_empty(void) {
    set s = malloc(sizeof(struct s_set));
    s->first = NULL;
    s->size = 0;
    return s;
}

set set_add(set s, set_elem e) {
    assert(invrep(s));

    if (!set_member(e, s)) {
        node_t new_node = create_node(e);

        if (s->first == NULL || e < s->first->elem) {
            new_node->next = s->first;
            s->first = new_node;
        } else {
            node_t current = s->first;

            while (current->next != NULL && current->next->elem < e) {
                current = current->next;
            }

            new_node->next = current->next;
            current->next = new_node;
        }

        s->size++;
    }

    return s;
}

/* OPERATIONS */

unsigned int set_cardinal(set s) {
    return s->size;
}

bool set_is_empty(set s) {
    return s->size == 0;
}

bool set_member(set_elem e, set s) {
    assert(invrep(s));

    node_t node = s->first;
    while (node != NULL && node->elem < e) {
        node = node->next;
    }

    return node != NULL && node->elem == e;
}

set set_elim(set s, set_elem e) {
    assert(invrep(s));

    if (set_member(e, s)) {
        node_t current = s->first;
        node_t previous = NULL;

        while (current != NULL && current->elem != e) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) {
            s->first = current->next;
        } else {
            previous->next = current->next;
        }

        destroy_node(current);
        s->size--;
    }

    return s;
}

set_elem set_get(set s) {
    assert(invrep(s) && !set_is_empty(s));
    return s->first->elem;
}

set_elem *set_to_array(set s) {
    assert(invrep(s));

    set_elem *arr = malloc(sizeof(set_elem) * s->size);
    node_t current = s->first;

    for (unsigned int i = 0; i < s->size; i++) {
        arr[i] = current->elem;
        current = current->next;
    }

    return arr;
}

set set_destroy(set s) {
   assert(invrep(s));
    struct s_node *killme = s->first;
    while(s->first != NULL) {
      killme = s->first;
      s->first = killme->next;
      destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;

}