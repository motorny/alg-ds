#include <stdio.h>
#include <stdlib.h>

#include "unrolledlinkedlist.h"

ullist_t* CreateList() {
	ullist_t* list = (ullist_t*)malloc(sizeof(ullist_t));
	if (list == NULL)
		return NULL;
	list->head = (node_t*)malloc(sizeof(node_t));
	if (list->head == NULL)
		return NULL;
	list->head->next = NULL;
	list->head->numElem = 0;
	return list;
}

//auxiliary function for AddElemToList and DeleteElemFromListByNum, calculates the number of the element in the node, a pointer to the node, which contains element
int _findPlaceOfElemInList(ullist_t* list, int numOfElemInList, node_t** ptrOnNodeOfElem, int* numOfElemInNode) {
	node_t* ptrOnCurrentNode = list->head;
	int numOfCurrentElemInNode;
	int counterOfListElems = 0;

	if (ptrOnCurrentNode->numElem == 0) {
		(*numOfElemInNode) = 0;
		(*ptrOnNodeOfElem) = ptrOnCurrentNode;
		return TRUE;
	}

	do {
		if (counterOfListElems + ptrOnCurrentNode->numElem < numOfElemInList) {
			counterOfListElems += ptrOnCurrentNode->numElem;
		}
		else {
			for (numOfCurrentElemInNode = 0; numOfCurrentElemInNode < ptrOnCurrentNode->numElem; numOfCurrentElemInNode++)
			{
				counterOfListElems++;
				if (counterOfListElems == numOfElemInList) {
					(*numOfElemInNode) = numOfCurrentElemInNode;
					(*ptrOnNodeOfElem) = ptrOnCurrentNode;
					return TRUE;
				}
			}
		}
		ptrOnCurrentNode = ptrOnCurrentNode->next;
	} while (ptrOnCurrentNode != NULL);

		return FALSE;
}

//auxiliary function for AddElemToList, add element to the given node
static void _insertElemIntoNode(node_t* node, int numOfElemToInsertAfter, int newElem) {
	int numOfMovingArrElem;
	for (numOfMovingArrElem = node->numElem - 1; numOfMovingArrElem > numOfElemToInsertAfter; numOfMovingArrElem--)
		node->arr[numOfMovingArrElem + 1] = node->arr[numOfMovingArrElem];
	node->arr[numOfMovingArrElem + 1] = newElem;
	node->numElem++;
}


int AddElemToList(ullist_t* list, int numOfElemToInsertAfterInList, int newElem) {
	node_t* ptrOnNodeOfElemToInsertAfter = NULL;
	int numOfElemToInsertAfterInNode;

	if (list == NULL || list->head == NULL)
		return INVALID_INPUT_DATA;

	if(_findPlaceOfElemInList(list, numOfElemToInsertAfterInList, &ptrOnNodeOfElemToInsertAfter, &numOfElemToInsertAfterInNode) == FALSE)
		return INVALID_INPUT_DATA;

	if (ptrOnNodeOfElemToInsertAfter->numElem < MAX_NUM_OF_ELEM) {   //if there is enough space in node
		_insertElemIntoNode(ptrOnNodeOfElemToInsertAfter, numOfElemToInsertAfterInNode, newElem);
	}
	else {   //if node is full
		node_t* newNode;
		int numOfElemMovingToNewArr;

		//creating new node
		newNode = (node_t*)malloc(sizeof(node_t));
		if (newNode == NULL)
			return FALSE;
		newNode->next = ptrOnNodeOfElemToInsertAfter->next;
		ptrOnNodeOfElemToInsertAfter->next = newNode;

		  //moving part of elements in new node
		for (numOfElemMovingToNewArr = (MAX_NUM_OF_ELEM + 1) / 2; numOfElemMovingToNewArr < MAX_NUM_OF_ELEM; numOfElemMovingToNewArr++)
			newNode->arr[numOfElemMovingToNewArr - (MAX_NUM_OF_ELEM + 1) / 2] = ptrOnNodeOfElemToInsertAfter->arr[numOfElemMovingToNewArr];
		ptrOnNodeOfElemToInsertAfter->numElem = MAX_NUM_OF_ELEM - MAX_NUM_OF_ELEM / 2;
		newNode->numElem = MAX_NUM_OF_ELEM - (MAX_NUM_OF_ELEM + 1) / 2;

		if (numOfElemToInsertAfterInNode < (MAX_NUM_OF_ELEM + 1) / 2) {  //if element is getting into initial node
			_insertElemIntoNode(ptrOnNodeOfElemToInsertAfter, numOfElemToInsertAfterInNode, newElem);
		}
		else {  //if element is getting into new node
			numOfElemToInsertAfterInNode -= (MAX_NUM_OF_ELEM + 1) / 2;
			_insertElemIntoNode(newNode, numOfElemToInsertAfterInNode, newElem);
		}
	}
	return TRUE;
}


