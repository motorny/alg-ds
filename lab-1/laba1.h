#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <crtdbg.h>
typedef struct tagLIST LIST;
struct tagLIST
{
  int preoritet;
  int number;
  LIST *Next;
};
typedef struct
{
  LIST *Top, *Tail;
}QUEUE;

int Clear ( QUEUE *Q );
LIST* PushE ( QUEUE *Q );
LIST* PushB ( QUEUE *Q );
int PopE ( LIST *New, QUEUE *Q );
int PopB ( LIST *New, QUEUE *Q );