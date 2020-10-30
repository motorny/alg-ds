#include "LabA23.h"
#pragma warning(disable:4996)
int main(void) {
	list *head, *mylist;
	FILE* f = fopen("words.txt", "r");
	int N;
	if (!(feof(f)))
	{
		head = ReadWord(f);
		while (!(feof(f))) {
			AddtoList(&head, ReadWord(f));
		}
		mylist = head;
		while (mylist) {
			printf(mylist->word);
			printf("\n");
			mylist=mylist->next;
		}
		printf("Find words with N letters, N = ");
		if(scanf("%i", &N))
		PrintN(head, N);
		printf("Find words with more then N letters, N = ");
		if(scanf("%i", &N))
		PrintMoreN(head, N);
		FreeList(&head);
		free(head);
	}
	fclose(f);
	return 0;
}