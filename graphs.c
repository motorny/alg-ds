//i don't like working with one .c either

#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode_t {
	struct queueNode_t* next;
	struct queueNode_t* prev;
	int num;
}queueNode_t;

typedef struct queue_t{
	queueNode_t* start;
	queueNode_t* end;
}queue_t;

queue_t* createQueue() {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if (queue != NULL) {
		queue->start = NULL;
		queue->end = NULL;
	}
	return queue;
}

int push(queue_t* queue, int num) {
	queueNode_t* newNode = (queueNode_t*)malloc(sizeof(queueNode_t));
	if (newNode != NULL && queue != NULL) {
		if (queue->end == NULL) {
			queue->end = newNode;
		}
		newNode->next = queue->start;
		if (newNode->next != NULL) {
			newNode->next->prev = newNode;
		}
		newNode->prev = NULL;
		newNode->num = num;
		queue->start = newNode;
	}
	return (newNode == NULL);
}

int pop(queue_t* queue) {
	queueNode_t* temp = queue->end;
	int retval;
	if (queue == NULL || temp == NULL) {
		retval = -1;
	}
	else {
		queue->end = temp->prev;
		if (temp->prev == NULL) {
			queue->start = NULL;
		}
		else {
			queue->end->next = NULL;
		}
		retval = temp->num;
		free(temp);
	}

	return retval;
}

void destroyQueue(queue_t* queue) {
	while (queue->start != NULL) {
		pop(queue);
	}
}

int main(void) {
	int temp;
	int num;
	int n;
	int err;
	char c;
	queue_t* queue = createQueue();

	int* attendedArray;
	int** adjMatrix;

	scanf("%i", &n);
	attendedArray = (int*)malloc(n * sizeof(int));
	adjMatrix = (int**)malloc(n * sizeof(int*));

	err = queue == NULL || attendedArray == NULL || adjMatrix == NULL;
	if (!err) {
		for (int i = 0; i < n && !err; i++) {
			//initializing adjacency matrix
			adjMatrix[i] = (int*)malloc(n * sizeof(int));
			attendedArray[i] = 0;
			err = adjMatrix[i] == NULL;
			if (!err) {
				for (int j = 0; j < n; j++) {
					adjMatrix[i][j] = 0;
				}
			}
			else {
				for (int j = 0; j < i; j++) {
					free(adjMatrix[j]);
				}
			}
		}
		if (!err) {
			for (int i = 0; i < n; i++) {
				//matrices are more convinient, reading list into matrice
				scanf("%i%c", &num, &c);
				while (c == ' ') {
					scanf("%i%c", &temp, &c);
					adjMatrix[num][temp] = 1;
					adjMatrix[temp][num] = 1;
				}
			}
			for (int i = 0; !err && i < n; i++) {
				/*iterate attendancy list
					if attended -> pass
					else mark and check adjacents
						if attended -> pass
						else mark and push
					pop the queue through to null
						check adjacents
							if attended -> pass
							else mark and push*/
				if (!attendedArray[i]) {
					attendedArray[i] = 1;
					printf("%i ", i);
					for (int j = i; !err && j < n; j++) {
						if (adjMatrix[i][j] && !attendedArray[j]) {
							attendedArray[j] = 1;
							printf("%i ", j);
							err = push(queue, j);
						}
					}
				}
				while (queue->start != NULL && !err){
					temp = pop(queue);
					if (temp != -1) {
						for (int j = i; !err && j < n; j++) {
							if (adjMatrix[temp][j] && !attendedArray[j]) {
								attendedArray[j] = 1;
								printf("%i ", j);
								err = push(queue, j);
							}
						}
					}
				}
			}
		}
	}

	if (queue != NULL) {
		destroyQueue(queue);
	}
	if (attendedArray != NULL) {
		free(attendedArray);
	}
	if (adjMatrix != NULL) {
		for (int i = 0; i < n && adjMatrix[i] != NULL; i++) {
			free(adjMatrix[i]);
		}
		free(adjMatrix);
	}

	return err;
}