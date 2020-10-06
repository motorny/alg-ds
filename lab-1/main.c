#include "list.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	List* pList = createList();

	addNode(pList, "1", 1);
	addNode(pList, "0", 1);
	addNode(pList, "9", 1);
	addNode(pList, "2", 1);
	addNode(pList, "5", 1);

	sortInsert(pList);
	printList(pList);

	addNode(pList, "7", 1);
	addNode(pList, "4", 1);
	addNode(pList, "8", 1);
	addNode(pList, "3", 1);
	addNode(pList, "6", 1);

	sortMerge(pList);
	printList(pList);

	destroyList(pList);

	

	return 0;
}
