
#include "LabA23.h"
#pragma warning(disable:4996)
unsigned int getcount(char* word) {
	unsigned int count = 0;
	while (word[count] != '\0' && count<100) {
		count += 1;
	}
	return count;
}
list* ReadWord(FILE* f) {
	list* newlist = (list*)calloc(1, sizeof(list));
	if (newlist != NULL) {
		if(fscanf(f, "%s", &newlist->word))
		newlist->CountOfLet = getcount(newlist->word);
	}
	return newlist;
}
int FindCount(list** mylist, unsigned int contofnew) {
	if ((*mylist)->CountOfLet == contofnew) {
		return -2;
	}
	else if ((*mylist)->CountOfLet > contofnew) {
		return 0;
	}
	while ((*mylist)->next) {
		if ((*mylist)->next->CountOfLet == contofnew) {
			return -1;
		}
		else if ((*mylist)->next->CountOfLet > contofnew) {
			return 1;
		}
	(*mylist) = (*mylist)->next;
	}
	return 1;
}
int FindLetter(list** mylist, list* newlist, int i) {
	unsigned int count = 0;
	if (i == -2) {
		for (count; count < newlist->CountOfLet; count++) {
			if ((*mylist)->word[count] > newlist->word[count])
				return 0;
			else if ((*mylist)->word[count] < newlist->word[count])
				return 1;
		}
		if (count == newlist->CountOfLet)
			return 1;
	}
	while ((*mylist)->next != NULL && (*mylist)->next->CountOfLet == newlist->CountOfLet) {
		for (count=0; count < newlist->CountOfLet; count++) {
			if ((*mylist)->next->word[count] > newlist->word[count])
				return 1;
			else if ((*mylist)->next->word[count] < newlist->word[count]) {
				break;
			}
		}
		if (count == newlist->CountOfLet)
			return 1;
		*mylist = (*mylist)->next;
	}
	return 1;
}
int FindRightPlace(list** mylist, list* newlist) {
	int i = FindCount(mylist, newlist->CountOfLet);
	if (i < 0) {
		i = FindLetter(mylist, newlist, i);
	}
	return i;
}
void AddtoList(list** head, list* newlist) {
	list* mylist = *head;
	switch (FindRightPlace(&mylist, newlist))
		{
		case 1:
			newlist->next = mylist->next;
			mylist->next = newlist;
			break;
		case 0:
			newlist->next = mylist;
			mylist = newlist;
			*head = mylist;
			break;
		default:
			break;
	}
}
void PrintN(list* mylist,unsigned int N) {
	while (mylist && mylist->CountOfLet < N)
		mylist = mylist->next;
	if (mylist == NULL || mylist->CountOfLet > N) {
		printf("No words with N letters\n");
	}
	else {
		while (mylist && mylist->CountOfLet == N) {
			printf(mylist->word);
			printf("\n");
			mylist = mylist->next;
		}
	}
}
void PrintMoreN(list* mylist, unsigned int N) {
	while (mylist && mylist->CountOfLet <= N)
		mylist = mylist->next;
	if (mylist == NULL) {
		printf("No words with more then N letters\n");
	}
	else {
		while (mylist) {
			printf(mylist->word);
			printf("\n");
			mylist = mylist->next;
		}
	}
}
void FreeList(list** mylist) {
	list* help;
	while ((*mylist)->next) {
		help = (*mylist)->next->next;
		free((*mylist)->next);
		(*mylist)->next = help;
		}
}
