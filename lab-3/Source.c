#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define KNOT_IN_END -1
typedef struct knot {
	int connectionC;
	int* connKnots;
	bool visited;
}knot;

typedef struct {
	int elementsC;
	int* elements;
}queue;

void queueInit(queue* myQueue) {
	myQueue->elementsC = 0;
	myQueue->elements = NULL;
}

void queuePush(queue* myQueue, int pushEl) {
	myQueue->elementsC++;
	myQueue->elements = realloc(myQueue->elements, myQueue->elementsC * sizeof(int));
	for (int i = myQueue->elementsC - 1; i > 0; i--) {
		myQueue->elements[i] = myQueue->elements[i - 1];
	}
	myQueue->elements[0] = pushEl;
}

int queuePop(queue* myQueue) {
	int popEl = myQueue->elements[myQueue->elementsC - 1];
	myQueue->elementsC--;
	if (myQueue->elementsC != 0)
		myQueue->elements = realloc(myQueue->elements, myQueue->elementsC * sizeof(int));
	else {
		free(myQueue->elements);
		myQueue->elements = NULL;
	}
	return popEl;
}

void InsertConnection(knot* allKnots, int knotToChange, int knotToIns) {
	int placeForKnot = KNOT_IN_END;
	int temp = -1;
	allKnots[knotToChange].connKnots = realloc(allKnots[knotToChange].connKnots, (allKnots[knotToChange].connectionC + 1) * sizeof(int));
	//—тавим соединенный узел на его место по пор€дку в массиве connKnots
	for (int i = 0; i < allKnots[knotToChange].connectionC; i++) {
		if (allKnots[knotToChange].connKnots[i] > knotToIns) {
			placeForKnot = i;
			break;
		}
	}
	if (placeForKnot != KNOT_IN_END) {
		temp = allKnots[knotToChange].connKnots[placeForKnot];
		allKnots[knotToChange].connKnots[placeForKnot] = knotToIns;
		allKnots[knotToChange].connKnots[allKnots[knotToChange].connectionC] = temp;
	}
	else {
		allKnots[knotToChange].connKnots[allKnots[knotToChange].connectionC] = knotToIns;
	}
	allKnots[knotToChange].connectionC++;
}

void GetConnections(knot* allKnots, int knotsC) {
	int knot1 = -1, knot2 = -1, pointer = 0;
	char string[5] = "", sym = '0';
	while (sym != EOF) {
		pointer = 0;
		do {
			sym = fgetc(stdin);
			string[pointer] = sym;
			pointer++;
		} while (sym != EOF && sym != '\r' && sym != '\n' && sym != ' ');
		if (sym == '\r')
			fgetc(stdin);

		knot1 = atoi(string);
		if (sym == ' ') {
			pointer = 0;
			do {
				sym = fgetc(stdin);
				string[pointer] = sym;
				pointer++;
			} while (sym != EOF && sym != '\r' && sym != '\n');
			if (sym == '\r')
				fgetc(stdin);

			knot2 = atoi(string);
			InsertConnection(allKnots, knot1, knot2);
			InsertConnection(allKnots, knot2, knot1);
		}
	}
}

void BFS(knot* allKnots, queue* myQueue) {
	int numGoKnot = -1;
	queuePush(myQueue, 0);
	allKnots[0].visited = true;
	while (myQueue->elementsC > 0) {
		numGoKnot = queuePop(myQueue);
		printf("%d ", numGoKnot);
		for (int i = 0; i < allKnots[numGoKnot].connectionC; i++) {
			if (!allKnots[allKnots[numGoKnot].connKnots[i]].visited) {
				queuePush(myQueue, allKnots[numGoKnot].connKnots[i]);
				allKnots[allKnots[numGoKnot].connKnots[i]].visited = true;
			}
		}
	}
}


int main(void) {
	int knotsC = 0;
	char sym = '0';
	int pointer = 0;
	knot* allKnots = NULL;
	queue myQueue;

	char string[20] = "";
	while (sym != EOF && sym != '\r' && sym != '\n') {
		sym = fgetc(stdin);
		string[pointer] = sym;
		pointer++;
	}
	if (sym == '\r')
		fgetc(stdin);
	knotsC = atoi(string);

	allKnots = malloc(sizeof(knot) * knotsC);
	for (int i = 0; i < knotsC; i++) {
		allKnots[i].connKnots = NULL;
		allKnots[i].connectionC = 0;
		allKnots[i].visited = false;
	}

	GetConnections(allKnots, knotsC);
	queueInit(&myQueue);
	BFS(allKnots, &myQueue);
	
	//ќсвобождаем пам€ть
	for (int i = 0; i < knotsC; i++) {
		free(allKnots[i].connKnots);
	}
	free(allKnots);

	return 0;
}