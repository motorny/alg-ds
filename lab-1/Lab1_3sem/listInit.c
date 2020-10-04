#define _CRT_SECURE_NO_WARNINGS

#include "listInit.h"
#include <string.h>
#include <stdlib.h>



myList* InitList(char* surname, char* name, char* patron) {
	myList* nMan = (myList*)malloc(sizeof(myList));
	EnterSNP(nMan, surname, name, patron);
	nMan->next = NULL;
	return nMan;
}


void DeleteList(myList* start) {
	myList* prevEl = start;
	
	myList* curEl = start->next;
	free(prevEl);
	prevEl = curEl;

	while (prevEl != NULL) {
		curEl = prevEl->next;
		free(prevEl);
		prevEl = curEl;
	}
}


enum SAME_E FindPosForMan(myList** start, SNP snp, myList** pMan, myList** nMan, enum SNP_E snp_pos) {
	myList* OfList = *start;
	*nMan = NULL;
	*pMan = NULL;
	char word[isize];
	char word2compare[isize];
	int cmpR = STRSAME;

	switch (snp_pos) {
	case SURNAME:
		strcpy(word2compare, snp.surname);
		break;
	case NAME:
		strcpy(word2compare, snp.name);
		break;
	case PATRON:
		strcpy(word2compare, snp.patron);
		break;
	}

	do {

		switch (snp_pos) {
		case SURNAME:
			strcpy(word, OfList->surname);
			break;
		case NAME:
			strcpy(word, OfList->name);
			break;
		case PATRON:
			strcpy(word, OfList->patron);
			break;
		}

		
		cmpR = strcmp(word2compare, word);

		if (cmpR == STR2B) {
			*nMan = OfList;
			break;
		}
		else if (cmpR == STR1B) {
			if (OfList->next == NULL) {
				*nMan = OfList->next;
				*pMan = OfList;
				break;
			}
			*pMan = OfList;
			OfList = OfList->next;
		}
		else {
			if (snp_pos != PATRON) {
				return SAME;
			}
			else {
				*nMan = OfList;
				return NSAME;
			}
		}

	} while (OfList != NULL);

	return NSAME;
}


myList* AddMan(myList* next, myList* pMan, char* surname, char* name, char* patron) {
	myList* nMan = (myList*)malloc(sizeof(myList));
	if (nMan == NULL)
		return NULL;

	nMan->next = next;
	if (pMan != NULL)
		pMan->next = nMan;
	EnterSNP(nMan, surname, name, patron);

	return nMan;
}


void EnterSNP(myList* man, char* surname, char* name, char* patron) {
	strcpy(man->surname, surname);
	strcpy(man->name, name);
	strcpy(man->patron, patron);
}


myList* Add2List(myList** start, SNP snp) {
	myList* OfList = *start;
	myList* nMan = NULL;
	myList* pMan = NULL;
	int pointer = 0;
	enum SAME_E fSNM_same = SAME;
	enum SNP_E snp_pos = SURNAME;
	
	do {
		fSNM_same = FindPosForMan(start, snp, &pMan, &nMan, snp_pos);

		if (fSNM_same != SAME || (snp_pos == PATRON)) {
			nMan = AddMan(nMan, pMan, snp.surname, snp.name, snp.patron);
			if (pMan == NULL)
				*start = nMan;
			snp_pos = BETW;
		}

		switch (snp_pos) {
		case BETW:
			snp_pos = SURNAME;
			break;
		case SURNAME:
			snp_pos = NAME;
			break;
		case NAME:
			snp_pos = PATRON;
			break;
		}
		//snp_pos++;
	} while (fSNM_same != NSAME);
	

	return nMan;
}

