#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
int main() {
	ArrayStack_t* stek;
	int arra[4] = {3, 4, 2, 3};
	error_t* errr = (error_t*)malloc(sizeof(error_t));
	if (errr == NULL)
		return 2;
	*errr = 0;
	stek = CreateArrayStack(errr);
	if (*errr != 0) {
		printf("ERROR");
		return 2;
	}
	PushArrayStack(stek, 5, errr);
	PushArrayStack(stek, 4, errr);
	
	printf("%d\n", PopArrayStack(stek, errr));

	printf("%d\n", PopArrayStack(stek, errr));
	
	printf("%d\n", PopArrayStack(stek, errr));
	printf("%d\n", *errr);
	
	
	for (int i = 0; i < 10; i++) {
		PushArrayStack(stek, i, errr);
	}
	printf("gg");

	
	printf("%d\n", PopArrayStack(stek, errr));
	printf("%d\n", PopArrayStack(stek, errr));
	
	printf("%d\n", stek->size);
	
	DestroyArrayStack(stek);
	
	printf("New tests\n");
	ArrayStack_t str = {arra, 4, 4};
	printf("%d\n", PopArrayStack(&str, errr));
	printf("%d\n", str.top);
	printf("%d\n", str.size);
	printf("Work with liststack\n");
	ListStack_t* skex;
	skex = CreateListStack(errr);
	PushListStack(&skex, 23, errr);
	for (int i = 0; i < 23; i++) {
		PushListStack(&skex, i, errr);

	}
	
	for (int i = 0; i < 23; i++) {
		printf("%d\n", PopListStack(&skex, errr));
		printf("%d\n", PopListStack(&skex, errr));

	}
	printf("Work with array\n");
	int arr[5] = { 73, 54, 12, 23 };
	ArrayStack_t steak = { arr, 4, 5 };
	PushArrayStack(&steak, 39, errr);

	printf("%d\n", PopArrayStack(&steak, errr));
	printf("%d\n", PopArrayStack(&steak, errr));
	printf("%d\n", PopArrayStack(&steak, errr));
	printf("%d\n", PopArrayStack(&steak, errr));
	printf("%d\n", PopArrayStack(&steak, errr));
	printf("New work\n");

	ListStack_t elem1 = { 15, NULL }, elem2 = { 45, &elem1 }, elem3 = {34, &elem2};

	
	
	
	return 0;
}


