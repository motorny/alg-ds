#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "vld.h" //for finding memory limits in debug
#define SIZEBUF 100
typedef struct Queue {
	Queue* next;
	Queue* prev;
	int data;
} Queue_t;

void rec(int** mass,int n,Queue_t** start,Queue_t** end) {
	if ((*start)->next != *end) {//while queue is not empty
		
		int j =(*end)->prev->data;
		(*end)->prev->prev->next = *end;
		Queue_t* tmp = (*end)->prev->prev;
		free((*end)->prev);
		(*end)->prev = tmp;
		printf("%i ", j);

		for (size_t i = 0; i < n; i++)
		{
			if (mass[j][i] && i != j && !mass[i][n]) {
				Queue_t* q = (Queue_t*)malloc(sizeof(Queue_t));
				q->next = (*start)->next; 
				q->prev = *start;
				((*start)->next)->prev=q;
				(*start)->next = q;
				mass[i][n] = 1;
				q->data = i;
			}

		}
		rec(mass, n, start, end);
	}
	/*else {
		for (size_t i = 0; i < n; i++)
		{
			if (!mass[i][n]) {
				Queue_t* q = (Queue_t*)malloc(sizeof(Queue_t));
				(*start)->next = q;
				(*end)->prev = q;
				q->next =*end;
				q->prev = *start;
				q->data = i;
				mass[i][n] = 1;
				rec(mass, n, start, end);
				break;
		  }	 
		} 

	}*/
}
int** createArr(int n) {

  }
int main(){
int n = 0,o=0;
int a=0, b=0;
char buf[SIZEBUF];
char c;
int flag = 1;
	//scanf("%d", &n);
//FILE* f=fopen("file.txt", "rt");
//fscanf(f, "%i", &n);
char str[SIZEBUF];
	while ((c = (char)getchar()) != '\n') {
		str[o++] = c;

		}
	str[o] = 0;
	n = atoi(str);
	
	
	int** mass = (int**)malloc(n*sizeof(int*));
	for (size_t i = 0; i < n; i++)
	{
	   mass[i]=(int*)malloc((n+1)*sizeof(int));
	   for (size_t j = 0; j <= n; j++)
	   {
		   if (i != j ||i==n)		   //write zeros in the special colomn(index n)
			   mass[i][j] = 0;	 //
		   else 
			   mass[i][j] = 1;			 // to see have we visited vertex yet or not
	   }
	}
	
	flag = 1;
	o = 0;
	while ((c = (char)getchar()) != EOF) {
		buf[o++] = c;
		if (c == ' '||c=='\n') {
			buf[o] = 0;
			if(flag%2)
	    	a = atoi(buf);
			else {
				b= atoi(buf);
				mass[a][b] = 1;
				mass[b][a] = 1;
			//	printf("%i %i ",a,b);
			}
			o = 0;
			flag++;

		}
	}
	//fclose(f);

	Queue_t* start=(Queue_t*)malloc(sizeof(Queue_t));
	Queue_t* end = (Queue_t*)malloc(sizeof(Queue_t));
	Queue_t* q = (Queue_t*)malloc(sizeof(Queue_t));
	start->next = q;
	start->prev = NULL;
	end->prev = q;
	end->next = NULL;
	q->next = end;
	q->prev = start;
	q->data = 0;
	mass[0][n] = 1;

	rec(mass,n,&start,&end);

	for (size_t i = 0; i < n; i++)
	{
		free(mass[i]);
	}
	free(mass);
	free(start);
	free(end);
	return 0;
}