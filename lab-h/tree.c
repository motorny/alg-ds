#include <stdlib.h>

#include "tree.h"

static void RightRotation(treap_t* treapNodeX, treap_t* treapNodeY) {
  treap_t* T1 = treapNodeX->left,
    * T2 = treapNodeX->right,
    * T3 = treapNodeY->right,
    * parentY = treapNodeY->parent;

  if (parentY != NULL) {
    if (parentY->left == treapNodeY)
      parentY->left = treapNodeX;
    else if (parentY->right == treapNodeY)
      parentY->right = treapNodeX;
  }

  if (T1 != NULL)
    T1->parent = treapNodeX;
  if (T2 != NULL)
    T2->parent = treapNodeY;
  if (T3 != NULL)
    T3->parent = treapNodeY;

  treapNodeX->parent = parentY;
  treapNodeX->right = treapNodeY;
  treapNodeX->left = T1;

  treapNodeY->parent = treapNodeX;
  treapNodeY->right = T3;
  treapNodeY->left = T2;
}

static void LeftRotation(treap_t* treapNodeX, treap_t* treapNodeY) {
  treap_t* T1 = treapNodeX->left,
    * T2 = treapNodeY->left,
    * T3 = treapNodeY->right,
    * parentX = treapNodeX->parent;

  if (parentX != NULL) {
    if (parentX->left == treapNodeX)
      parentX->left = treapNodeY;
    else if (parentX->right == treapNodeX)
      parentX->right = treapNodeY;
  }

  if (T1 != NULL)
    T1->parent = treapNodeX;
  if (T2 != NULL)
    T2->parent = treapNodeX;
  if (T3 != NULL)
    T3->parent = treapNodeY;

  treapNodeY->parent = parentX;
  treapNodeY->right = T3;
  treapNodeY->left = treapNodeX;

  treapNodeX->parent = treapNodeY;
  treapNodeX->right = T2;
  treapNodeX->left = T1;
}

int TreapFind(treap_t* treap, double data) {
  treap_t* tmp = treap;

  while (tmp != NULL) {
    if (tmp->data < data)
      tmp = tmp->right;
    else if (tmp->data > data)
      tmp = tmp->left;
    else
      return LABH_TRUE;
  }

  return LABH_FALSE;
}

int TreapAdd(treap_t** treap, double data) {
  treap_t* newElement = (treap_t*)malloc(sizeof(treap_t)), * tmp = *treap, * prevTmp = NULL;
  int wasMainNode = 0;

  if (newElement == NULL || TreapFind(*treap, data) == LABH_TRUE)
    return LABH_FALSE;

  newElement->data = data;
  newElement->prior = ((double)rand()) / (RAND_MAX + 1.0);
  newElement->left = newElement->right = NULL;

  // if empty list
  if (tmp == NULL) {
    newElement->parent = NULL;
    *treap = newElement;
  }
  else {
    // add newElement in tree
    while (tmp != NULL) {
      prevTmp = tmp;

      if (tmp->data < data)
        tmp = tmp->right;
      else if (tmp->data > data)
        tmp = tmp->left;
    }
    newElement->parent = prevTmp;

    if (prevTmp->data < data)
      prevTmp->right = newElement;
    else
      prevTmp->left = newElement;

    // rotate elements
    while (newElement != NULL && newElement->parent != NULL && newElement->parent->prior > newElement->prior) {
      wasMainNode = 0;
      if (newElement->parent == *treap)
        wasMainNode = 1;

      if (newElement == newElement->parent->left)
        RightRotation(newElement, newElement->parent);
      else
        LeftRotation(newElement->parent, newElement);

      if (wasMainNode)
        *treap = newElement;
    }
  }

  return LABH_TRUE;
}

int TreapRemove(treap_t** treap, double data) {
  treap_t* elementToDelete, * tmp = *treap;
  int deleteMainNodeFlag = 0;

  // find element
  while (tmp != NULL) {
    if (tmp->data < data)
      tmp = tmp->right;
    else if (tmp->data > data)
      tmp = tmp->left;
    else
      break;
  }

  // if no element
  if (tmp == NULL)
    return LABH_FALSE;

  // rotate elements
  elementToDelete = tmp;
  while (!(elementToDelete->left == NULL && elementToDelete->right == NULL)) {
    deleteMainNodeFlag = 0;
    // if we delete main node
    if (*treap == elementToDelete)
      deleteMainNodeFlag = 1;

    if (elementToDelete->left != NULL && elementToDelete->right != NULL) {
      if (elementToDelete->left->prior < elementToDelete->right->prior)
        RightRotation(elementToDelete->left, elementToDelete);
      else
        LeftRotation(elementToDelete, elementToDelete->right);
    }
    else if (elementToDelete->left == NULL)
      LeftRotation(elementToDelete, elementToDelete->right);
    else if (elementToDelete->right == NULL)
      RightRotation(elementToDelete->left, elementToDelete);

    if (deleteMainNodeFlag)
      *treap = elementToDelete->parent;
  }

  // correct parent
  if (elementToDelete->parent != NULL)
    if (elementToDelete->parent->left == elementToDelete)
      elementToDelete->parent->left = NULL;
    else
      elementToDelete->parent->right = NULL;

  if (elementToDelete == *treap) {
    free(elementToDelete);
    *treap = NULL;
  }
  else
    free(elementToDelete);
  return LABH_TRUE;
}