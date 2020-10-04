#define _CRT_SECURE_NO_WARNINGS

#include "listInit.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListFinding.h"

void PrintList(myList* man)
{
	while (man != NULL)
	{
		printf("%s %s %s\n", man->surname, man->name, man->patron);
		man = man->next;
	}
}

int main(int argc, char* argv[]) {
	myList *start = NULL, *nMan = NULL;
	myList** searchList = NULL;
	FILE* file = NULL;
	SNP snp, searchSNP;
	char buf[20], filename[50], search[40];
	char* word;

	switch (argc) {
	case 1: {
		printf("Enter filename.\n");
		scanf("%s", filename);
		//Быстрый ввод для удобства
		if (filename[0] == '1')
			strcpy(filename, "D:\\Programms\\ForLab1_3sem\\List.txt");
		//
		break;
	}
	case 2: {
		strcpy(filename, argv[1]);
		break;
	}
	default: {
		printf("Not correct list of files!");
		return 1;
	}
	}


	file = fopen(filename, "r");

	if (file == NULL) {
		printf("The file manList wasn't open");
		return 2;
	}

	//ВВодим первого в список
	fscanf(file, "%s", snp.surname);
	fscanf(file, "%s", snp.name);
	fscanf(file, "%s", snp.patron);

	start = InitList(snp.surname, snp.name, snp.patron);
	////

	///////
	strcpy(snp.surname, "dd");
	strcpy(snp.name, "ee");
	strcpy(snp.patron, "ff");
	Add2List(&start, snp);
	Add2List(&start, snp);
	//////

	while (!feof(file)) {
		fscanf(file, "%s", snp.surname);
		fscanf(file, "%s", snp.name);
		fscanf(file, "%s", snp.patron);
		nMan = Add2List(&start, snp);
	}

	PrintList(start);

	printf("\nEnter search params...\n");
	/*scanf("%s %s %s", snp.surname, snp.name, snp.patron);*/
	
	//fgetsДва раза потому, что он читает \n в начале
	fgets(search, 40, stdin);
	fgets(search, 40, stdin);
	StrSearchAnalys(&searchSNP, search);
	searchList = SearchInList(start, searchSNP);
	PrintSearch(searchList);
	ClearSearch(searchList);

	DeleteList(start);
	fclose(file);
	return 0;
}
