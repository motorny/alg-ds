#include "Header.h"
#include <time.h>
#include <stdio.h>


#define N 1000000

int main() {

	queue* q1 = (queue*)malloc(sizeof(queue));
	queueM* q2= (queueM*)malloc(sizeof(queueM));
	int i,c;
	int t1, t2;

	empty(q1);
	emptyM(q2);

	t1 = clock();
	for (i = 0; i < N; i++) {
		add(q1, i);
	}
	t2 = clock();
	printf("time to fill the queue with List  == %d\n", t2 - t1);

	t1 = clock();
	for (i = N; i > 0; i--) {
		get(q1, &c);
	}
	t2 = clock();
	printf("time to free the queue with List == %d\n", t2 - t1);

	t1 = clock();
	for (i = 0; i < N; i++) {
		addM(q2, i);
	}
	t2 = clock();
	printf("time to fill the queue with Array  == %d\n", t2 - t1);

	t1 = clock();
	for (i = N; i > 0; i--) {
		getM(q2, &c);
	}
	t2 = clock();
	printf("time to free the queue with Array == %d\n", t2 - t1);
}



//при извлечении элементов из очереди намного выгоднее использовать список. При вствках правктически никакой разницы нет при малых размерах очереди. При большом количестве элементов,
// поиск памяти для массива может занять больше времени. (или вообще не найти)