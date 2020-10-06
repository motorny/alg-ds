#include "sort.h"
#include "list.h"
#include <string.h>

static Node* _merge(List* pList, Node* pNodeFirst, int step) {//merging two supposedly sorted sublists sized step
	Node* pNodeSecond = pNodeFirst;
	Node* pNodeAux = pNodeFirst;
	int i; //iterating first sublist
	int j = 0; //iterating second sublist

	for (i = 0; i < step; i++) {
		if (pNodeSecond->next != NULL) {
			pNodeSecond = pNodeSecond->next;
		}
		else {
			return pNodeSecond;
		}
	}
	for (i = 0; i < step; i++) {
		while (j < step && pNodeSecond != NULL && strcmp(pNodeFirst->cont, pNodeSecond->cont) > 0) {
			// inserting second node before first since it's less
			j++; //j is used outside so no for loop
			pNodeAux = pNodeSecond->next;
			//attaching nodes surrounding second node
			if (pNodeAux != NULL) {
				pNodeAux->prev = pNodeSecond->prev;
				pNodeAux->prev->next = pNodeAux;
			}
			else {
				pNodeSecond->prev->next = NULL;
				pList->tail = pNodeSecond->prev; //kept list pointer for this
			}
			//attaching node before first to the second
			if (pNodeFirst->prev != NULL) {
				pNodeFirst->prev->next = pNodeSecond;
			}
			else {
				pList->head = pNodeSecond;
			}
			pNodeSecond->prev = pNodeFirst->prev; //second to one before first, or writing in the null
			pNodeFirst->prev = pNodeSecond; //first to second
			pNodeSecond->next = pNodeFirst; //second to first
			pNodeSecond = pNodeAux; //returning pointer to the second sublist
		}
		if (pNodeSecond == NULL || j >= step) {
			//so sorted sublist is done
			break;
		}
		pNodeFirst = pNodeFirst->next;
	}
	//auxilary node is supposed to point to the edge of second sublist, but at times it's not involved at all
	while (j < step && pNodeSecond != NULL) {
		pNodeSecond = pNodeSecond->next;
		j++;
	}
	return pNodeSecond; //convenient, don't have to run over there again
}


void sortMerge(List* pList) {
	//complexity: O(n*log(n))
	//merging bottom-up
	Node* pNode = pList->head;
	int listLength = 0;
	int step; //size of sublists
	int n; //size of passed part of the list

	while (pNode != NULL) {
		listLength++;
		pNode = pNode->next;
	}
	pNode = pList->head;
	for (step = 1; step < listLength; step *= 2) {//can't make 2 sublists each larger then the original one
		for (n = 0; n < listLength; n += step * 2) {
			pNode = _merge(pList, pNode, step); //merges 2 sublists and returns pointer after them
		}
		pNode = pList->head;
	}
}

void sortInsert(List* pList) {
	//complexity: O(n^2)
	Node* pNodeEdge = pList->head; //end of partially sorted list
	Node* pNodeCur = pList->head; //current node being inserted in partially sorted list
	Node* pNodeAux; //auxilary node for swapping and comparing
	Bool isNotInPlace = TRUE; //whether or not current node is on its place

	while (pNodeCur != NULL) {
		pNodeEdge = pNodeEdge->next;
		while (isNotInPlace) {
			if (pNodeCur->prev != NULL) {
				if (strcmp(pNodeCur->prev->cont, pNodeCur->cont) > 0) {
					//swap nodes
					pNodeAux = pNodeCur->prev;

					pNodeAux->next = pNodeCur->next;
					pNodeCur->prev = pNodeAux->prev;
					pNodeCur->next = pNodeAux;
					pNodeAux->prev = pNodeCur;

					//handling surrounding nodes
					if (pNodeAux->next != NULL) {
						pNodeAux->next->prev = pNodeAux;
					}
					if (pNodeCur->prev != NULL) {
						pNodeCur->prev->next = pNodeCur;
					}

					//checking place within list struct
					if (pList->head == pNodeAux) {
						pList->head = pNodeCur;
					}
					else if (pList->tail == pNodeCur){
						pList->tail = pNodeAux;
					}
				}
				else {
					//next is more but previous is less, node is on its place
					isNotInPlace = FALSE;
				}
			}
			else {
				//node is the smallest in sublist
				isNotInPlace = FALSE;
			}
		}
		isNotInPlace = TRUE;
		pNodeCur = pNodeEdge;
	}


}