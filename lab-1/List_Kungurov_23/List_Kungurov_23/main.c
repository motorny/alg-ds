#include <stdio.h>
#include <string.h>
#include "FunsForList.h"
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 100
#define OUT_OF_MEM -1
#define SUCCESS 0
#pragma warning (disable: 4996)

int main(void) {
	FILE* f;
	int N;
	int K;
	int RESULT = 0;
	char* filename = (char*)malloc(sizeof(char) * 10);
	if (filename == NULL) {
		return OUT_OF_MEM;
	}
	DoubleLinkedList* list = CreateDoubleLinkedList(RESULT);
	if (RESULT == OUT_OF_MEM) {
		return OUT_OF_MEM;
	}
	printf("Enter the filename: \n");
	scanf("%s",filename);
	f = fopen(filename, "r");
	while (f == NULL) {
		printf("sad(\n try again: ");
		scanf("%s", filename);
		f = fopen(filename, "r");
	}
	if (f != NULL) {
		printf("File is successfully opened...Continue\n");
	}
	while (!feof(f)) {
		char* word = (char*)malloc(sizeof(char) * SIZE);
		if (word == NULL) {
			return OUT_OF_MEM;
		}
		fscanf(f, "%s %[ \n]%s", word);
		PutOnTheRightPlace(word,list);
	}
	fclose(f);
	free(filename);
	printf("Enter the number of letters (you'll see all words that consist of more letters than you've entered)\n");
	scanf("%i", &N);
	PrintDoubleLinkedListMoreThanN(list,N);
	printf("Enter the number of letters (you'll see all words that consist of the exact number of letters you've entered)\n");
	scanf("%i", &K);
	PrintDoubleLinkedListTheN(list,K);
	DeleteDoubleLinkedList(&list);
	return SUCCESS;
}