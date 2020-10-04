#define _CRT_SECURE_NO_WARNINGS

#include "listInit.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListFinding.h"

void StrSearchAnalys(SNP* searchSNP, char* search) {
	int pointer = 0;
	
	for (int i = 0; i < 3; i++) {
		if (search[pointer] == ' ') {
			switch (i) {
			case 0:
				strcpy(searchSNP->surname, "");
				break;
			case 1:
				strcpy(searchSNP->name, "");
				break;
			case 2:
				strcpy(searchSNP->patron, "");
				break;
			}
			pointer+=2;
		}
		else {
			switch (i) {
			case 0:
				sscanf(search + pointer, "%s", searchSNP->surname);
				break;
			case 1:
				sscanf(search + pointer, "%s", searchSNP->name);
				break;
			case 2:
				sscanf(search + pointer, "%s", searchSNP->patron);
				break;
			}
			while (search[pointer] != ' ')
				pointer++;
			pointer++;
		}
	}
	
}


int SearchCompare(myList* man, SNP searchSNP) {
	int length = 0;

	if (searchSNP.surname != '\0') {
		length = strlen(searchSNP.surname);
		for (int i = 0; i < length; i++)
			if (searchSNP.surname[i] != man->surname[i])
				return -1;
	}
	if (searchSNP.name != '\0') {
		length = strlen(searchSNP.name);
		for (int i = 0; i < length; i++)
			if (searchSNP.name[i] != man->name[i])
				return -1;
	}
	if (searchSNP.patron != '\0') {
		length = strlen(searchSNP.patron);
		for (int i = 0; i < length; i++)
			if (searchSNP.patron[i] != man->patron[i])
				return -1;
	}

	return 1;

}


myList** SearchInList(myList* start, SNP searchSNP) {
	int memSize = 10;
	myList** searchList = (myList**)malloc(sizeof(myList) * memSize);
	myList* man = start;
	int slCount = 0;

	while (man!=NULL) {
		if (SearchCompare(man, searchSNP) > 0) {
			if (memSize <= slCount)
				searchList = (myList**)realloc(searchList, sizeof(myList) * memSize);

			searchList[slCount] = man;
			slCount++;
		}
		man = man->next;

	}
	searchList[slCount] = NULL;
	return searchList;
}


void PrintSearch(myList** searchList) {
	int pointer = 0;
	while (searchList[pointer] != NULL) {
		printf("%s %s %s\n", searchList[pointer]->surname, searchList[pointer]->name, searchList[pointer]->patron);
		pointer++;
	}
}


void ClearSearch(myList** searchList) {
	free(searchList);
}

