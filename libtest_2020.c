#include "C:\Users\Lenovo\source\repos\lib_2020\lid_2020.h"
#include "C:\Users\Lenovo\source\repos\lib_2020\lib_2020.c"
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#define SRTLEN 30
#define LISTLEN 10000


int isSortedDesc(LIST_T *head)
{
	if (head == NULL)
		return 0;
	for (LIST_T *t = head; t->next != NULL; t = t->next)
		if ((strcmp(t->str, t->next->str)>0))
			return 1;
	return 0;
}
void print(LIST_T *head) {
	int i = 1;
	LIST_T *current_node = head;
	while (current_node != NULL) {
		printf("%i. %s\n", i,current_node->str);
		current_node = current_node->next;
		i++;
	}
}
void push(LIST_T * head, char* val) {
	LIST_T * current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = (LIST_T *)malloc(sizeof(LIST_T));
	current->next->str = val;
	current->next->next = NULL;
}
static char *rand_string(char *str, size_t size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (size) {
		--size;
		for (size_t n = 0; n < size; n++) {
			int key = rand() % (int)(sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}
int main() 
{
	LIST_T *t, *tmp;
	char *str,*str1;
	int i=0;
	str1 = (char*)malloc(SRTLEN * sizeof(char));
	t = (LIST_T*)malloc(sizeof(LIST_T));
	t->str = rand_string(str1, SRTLEN);
	t->next = NULL;
	t->prev = NULL;
	for (i = 0; i < LISTLEN-1; i++)
	{
		str= (char*)malloc(SRTLEN * sizeof(char));
		push(t, rand_string(str, SRTLEN));
	}
	print(t);
	Sort(&t);
	print(t);
	printf("%i",isSortedDesc(t));
	return 0;
}