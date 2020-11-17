
#include "laba1.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <crtdbg.h>
int PopB ( LIST *New, QUEUE *Q ) {
  LIST *A;
  A = (LIST*)malloc(sizeof(LIST));
  if (Q->Top == NULL) {
	  return 0;
  }
  A = Q->Top;
  Q->Top = New;
  New->Next = A;
  return 1;
}
int PopE ( LIST *New, QUEUE *Q ) {
  LIST *A, *B;
  A = (LIST*)malloc(sizeof(LIST));
  B = (LIST*)malloc(sizeof(LIST));
  if (Q->Top == NULL) { 
	  return 0;
  }
	  for (A = Q->Top; A->Next != Q->Tail; A = A->Next);
	  B = Q->Tail;
	  A->Next = B;
	  B->Next = New;
	  Q->Tail = New;
	  New->Next = NULL;
	  return 1;
}
LIST* PushB ( QUEUE *Q ) {
  LIST *A;
  A = (LIST*)malloc(sizeof(LIST));
  A = Q->Top;
  Q->Top = A->Next;
  return A;
}
LIST* PushE ( QUEUE *Q ) {
  LIST *A, *B;
  A = (LIST*)malloc(sizeof(LIST));
  B = (LIST*)malloc(sizeof(LIST));
  B = Q->Tail;
  for(A = Q->Top;A->Next != Q->Tail; A = A->Next);
  A->Next = NULL;
  Q->Tail = A;
  return B;
}
int Clear(QUEUE* Q) {
	LIST* A, * B;
	int i = 1;


	if (Q->Top == NULL)
		return 0;
	A = Q->Top;
	while (A != NULL) {
		B = A;
		A = A->Next;
		free(B);

	} 
	
	Q->Top = NULL;
	Q->Tail = NULL;
  free(A);
  return 1;
}