int FindNumOfElemInListByKey(ullist_t* list, int key) {
	node_t* ptrOnCurrentNode;
	int numOfCurrentElemInNode;
	int numOfCurrentElemInList = 0;

	if (list == NULL || list->head == NULL)
		return INVALID_INPUT_DATA;

	ptrOnCurrentNode = list->head;

	do {
		for (numOfCurrentElemInNode = 0; numOfCurrentElemInNode < ptrOnCurrentNode->numElem; numOfCurrentElemInNode++) {
			numOfCurrentElemInList++;
			if (ptrOnCurrentNode->arr[numOfCurrentElemInNode] == key)
				return numOfCurrentElemInList;
		}
		ptrOnCurrentNode = ptrOnCurrentNode->next;
	} while (ptrOnCurrentNode != NULL);

	return  ELEM_IS_NOT_IN_THE_LIST; //function returns -2 if that list doesn't contain the element
}


int* FindElemInListByNum(ullist_t* list, int num) {
	node_t* ptrOnCurrentNode = list->head;
	int numOfCurrentElem;
	int counterOfListElems = 0;

	if (list == NULL || list->head == NULL)
		return NULL;

	do {
		if (counterOfListElems + ptrOnCurrentNode->numElem < num)
			counterOfListElems = counterOfListElems + ptrOnCurrentNode->numElem;
		else {
			for (numOfCurrentElem = 0; numOfCurrentElem < ptrOnCurrentNode->numElem; numOfCurrentElem++)
			{
				counterOfListElems++;
				if (counterOfListElems == num) {
					return &(ptrOnCurrentNode->arr[numOfCurrentElem]);
				}
			}
		}
		ptrOnCurrentNode = ptrOnCurrentNode->next;
	} while (ptrOnCurrentNode != NULL);

	return NULL;
}


int DeleteElemFromListByNum(ullist_t* list, int numOfElemToDeleteInList) {
	node_t* ptrOnNodeOfElemToDelete;
	int numOfElemToDeleteInNode;
	int numOfCurrentElemInNode;

	if (list == NULL || list->head == NULL)
		return INVALID_INPUT_DATA;

	if (list->head->numElem == 0) {
		return LIST_IS_EMPTY;  //function returns -3 if that list is empty
	}

	ptrOnNodeOfElemToDelete = list->head;

	if (_findPlaceOfElemInList(list, numOfElemToDeleteInList, &ptrOnNodeOfElemToDelete, &numOfElemToDeleteInNode) == FALSE)
		return INVALID_INPUT_DATA;

	for (numOfCurrentElemInNode = numOfElemToDeleteInNode; numOfCurrentElemInNode < ptrOnNodeOfElemToDelete->numElem - 1; numOfCurrentElemInNode++)
		ptrOnNodeOfElemToDelete->arr[numOfCurrentElemInNode] = ptrOnNodeOfElemToDelete->arr[numOfCurrentElemInNode + 1];
	ptrOnNodeOfElemToDelete->numElem--;

	//if node becomes half-empty, complete it with elements from the next one
	if (ptrOnNodeOfElemToDelete->numElem < (MAX_NUM_OF_ELEM + 1) / 2 && ptrOnNodeOfElemToDelete->next != NULL) {
		int gnttOfElemsToMove = ((MAX_NUM_OF_ELEM + 1) / 2) - ptrOnNodeOfElemToDelete->numElem;
		int numOfFirstArrPlace = ptrOnNodeOfElemToDelete->numElem;
		int numOfMovingSecondArrElem;
		//moving elements from the next node
		for (numOfMovingSecondArrElem = 0; numOfMovingSecondArrElem < gnttOfElemsToMove; numOfMovingSecondArrElem++) {
			ptrOnNodeOfElemToDelete->arr[numOfFirstArrPlace] = ptrOnNodeOfElemToDelete->next->arr[numOfMovingSecondArrElem];
			numOfFirstArrPlace++;
		}
		ptrOnNodeOfElemToDelete->numElem = numOfFirstArrPlace;
		ptrOnNodeOfElemToDelete->next->numElem -= gnttOfElemsToMove;
		//if the next node becomes half-empty, moving remaining elements in our node
		if (ptrOnNodeOfElemToDelete->next->numElem < MAX_NUM_OF_ELEM / 2) {
			for (numOfMovingSecondArrElem; numOfMovingSecondArrElem < ptrOnNodeOfElemToDelete->next->numElem + gnttOfElemsToMove; numOfMovingSecondArrElem++) {
				ptrOnNodeOfElemToDelete->arr[numOfFirstArrPlace] = ptrOnNodeOfElemToDelete->next->arr[numOfMovingSecondArrElem];
				numOfFirstArrPlace++;
			}
			ptrOnNodeOfElemToDelete->numElem = numOfFirstArrPlace;
			//deleting the next node
			node_t* ptrToDeleteNode = ptrOnNodeOfElemToDelete->next;
			ptrOnNodeOfElemToDelete->next = ptrToDeleteNode->next;
			free(ptrToDeleteNode);
		}
		//if the next node stays more that half complete, shifting elements in it
		else {
			for (numOfMovingSecondArrElem; numOfMovingSecondArrElem < ptrOnNodeOfElemToDelete->next->numElem + gnttOfElemsToMove; numOfMovingSecondArrElem++) {
				ptrOnNodeOfElemToDelete->next->arr[numOfMovingSecondArrElem - gnttOfElemsToMove] = ptrOnNodeOfElemToDelete->next->arr[numOfMovingSecondArrElem];
			}
		}
	}
	//if element is one and only in the last node in list, just deleting node 
	else if (ptrOnNodeOfElemToDelete->next == NULL && ptrOnNodeOfElemToDelete->numElem == 0 && ptrOnNodeOfElemToDelete != list->head) {
		node_t* curNode;
		curNode = list->head;
		while (curNode->next->next != NULL) {
			curNode = curNode->next;
		} 
		free(ptrOnNodeOfElemToDelete);
		curNode->next = NULL;
	}

	return TRUE;
}


