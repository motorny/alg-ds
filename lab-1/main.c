#include "queuePriority.h"

#define N 10
//#define N 0

int main(void) {
	int arr[N] = { 1,3,5,7,9,11,13,15,17,19};
	//int* arr = NULL;
	int el1 = 4, el2 = 8, el3 = 7, priority1 = 4, priority2 = 0, max = 0, min = 0;
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	queuePrior_t* queue = NULL;
	error_t error = 0;

	printf("Create a priority queue\n");
	//printf("Create an empty queue\n");
	queue = InitQueuePriority(arr, N, &error);
	if (error) {
		printf("ERROR: queue is empty\n\n");
		error = 0;
	}
	else
		PrintQueue(queue, N);


	printf("Add an element %d with priority %d:\n", el1, priority1);
	InsertEl(queue, queue1, queue2, el1, N, priority1, &error);
	if (error) {
		printf("ERROR: no queue to add an element\n\n");
		error = 0;
	}
	else if (priority1 == N) {
		PrintQueue(queue, N + 1);
		DeleteQueue(queue, N + 1, &error);
		free(queue1);
		free(queue2);
	}
	else {
		PrintQueue(queue1, N + 1);
		DeleteQueue(queue1, N + 1, &error);
		free(queue2);
		free(queue);
	}

	queue = InitQueuePriority(arr, N, &error);
	max = FindMax(queue, &error);
	printf("Find the max element in the priority queue\n");
	if (error) {
		printf("ERROR: max is not found\n\n");
		error = 0;
	}
	else
		printf("The first element in the priority queue is %d\n\n", max);


	DeleteMax(queue, &error);
	printf("Delete the first element\n");
	if (error) {
		printf("ERROR: no element to delete\n\n");
		error = 0;
	}
	else
		PrintQueue(queue, N);
	DeleteQueue(queue, N - 1, &error);


	queue = InitQueuePriority(arr, N, &error);
	min = FindMin(queue, &error);
	printf("Find the min element in the priority queue\n");
	if (error) {
		printf("ERROR: min is not found\n\n");
		error = 0;
	}
	else
		printf("The last element in the priority queue is %d\n\n", min);
	

	printf("Add an element %d at the end of the priority queue\n", el2);
	InsertEnd(queue, el2, &error);
	if (error) {
		printf("ERROR: no queue to insert at the end\n\n");
		error = 0;
	}
	else
		PrintQueue(queue, N + 1);
	DeleteQueue(queue, N + 1, &error);


	printf("Find the element %d in the priority queue\n", el3);
	queue = InitQueuePriority(arr, N, &error);
	priority2 = FindEl(queue, N, el3, &error);
	if (error) {
		printf("ERROR: element is not found\n\n");
		error = 0;
	}
	else
		printf("Priority of the element %d is %d\n\n", el3, priority2);


	DeleteQueue(queue, N, &error);
	if (error) {
		printf("ERROR: queue is already empty\n\n");
		error = 0;
	}
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	return 0;
}