#define _CRT_SECURE_NO_WARNINGS

#include "list_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void EnterWord(list_p* list, char* word) {
	strcpy(list->word, word);
}

list_p* InitList(char* word) {
	list_p* fWord = (list_p*)malloc(sizeof(list_p));

	EnterWord(fWord, word);
	fWord->next = NULL;

	return fWord;
}

void DeleteList(list_p* list) {
	list_p* prevW = list;
	list_p* curW = list->next;

	free(prevW);
	prevW = curW;

	while (prevW != NULL) {
		curW = prevW->next;
		free(prevW);
		prevW = curW;
	}
}

void FindPlaceForWord(list_p** list, char word[], list_p** pWord, list_p** nWord) {
	list_p* cList = *list;
	*nWord = NULL;
	*pWord = NULL;
	int comp = EQUAL_STR;
	char temp_word[stsize];
	char word2compare[stsize];

	strcpy(word2compare, word);
	do {
		strcpy(temp_word, cList->word);
		comp = strcmp(word2compare, temp_word);
		if (comp == STR2BIG || comp == EQUAL_STR) {
			*nWord = cList;
			break;
		}
		if (comp == STR1BIG) {
			*pWord = cList;
			cList = cList->next;
		}
	} while (cList != NULL);
}

list_p* AddWord(list_p* nWord, list_p* pWord, char* word) {
	list_p* cWord = (list_p*)malloc(sizeof(list_p));
	if (cWord == NULL)
		return NULL;

	cWord->next = nWord;
	if (pWord != NULL)
		pWord->next = cWord;
	EnterWord(cWord, word);

	return cWord;
}

void Add2List(list_p** list, char word[]) {
	list_p* nWord = NULL;
	list_p* pWord = NULL;

	FindPlaceForWord(list, word, &pWord, &nWord);

	nWord = AddWord(nWord, pWord, word);
	if (pWord == NULL)
		*list = nWord;
}

void PrintList(list_p* list, FILE* file3) {
	while (list != NULL) {
		fprintf(file3, "%s\n", list->word);
		list = list->next;
	}
}

void UnionList(list_p* list2, list_p* list1) {
	char word[20];
	while (list2 != NULL)
	{
		strcpy(word, list2->word);
		Add2List(&list1, word);
		list2 = list2->next;
	}
}

void UnionAndPrintList(list_p* list1, list_p* list2, FILE* file3) {
	int comp = EQUAL_STR;
	comp = strcmp(list1->word, list2->word);

	if (comp == STR1BIG) {
		UnionList(list1, list2);
		PrintList(list2, file3);
	}
	else {
		UnionList(list2, list1);
		PrintList(list1, file3);
	}
}