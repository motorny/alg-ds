#include "LabC3.h"
#pragma warning (disable:4996)

void ReadAdjacencyList(adjacency_list_t* list) {
	int i;
	int curT;
	int tempT;
	char ch;

	for (i = 0; i < list->numT; i++) {
		scanf("%i%c", &curT, &ch);

		while (ch == ' ') {
			scanf("%i%c", &tempT, &ch);

			list->tops[curT].edges[list->tops[curT].numE++] = tempT;
			list->tops[tempT].edges[list->tops[tempT].numE++] = curT;
		}
	}


}


int CreateQ(queue_t* q, int size) {
	q->arr = NULL;

	if (size <= 0) {
		return FAIL;
	}

	q->arr = (int*)calloc(size, sizeof(int));

	if (q->arr == NULL) {
		return FAIL;
	}

	q->size = size;
	q->head = 0;
	q->tail = 0;

	return SUCCESS;

}

int AddInTail(queue_t* q, int nextTop) {
	if (q->arr == NULL || q->size <= q->tail) {
		return FAIL;
	}
	q->arr[q->tail++] = nextTop;
	return SUCCESS;
}

int GetFromHead(queue_t* q, int* head) {
	if (q == NULL || q->head == q->tail) {
		return FAIL;
	}
	*head = q->arr[q->head++];
	return SUCCESS;
}

void DeleteQ(queue_t* q) {
	q->head = 0;
	q->tail = 0;
	q->size = 0;
	free(q->arr);
	q->arr = NULL;

}

int BreadthFirstSearch(adjacency_list_t* list, queue_t* q) {
	int i;
	//текущая вершина
	int curT;
	//массив, чтобы посмотреть записана уже вершина или нет
	int* temp = NULL;

	if (list->tops == NULL || list->numT == 0 || q->arr ==NULL || q->size < list->numT) {
		return FAIL;
	}

	temp = (int*)calloc(list->numT, sizeof(int));
	if (temp == NULL)
		return FAIL;
	AddInTail(q, 0);
	temp[0] = HAVE;


	while (GetFromHead(q, &curT)) {

		for (i = 0; i < list->tops[curT].numE; i++) {
			if (temp[list->tops[curT].edges[i]] == NOT_HAVE) {
				AddInTail(q, list->tops[curT].edges[i]);
				temp[list->tops[curT].edges[i]] = HAVE;
			}
		}
			
		
	}

	free(temp);
	return SUCCESS;
}