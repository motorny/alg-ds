#define _CRT_SECURE_NO_WARNINGS

#include "list_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	list_p* list1 = NULL;
	list_p* list2 = NULL;
	list_p* list3 = NULL;
	FILE* file1 = NULL;
	FILE* file2 = NULL;
	FILE* file3 = NULL;
	//FILE* file4 = NULL;
	//FILE* file5 = NULL;
	char word[20];

	file1 = fopen("input1.txt", "r");

	if (file1 == NULL) {
		printf("The file error");
		return 2;
	}

	fscanf(file1, "%s", word);

	list1 = InitList(word);

	while (!feof(file1)) {
		fscanf(file1, "%s", word);
		Add2List(&list1, word);
	}

	fclose(file1);

	file2 = fopen("input2.txt", "r");

	if (file2 == NULL) {
		printf("The file error");
		return 2;
	}


	fscanf(file2, "%s", word);

	list2 = InitList(word);

	while (!feof(file2)) {
		fscanf(file2, "%s", word);
		Add2List(&list2, word);
	}

	fclose(file2);

	file3 = fopen("output.txt", "w");
	list3 = list1;

	/*
	file4 = fopen("output1.txt", "w");
	file5 = fopen("output2.txt", "w");
	PrintList(list1, file4);
	PrintList(list2, file5);
	fclose(file4);
	fclose(file5);
	*/

	UnionAndPrintList(list3, list2, file3);
	fclose(file3);

	DeleteList(list2);
	DeleteList(list1);

	return 0;
}