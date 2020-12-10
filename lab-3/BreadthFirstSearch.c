#include "queue.h"

void NeighborsSort(int* arr, int size) {
	int i = 0, r = 0;
	int A = 0;
	for (i = 0; i < size; i++) {
		A = arr[i];
		r = i;
		while (A < arr[r - 1] && (r - 1) >= 0) {
			arr[r] = arr[r - 1];
			r--;
		}
		arr[r] = A;
	}
}

int ReadAdjacencyList(adjacencyList_t* list) {
	int i = 0, j = 0, k = 0;
	int count = 0; //quantity of the neighboring peaks
	char ch;
	scanf("%d\n", &list->vertexQuantity);
	list->vertexes = (vertex_t*)malloc(list->vertexQuantity * sizeof(vertex_t));
	if (!list->vertexes)
		return FAILED;

	for (i = 0; i < list->vertexQuantity; i++){
		count = 0;
		list->vertexes[i].number = (int)getchar() - ZERO_CODE;
		ch = getchar();
		while (IS_NUMBER(ch)) {
			list->vertexes[i].number = list->vertexes[i].number * FACTOR + ((int)ch - ZERO_CODE);
			ch = getchar();
		}
		list->vertexes[i].flag = NOT_VISITED;
		list->vertexes[i].neighbors = (int*)malloc(list->vertexQuantity * sizeof(int));
		if (!list->vertexes[i].neighbors) {
			for (k = i; k >= 0; k--)
				free(list->vertexes[k].neighbors);
			free(list->vertexes);
			return FAILED;
		}

		while (ch != '\n') {
			if (IS_NUMBER(ch)) {
				list->vertexes[i].neighbors[count] = (int)ch - ZERO_CODE;
				while (ch = getchar()) {
					if(IS_NUMBER(ch))
						list->vertexes[i].neighbors[count] = list->vertexes[i].neighbors[count] * FACTOR + ((int)ch - ZERO_CODE);
					else 
						break;
				}
				count++;
			}
			else
				ch = getchar();
		}
		for (j = 0; j < i; j++) { //vertexes that are already read
			for (k = 0; k < list->vertexes[j].neighborsQuantity; k++) { //finding the same number among neighbors
				if (list->vertexes[j].neighbors[k] == list->vertexes[i].number) 
					list->vertexes[i].neighbors[count++] = list->vertexes[j].number;
			}
		}

		list->vertexes[i].neighborsQuantity = count;
	}

	return FINISHED;
}

int FreeAdjacencyList(adjacencyList_t* list) {
	int i = 0;
	if (list == NULL || list->vertexes == NULL)
		return FAILED;

	for (i = 0; i < list->vertexQuantity; i++) {
		free(list->vertexes[i].neighbors);
	}
	free(list->vertexes);
	return FINISHED;
}

int BFS(adjacencyList_t* list) {
	int i = 0, j = 0, currentNum = 0, n = 0;
	queue_t queue;
	if (list == NULL || list->vertexes == NULL || CreateQueue(&queue, list->vertexQuantity) == FAILED)
		return FAILED;

	Push(&queue, list->vertexes[0].number);
	list->vertexes[0].flag = VISITED;
	
	while (queue.head < queue.tail) {
		Pop(&queue, &currentNum);
		printf("%d ", list->vertexes[currentNum].number);
		for (j = 0; j < list->vertexes[currentNum].neighborsQuantity; j++) { // not visited neighbors push to the queue
			if (list->vertexes[list->vertexes[currentNum].neighbors[j]].flag == NOT_VISITED) {
				Push(&queue, list->vertexes[currentNum].neighbors[j]);
				list->vertexes[list->vertexes[currentNum].neighbors[j]].flag = VISITED;
			}
		}
	}

	DestroyQueue(&queue);
	return FINISHED;
}

int main(void) {
	int i = 0, j = 0;
	adjacencyList_t list;
	ReadAdjacencyList(&list);

	//get sorted neighbors
	for (i = 0; i < list.vertexQuantity; i++) 
		NeighborsSort(list.vertexes[i].neighbors, list.vertexes[i].neighborsQuantity);

	BFS(&list);

	FreeAdjacencyList(&list);
	return 0;
}