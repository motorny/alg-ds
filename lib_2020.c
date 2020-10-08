//#include "stdafx.h"
//#include "lid_2020.h"
//#include <stdio.h>
//#include <stdint.h>
//#include <string.h>
//#pragma warning(disable:4996)
//
//struct poly_t
//{
//	int degree;
//	int *terms;
//};
//
//static int    polyValid(poly *p, size_t i);
//static poly   *polyBigger(poly *p1, poly *p2);
//static poly   *polySmaller(poly *p1, poly *p2);
//static poly   *polyZero(void);
//static poly   *polyReduce(poly *p);
//
//
//poly *polyCreate(int n)
//{
//	poly *p = malloc(sizeof(struct poly_t));
//	if (!p) return NULL;
//
//	p->terms = calloc(n + 1, sizeof(double));
//	if (!p->terms) {
//		free(p);
//		return NULL;
//	}
//
//	p->degree = n;
//
//	return p;
//}
//
//void polyDestroy(poly *p)
//{
//	if (p == NULL) return;
//
//	free((p)->terms);
//	free(p);
//
//	p = NULL;
//}
//
//void polySetDegree(poly *p, int i, int a)
//{
//	if (p == NULL || !polyValid(p, i)) return;
//
//	p->terms[i] = a;
//
//	if (a == 0.0) p = polyReduce(p);
//}
//
//int polyGetCoeff(poly *p, int i)
//{
//	if (p == NULL || !polyValid(p, i)) return 0;
//	return p->terms[i];
//}
//
//poly* polyFrom(int n, ...) {
//	poly* result;
//	result = polyCreate(n);
//	for (int i =0, *ptr = &n; i < n+1; i++) {
//		polySetDegree(result, i, *(++ptr));
//	}
//	return result;
//}
//
//poly* polyParse(const char *str) {
//	int *coefficient;
//	poly *result;
//	coefficient = malloc(sizeof(int)*1000);
//
//	char *p = strtok(str, "+");
//	int a = 1;
//	while (p)
//	{
//		int z = 0;
//		while (p[z] != 'x')
//			z++;
//		char *temp;
//		temp = malloc(sizeof(char)*z);
//		strncpy(temp, p, z);
//		coefficient[a] = atoi(temp);
//		p = strtok(NULL, "+");
//		a++;
//	}
//	coefficient[0] = a-2;
//	result = polyFrom(*coefficient);
//	for (int i = 0; i < coefficient[0]+1; i++) {
//		polySetDegree(result, i, coefficient[i+1]);
//	}
//	return result;
//}
//
//
//void polyFormat(poly *p,char* str) {
//	int N = 5000;
//	char *temp;
//	char *num;
//	temp = calloc(N, sizeof(char));
//	num = malloc(sizeof(char) * 20);
//	for (int i = 0; i < p->degree+1; i++)
//	{
//		if (p->terms[i] >= 0 && i != 0)
//			sprintf(num, "+%i*x^%i", p->terms[i], i );
//		else
//			sprintf(num, "%i*x^%i", p->terms[i], i );
//		snprintf(str, sizeof str*N, "%s%s", temp, num);
//		temp = str;
//	}
//	free(num);
//}
//
//poly* polyRead(FILE* p) {
//	int N = 5000;
//	poly* result = NULL;
//	char *str;
//	str = malloc(sizeof(char)*N);
//	if (p == NULL)
//	{
//		printf("Not able to open the file");
//	}
//	else
//	{
//		while (fgets(str, N, p) != NULL);
//		result = polyParse(str);
//	}
//	return result;
//}
//
//void polyWrite(FILE* f, poly *p) {
//	char *str=malloc(sizeof(str)*1000);
//	if (f == NULL)
//	{
//		printf("Not able to open the file");
//	}
//	else
//	{
//		polyFormat(p,str);
//		fwrite(str, sizeof(char), strlen(str), f);
//		free(str);
//	}
//}
//
//char* polyElement(poly* poly, int i) {
//	char* str = malloc(sizeof(char) * 20);
//	int res = polyGetCoeff(poly, i);
//	sprintf(str, "%i*x^%i", res, i);
//	return str;
//}
//
//double polyEvaluale(poly *p, double x)
//{
//	if (p == NULL) return 0.0;
//
//	double result = 0;
//
//	size_t i = p->degree + 1;
//
//	while (i--) result = result * x + p->terms[i];
//
//	return result;
//}
//
//poly *polyAdd(poly *p1, poly *p2)
//{
//	if (p1 == NULL || p2 == NULL) return NULL;
//
//	poly *smaller = polySmaller(p1, p2);
//	poly *bigger = polyBigger(p1, p2);
//
//	size_t n = smaller->degree;
//	size_t m = bigger->degree;
//
//	poly *result = polyCreate(m);
//	if (!result) return NULL;
//
//	size_t i;
//
//	for (i = 0; i <= n; i++)
//		result->terms[i] = p1->terms[i] + p2->terms[i];
//
//	for (i = n + 1; i <= m; i++)
//		result->terms[i] = bigger->terms[i];
//
//	return polyReduce(result);
//}
//
//poly *polySub(poly *p1, poly *p2)
//{
//	if (p1 == NULL || p2 == NULL) return NULL;
//
//	poly *smaller = polySmaller(p1, p2);
//	poly *bigger = polyBigger(p1, p2);
//
//	size_t n = smaller->degree;
//	size_t m = bigger->degree;
//
//	poly *result = polyCreate(m);
//	if (!result) return NULL;
//
//	size_t i;
//
//	for (i = 0; i <= n; i++)
//		result->terms[i] = p1->terms[i] - p2->terms[i];
//
//	for (i = n + 1; i <= m; i++)
//		result->terms[i] = (p1 == smaller ? -1 : 1) * bigger->terms[i];
//	return polyReduce(result);
//}
//
//poly *polyMul(poly *p1, poly *p2)
//{
//	if (p1 == NULL || p2 == NULL) return NULL;
//
//	poly *result = polyCreate(p1->degree + p2->degree);
//	if (!result) return NULL;
//
//	for (size_t i = 0; i <= p1->degree; i++)
//		for (size_t j = 0; j <= p2->degree; j++)
//			result->terms[i + j] += p1->terms[i] * p2->terms[j];
//
//	return polyReduce(result);
//}
//
//poly *polyMulInt(poly *p, int c)
//{
//	if (p == NULL) return NULL;
//	if (c == 0) return polyZero();
//
//	poly *result = polyCreate(p->degree);
//	if (!result) return NULL;
//
//	for (size_t i = 0; i <= p->degree; i++)
//		result->terms[i] = p->terms[i] * c;
//
//	return result;
//}
//
//static int polyValid(poly *p, int i)
//{
//	if (p == NULL) return 0;
//	if (i >= p->degree + 1) return 0;
//
//	return 1;
//}
//
//static poly *polyBigger(poly *p1, poly *p2)
//{
//	if (p1 == NULL || p2 == NULL) return NULL;
//
//	return (p1->degree > p2->degree) ? p1 : p2;
//}
//
//static poly *polySmaller(poly *p1, poly *p2)
//{
//	if (p1 == NULL || p2 == NULL) return NULL;
//
//	return (p1->degree > p2->degree) ? p2 : p1;
//}
//
//static poly *polyZero()
//{
//	return polyCreate(0);
//}
//
//static poly *polyReduce(poly *p)
//{
//	if (p == NULL) return NULL;
//
//	int degree = p->degree;
//
//	while (degree > 0 && p->terms[degree] == 0) degree--;
//
//	if (degree != p->degree)
//		p->terms = realloc(p->terms, (degree + 1) * sizeof(double));
//
//	p->degree = degree;
//
//	return p;
//}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lid_2020.h"