int CountNumOfElements(ullist_t* list) {
	node_t* ptrOnCurrentNode;
	int counterOfListElems = 0;

	if (list == NULL || list->head == NULL)
		return INVALID_INPUT_DATA;

	ptrOnCurrentNode = list->head;

	do {
		counterOfListElems += ptrOnCurrentNode->numElem;
		ptrOnCurrentNode = ptrOnCurrentNode->next;
	} while (ptrOnCurrentNode != NULL);

	return counterOfListElems;
}


int DeleteList(ullist_t* list) {
	node_t* ptrOnCurrentNode = NULL;
	node_t* ptrOnNextNode = NULL;
	if (list == NULL || list->head == NULL)
		return INVALID_INPUT_DATA; 
	ptrOnCurrentNode = list->head;
	do {
		ptrOnNextNode = ptrOnCurrentNode->next;
		free(ptrOnCurrentNode);
		ptrOnCurrentNode = ptrOnNextNode;
	} while (ptrOnCurrentNode != NULL);
	free(list);
	return TRUE;
}

ullIter_t* CreateIterator(ullist_t* list) {
	ullIter_t* iterator;
	if (list == NULL || list->head == NULL)
		return NULL;
	iterator = (ullIter_t*)malloc(sizeof(ullIter_t));
	if (iterator == NULL)
		return NULL;
	if (list->head->numElem == 0)
		return NULL;
	iterator->list = list;
	iterator->node = list->head;
	iterator->numOfCurElemInNode = 0;
	iterator->ptrOnCurElem = &(list->head->arr[0]);
	return iterator;
}

int GetFromIterator(ullIter_t* iterator, int* gettingElem) {
	if (iterator == NULL || iterator->list == NULL || iterator->ptrOnCurElem == NULL)
		return INVALID_INPUT_DATA;
	else {
		*gettingElem = *(iterator->ptrOnCurElem);
		return TRUE;
	}
}

int NextInIterator(ullIter_t* iterator) {
	if (iterator == NULL || iterator->list == NULL || iterator->ptrOnCurElem == NULL)
		return INVALID_INPUT_DATA;
	if (iterator->numOfCurElemInNode < iterator->node->numElem - 1) {
		iterator->numOfCurElemInNode++;
		iterator->ptrOnCurElem++;
		return TRUE;
	}
	else if (iterator->numOfCurElemInNode == iterator->node->numElem - 1) {
		iterator->node = iterator->node->next;
		if (iterator->node != NULL) {
			iterator->numOfCurElemInNode = 0;
			iterator->ptrOnCurElem = &(iterator->node->arr[0]);
			return TRUE;
		}
	}
	iterator->ptrOnCurElem = NULL;
	return END_OF_THE_LIST;  //function returns -3 if that list ends
}