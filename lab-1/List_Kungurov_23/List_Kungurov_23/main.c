#include <stdio.h>
#include <string.h>
#include "FunsForList.h"
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 1000
#pragma warning (disable: 4996)
int main(void) {
	FILE* f;
	int N;
	int K;
	DoubleLinkedList* List = CreateDoubleLinkedList();
	f = fopen("slon.txt", "r");
	if (f == NULL) {
		exit(1);
		printf("sad(");
	}
	while (!feof(f)) {
		char* word = (char*)malloc(sizeof(char) * SIZE);
		if (word == NULL)
			exit(2);
		fscanf(f,"%[ \n]%s", word);
		PutOnTheRightPlace(word,List);
	}
	fclose(f);
	scanf("%i", &N);
	PrintDoubleLinkedList(List, PrintMoreThanN,N);
	scanf("%i", &K);
	PrintDoubleLinkedList(List, PrintTheN, K);
	DeleteDoubleLinkedList(&List);
	return 0;
}