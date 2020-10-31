
#include "LabA23.h"
#pragma warning(disable:4996)
unsigned int getcount(char* word) {
	unsigned int count = 0;
	while (word[count] != '\0' && count < MAX_LETTER_COUNT) {
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
		return SAME_LENGTH_WITH_HEAD;
	}
	else if ((*mylist)->CountOfLet > contofnew) {
		return NEW_HEAD;
	}
	while ((*mylist)->next) {
		if ((*mylist)->next->CountOfLet == contofnew) {
			return SAME_LENGTH;
		}
		else if ((*mylist)->next->CountOfLet > contofnew) {
			return ADD_AFTER_SELECTED_LIST;
		}
	(*mylist) = (*mylist)->next;
	}
	return ADD_AFTER_SELECTED_LIST;
}
int FindLetter(list** mylist, list* newlist, int i) {
	unsigned int count = 0;
	if (i == SAME_LENGTH_WITH_HEAD) {
		for (count; count < newlist->CountOfLet; count++) {
			if ((*mylist)->word[count] > newlist->word[count])
				return NEW_HEAD;
			else if ((*mylist)->word[count] < newlist->word[count])
				return ADD_AFTER_SELECTED_LIST;
		}
		if (count == newlist->CountOfLet)
			return ADD_AFTER_SELECTED_LIST;
	}
	while ((*mylist)->next != NULL && (*mylist)->next->CountOfLet == newlist->CountOfLet) {
		for (count=0; count < newlist->CountOfLet; count++) {
			if ((*mylist)->next->word[count] > newlist->word[count])
				return ADD_AFTER_SELECTED_LIST;
			else if ((*mylist)->next->word[count] < newlist->word[count]) {
				break;
			}
		}
		if (count == newlist->CountOfLet)
			return ADD_AFTER_SELECTED_LIST;
		*mylist = (*mylist)->next;
	}
	return ADD_AFTER_SELECTED_LIST;
}
int FindRightPlace(list** mylist, list* newlist) {
	int rightplace = FindCount(mylist, newlist->CountOfLet);
	if (rightplace == SAME_LENGTH || rightplace == SAME_LENGTH_WITH_HEAD) {
		rightplace = FindLetter(mylist, newlist, rightplace);
	}
	return rightplace;
}
void AddtoList(list** head, list* newlist) {
	list* mylist = *head;
	switch (FindRightPlace(&mylist, newlist))
		{
		case ADD_AFTER_SELECTED_LIST:
			newlist->next = mylist->next;
			mylist->next = newlist;
			break;
		case NEW_HEAD:
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
