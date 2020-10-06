#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* createList() {
	List* pList;
	
	pList = (List*)malloc(sizeof(List));
	if (pList != NULL) {
		pList->head = NULL;
		pList->tail = NULL;
	}

	return pList;
}

Bool addNode(List* pList, const char* str, int n){
	Node* pNode = (Node*)malloc(sizeof(Node));
	Bool hasSucceded = (Bool) (pNode != NULL);

	if (hasSucceded) {
		pNode->cont = (char*)malloc((n + 1) * sizeof(char));
		hasSucceded = (Bool) (pNode->cont != NULL);
		if (hasSucceded) {
			strcpy(pNode->cont, str);
			pNode->next = NULL;

			if (pList->head == NULL) {//then put in head
				pNode->prev = NULL;
				pList->head = pNode;
			}
			else if (pList->tail == NULL) {//then put in tail
				pNode->prev = pList->head;
				pList->head->next = pNode;
				pList->tail = pNode;
			}
			else {//attach to tail
				pNode->prev = pList->tail;
				pList->tail->next = pNode;
				pList->tail = pNode;
			}
		}
		else {
			free(pNode);
		}
	}
	return hasSucceded;
}


void destroyList(List* pList) {
	Node* pNode = pList->head;
	Node* pNodeAux;

	while (pNode != NULL) {
		pNodeAux = pNode->next;
		if (pNode->cont != NULL) {
			free(pNode->cont);
		}
		free(pNode);
		pNode = pNodeAux;
	};

	free(pList);
};
void printList(List* pList) {
	Node* pNode = pList->head;
	while (pNode != NULL) {
		printf("%s\n", pNode->cont);
		pNode = pNode->next;
	}
	printf("\n");
};