struct LIST
{
	char *str;
	struct LIST *next;
	struct LIST* prev;
};

void Split(LIST_T* head, LIST_T** first, LIST_T** second)
{
	LIST_T * front, *back;
	if (head == NULL || head->next == NULL) 
	{
		(*first) = NULL;
		(*second) = NULL;
		return;
	}
	front = head->next;
	back = head;
	while (front != NULL)
	{
		front = front->next;
		if (front != NULL)
		{
			back = back->next;
			front = front->next;
		}
	}
	(*second) = back->next;
	(*second)->prev = NULL;
	(*first) = head;
	back->next = NULL;
}
LIST_T * Merge(LIST_T *A, LIST_T *B)
{
	LIST_T *C = NULL;
	if (A == NULL && B == NULL)
		return C;
	else if (A == NULL)
		return B;
	else if (B == NULL)
		return A;

	if ((strcmp(A->str, B->str) <= 0) ? 1 : 0)
	{
		C = A;
		C->next = Merge(A->next, B);
		C->next->prev = C;
	}
	else
	{
		C = B;
		C->next = Merge(A, B->next);
		C->next->prev = C;
	}
	return C;
}

void Sort(LIST_T **head)
{
	LIST_T *ref=*head;
	LIST_T * first = NULL, *second = NULL;
	if (ref == NULL || ref->next == NULL)
	{
		return;
	}
	Split(ref, &first, &second);
	Sort(&first);
	Sort(&second);
	*head = Merge(first, second);
}