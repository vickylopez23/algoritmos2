#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left; //rama izquierda
    struct _s_abb *right; //rama derecha
};

//static bool elem_eq(abb_elem a, abb_elem b) {
 //   return a == b;
//}

//static bool elem_less(abb_elem a, abb_elem b) {
//    return a < b;
//}

static bool invrep(abb tree) {
      return tree == NULL ||
           // El arbol a la izquierda es valido
           ((tree->left == NULL || (tree->elem > abb_max(tree->left) && invrep(tree->left))) &&
           // El arbol a la derecha es valido
           (tree->right == NULL || (tree->elem < abb_min(tree->right) && invrep(tree->right))));
}


abb abb_empty(void)
{
  abb tree;
  tree = NULL;
  assert(invrep(tree) && abb_is_empty(tree));
  return tree;
}

abb abb_add(abb tree, abb_elem e)
{
  assert(invrep(tree));
  /*
   * Needs implementation
   */
  if (abb_is_empty(tree)) {
    tree = malloc(sizeof(struct _s_abb));
    tree->elem = e;
    tree->left = abb_empty();
    tree->right = abb_empty();

  } else if (e < tree->elem) {
    tree->left = abb_add(tree->left, e);
  } else if (e > tree->elem) {
    tree->right = abb_add(tree->right, e);
  }
  assert(invrep(tree) && abb_exists(tree, e));
  return tree;
}

bool abb_is_empty(abb tree)
{
  // bool is_empty = false;
  assert(invrep(tree));
  /*
   * Needs implementation
   */
  return (tree == NULL);
  // return is_empty;
}

bool abb_exists(abb tree, abb_elem e)
{
  bool exists = false;
  assert(invrep(tree));
  /*
   * Needs implementation
   */
  if (tree != NULL) {
    exists = (tree->elem == e);
    exists |= (tree->elem > e) && abb_exists(tree->left, e);
    exists |= (tree->elem < e) && abb_exists(tree->right, e);
  }
  return exists;
}

unsigned int abb_length(abb tree)
{
  unsigned int length = 0;
  assert(invrep(tree));
  /*
   * Needs implementation
   */
  if (!abb_is_empty(tree)) {
    length += 1 + abb_length(tree->left) + abb_length(tree->right);
  }
  assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
  return length;
}

abb _del_max(abb tree)
{
  abb left;
  if (abb_is_empty(tree->right)) {
    left = tree->left;
    free(tree);
    tree = left;
  } else {
    tree->right = _del_max(tree->right);
  }
  return tree;
}

abb abb_remove(abb tree, abb_elem e)
{
  assert(invrep(tree));
  abb_elem tree_elem = tree->elem;
  if (!abb_is_empty(tree)) {
    if (tree_elem < e) {
      tree->right = abb_remove(tree->right, e);
    } else if (tree_elem > e) {
      tree->left = abb_remove(tree->left, e);
    } else if ((e == tree_elem) && abb_is_empty(tree->left)) {
      abb right = tree->right;
      free(tree);
      tree = right;

    } else {
      tree->elem = abb_max(tree->left);
      _del_max(tree->left);
    }
  }
  bool tmp = invrep(tree);
  assert(tmp && !abb_exists(tree, e));
  return tree;
}

abb_elem abb_root(abb tree)
{
  abb_elem root;
  assert(invrep(tree) && !abb_is_empty(tree));
  /*
   * Needs implementation
   */
  root = tree->elem;
  assert(abb_exists(tree, root));
  return root;
}

abb_elem abb_max(abb tree)
{
  abb_elem max_e;
  assert(invrep(tree) && !abb_is_empty(tree));
  /*
   * Needs implementation
   */
  if (abb_is_empty(tree->right)) {
    max_e = tree->elem;
  } else {
    max_e = abb_max(tree->right);
  }
  assert(invrep(tree) && abb_exists(tree, max_e));
  return max_e;
}

abb_elem abb_min(abb tree)
{
  abb_elem min_e;
  assert(invrep(tree) && !abb_is_empty(tree));
  /*
   * Needs implementation
   */
  if (abb_is_empty(tree->left)) {
    min_e = tree->elem;
  } else {
    min_e = abb_min(tree->left);
  }
  assert(invrep(tree) && abb_exists(tree, min_e));
  return min_e;
}

void abb_dump(abb tree)
{
  assert(invrep(tree));
  if (tree != NULL) {
    abb_dump(tree->left);
    printf("%d ", tree->elem);
    abb_dump(tree->right);
  }
}

abb abb_destroy(abb tree)
{
  assert(invrep(tree));
  /*
   * Needs implementation
   */
  if (tree == NULL) {
    return tree;
  }

  if (!abb_is_empty(tree->left)) {
    abb_destroy(tree->left);
  }

  if (!abb_is_empty(tree->right)) {
    abb_destroy(tree->right);
  }

  free(tree);
  tree = NULL;
  assert(tree == NULL);
  return tree;
}
