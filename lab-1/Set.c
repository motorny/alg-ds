#include <stdlib.h>
#include <assert.h>
#include "Set.h"

Set * SetInit()
{
  Set *A;
  A = malloc(sizeof(Set));
  if (A == NULL)
    return NULL;
  A->Root = NULL;
  return A;
}

void SetAdd(Set* S, int Data)
{
  Node** El = NULL;
  Node* tmp;
  if (S == NULL)
    return NULL;
  El = &(S->Root);
  while ((*El) != NULL && (*El)->data < Data) // Untill next becomes bigger than us
    El = &((*El)->next);
  
  if ((*El) != NULL && (*El)->data == Data)
    return;
  
  tmp = malloc(sizeof(Node));
  assert(tmp);
  tmp->data = Data;
  tmp->next = (*El);
  (*El) = tmp;

  return;
}

int SetCheck(Set* S, int Data)
{
  Node* El;
  if (S == NULL)
    return 0;
  El = S->Root;
  while (El != NULL)
  {
    if (El->data == Data)
      return 1;
    El = El->next;
  }
  return 0;
}

int SetDel(Set* S, int Data)
{
  Node* El;
  if (S == NULL)
    return 0;
  El = S->Root;
  if (El != NULL && El->data == Data)
  {
    S->Root = El->next;
    free(El);
    return 1;
  }
  while (El != NULL)
  {
    if (El->next != NULL && El->next->data == Data)
    {
      Node *tmp = El->next;
      El->next = El->next->next;
      free(tmp);
      return 1;
    }
    El = El->next;
  }
  return 0;
}

Set* SetUnion(Set* S1, Set* S2)
{
  Node *El1, *El2;
  Set *Srez;
  if (S1 == NULL || S2 == NULL)
    return NULL;
  Srez = SetInit();
  if (Srez == NULL)
    return NULL;
  El1 = S1->Root;
  El2 = S2->Root;
  while (El1 != NULL && El2 != NULL)
    if (El1->data == El2->data)
    {
      SetAdd(Srez, El1->data);
      El1 = El1->next;
      El2 = El2->next;
    }
    else if (El1->data > El2->data)
    {
      SetAdd(Srez, El2->data);
      El2 = El2->next;
    }
    else
    {
      SetAdd(Srez, El1->data);
      El1 = El1->next;
    }
  while (El1 != NULL)
  {
    SetAdd(Srez, El1->data);
    El1 = El1->next;
  }
  
  while (El2 != NULL)
  {
    SetAdd(Srez, El2->data);
    El2 = El2->next;
  }
  return Srez;
}

Set * SetIntersect(Set *S1, Set *S2)
{
  Node *El1, *El2;
  Set *Srez;
  if (S1 == NULL || S2 == NULL)
    return NULL;
  Srez = SetInit();
  if (Srez == NULL)
    return NULL;
  El1 = S1->Root;
  El2 = S2->Root;
  while (El1 != NULL && El2 != NULL)
    if (El1->data == El2->data)
    {
      SetAdd(Srez, El1->data);
      El1 = El1->next;
      El2 = El2->next;
    }
    else if (El1->data > El2->data)
      El2 = El2->next;
    else
      El1 = El1->next;
  return Srez;
}

void SetFree(Set *S)
{
  Node *El;
  if (S == NULL)
    return;
  El = S->Root;
  while (El != NULL)
  {
    Node *tmp = El;
    El = El->next;
    free(tmp);
  }
  return;
}