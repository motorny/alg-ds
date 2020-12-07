#include <stdio.h>
#include <stdlib.h>


#define MALLOC_ERROR 1
#define EMPTY 1;

int** memA(int n, int *e) { // выделение памяти для двумерного массива


	int i;

	int** A = (int**)malloc(n * sizeof(int*));
	if (A == NULL) {
		*e = MALLOC_ERROR;
		return NULL;
	}

	for (i = 0; i < n; i++) {
		A[i] = (int*)malloc(n * sizeof(int));
		if (A[i] == NULL) {
			*e = MALLOC_ERROR;
			return NULL;
		}
	}


	return A;

}

int* mem(int n, int *e) { // выделение памяти для массива


	int i;

	int* A = (int*)malloc(n * sizeof(int*));
	if (A == NULL) {
		*e = MALLOC_ERROR;
		return NULL;
	}
	return A;
}

int push(int* q, int *it, int a) {
	
	q[*it] = a;
	*it = *it + 1;

	return 0;
	
}

int pop(int* q, int *it) { // взять 1 элемент из очереди

	int i, a;

	a = q[0];

	for (i = 0; i < *it; i++){
		
		q[i] = q[i + 1];
	}
	*it = *it - 1;

	return a;
	
}

int input(int **A) {

	int a, b,i=0;

	while (!feof(stdin) && 2 == scanf("%d %d %*[ \n]", &a, &b)) {

		//c = fscanf(stdin,"%d%d", &a,&b);
		//if (c == -1) break;

		A[a][b] = 1;
		A[b][a] = 1;
		i++;
	}

	return i;
}

int BFS(int** A, int n) {

	int e = 0, i = 0, g, it = 0;
	int * queue, * B;

	queue = mem(n, &e);
	B = mem(n, &e);

	printf("%d ", 0);
	
	push(queue, &it, 0);
	B[0] = 1;
	

	while (it > 0) {

		g = pop(queue, &it);
		

		for (i = 0; i < n; i++) {
			if (A[g][i] == 1 && B[i] != 1) {
				push(queue, &it, i);
				B[i] = 1;
				printf("%d ", i);
			}
		}

	}

	return it;

}

int main() {

	int n,e =0,i=0,j,a,b,g, it=0,c;
	int** A, *queue,*B;

	scanf("%d", &n);
	//getc(stdin);

	A = memA(n, &e);

	input(A);
	BFS(A,n);
	
	return 0;
}