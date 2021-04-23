#ifndef __SET_H_
#define __SET_H_

typedef struct Set Set;
typedef struct Node Node;

struct Node
{
  int data;
  Node* next;
};

struct Set
{
  Node* Root;
};

Set * SetInit();

void SetAdd(Set *S, int Data);

int SetDel(Set* S, int Data);

int SetCheck(Set* S, int Data);

Set * SetUnion(Set* S1, Set* S2);

Set * SetIntersect(Set* S1, Set* S2);

void SetFree(Set *S);

#endif // !__SET_H_
