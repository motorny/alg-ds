#include "list.h"
#include<stdlib.h>

Node* findPlace(Node* pHead, Node* pItem){
	Node* pIt = pHead;
	while (pIt->hours > pItem->hours ||
		((pIt->hours == pItem->hours) && (strcmp(pItem->name, pIt->name) > 0))) {
		if (pIt->pPrev == END_OF_LIST) return END_OF_LIST;
		pIt = pIt->pPrev;
	}
	return pIt;
}

Node* findLastNode(Node* pHead)
{
	if (!pHead) return END_OF_LIST;
	Node* pIt = pHead;
	while (pIt->pPrev != END_OF_LIST) {
		pIt = pIt->pPrev;
	}
	return pIt;
}

void printMoreN(Node* pHead, const int N)
{
	while (pHead) {
		int surnameLength;
		if (pHead->hours > N) {
			for (surnameLength = 0; (surnameLength < MAX_NAME_SYMB); surnameLength++) {

				if (pHead->name[surnameLength] == ' ') break;
			}
			printf("%*.*s %s\n", surnameLength, surnameLength, pHead->name,pHead->date);

		}
		pHead = pHead->pPrev;
	}
}

void freeMem(Node* pHead)
{
	while (pHead) {
		Node* pNodeToDelete = pHead;
		pHead = pHead->pPrev;
		free(pNodeToDelete);
	}
}



Node* readEntry(Node* pHead, FILE* pF) {
	if (pHead == END_OF_LIST) {
		pHead = (Node*)calloc(1, sizeof(Node));
		fscanf(pF, "%s\n", pHead->date);
		fgets(pHead->name, MAX_NAME_SYMB, pF);
		fscanf(pF, "%u", &pHead->hours);

		return pHead;
	} //No elements in list
	Node tmpNode;
	fscanf(pF, "%s\n", &tmpNode.date);
	fgets(tmpNode.name, MAX_NAME_SYMB, pF);
	fscanf(pF, "%u", &tmpNode.hours);
	
	Node* pLessNode = findPlace(pHead, &tmpNode);
	Node* pNewNode = (Node*)calloc(1, sizeof(Node));

	if (pLessNode == END_OF_LIST) {
		findLastNode(pHead)->pPrev = pNewNode;
		memcpy(pNewNode, &tmpNode, sizeof(Node));
		pNewNode->pPrev = END_OF_LIST;
	}
	else {
		memcpy(pNewNode, pLessNode, sizeof(Node));
		memcpy(pLessNode, &tmpNode, sizeof(Node));
		pLessNode->pPrev = pNewNode;
	}
	return pHead;
}
