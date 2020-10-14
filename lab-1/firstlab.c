#include "firstlab.h"
elem_t* CreateHead() {
  elem_t* head;
  head = (elem_t*)malloc(sizeof(elem_t));
  if (head) {
    head->numElements = 0;
    head->next = NULL;
    return head;
  }
  else {
    return NULL;
  }
}
elem_t* CreateNewNode(elem_t* prev) {
  elem_t* node = (elem_t*)malloc(sizeof(elem_t));
  if (node) {
    node->numElements = 0;
    node->next = NULL;
    prev->next = node;
    return node;
  }
  else {
    return NULL;
  }
}
elem_t* GetCurrentNode(elem_t* head) {
  elem_t* current;
  if (head->next != NULL) {
    current = head->next;
    while (current->next) {
      current = current->next;
    }
    return current;
  }
  else {
    return head;
  }
}
void AddElement(elem_t* head, int elem) {
  elem_t* current;
  elem_t* node;
  current = GetCurrentNode(head);
  if (current == NULL) {
    return;
  }
  if (current->numElements == SIZE) {
    node = CreateNewNode(current);
    node->arr[0] = elem;
    node->numElements = 1;
  }
  else {
    current->arr[current->numElements] = elem;
    current->numElements++;
  }
}
void DeleteElement(elem_t* head, int num) {
  int i, n = 0, j;
  elem_t* buf;
  buf = head;
  while (buf) {
    for (i = 0; i < buf->numElements; i++) {
      n++;
      if (n == num) {
        for (j = i; j < buf->numElements - i - 1; j++) {
          buf->arr[j] = buf->arr[j + 1];
        }
        buf->numElements--;
        return;
      }
    }
    buf = buf->next;
  }
}
int GetElementNum(elem_t* head, int num) {
  int i, n = 0;
  elem_t* buf;
  buf = head;
  while (buf) {
    for (i = 0; i < buf->numElements; i++) {
      n++;
      if (n == num) {
        return buf->arr[i];
      }
    }
    buf = buf->next;
  }
  return ERROR;
}
int GetNumKey(elem_t* head, int key) {
  int i, n = 0;
  elem_t* buf;
  buf = head;
  while (buf) {
    for (i = 0; i < buf->numElements; i++) {
      if (buf->arr[i] == key) {
        n++;
        return n;
      }
      n++;
    }
    buf = buf->next;
  }
  return ERROR;
}
int GetNextElementKey(elem_t* head, int key) {
  int i, n = 0;
  elem_t* buf;
  buf = head;
  while (buf) {
    for (i = 0; i < buf->numElements; i++) {
      if (buf->arr[i] == key) {
        if (i == (buf->numElements - 1)) {
          return buf->next->arr[0];
        }
        else {
          return buf->arr[i + 1];
        }
      }
      n++;
    }
    buf = buf->next;
  }
  return ERROR;
}
int GetCountElements(elem_t* head) {
  int i, n = 0;
  elem_t* buf;
  buf = head;
  while (buf) {
    for (i = 0; i < buf->numElements; i++) {
      n++;
    }
    buf = buf->next;
  }
  return n;
}