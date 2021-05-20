#include <string.h>
#include <stdio.h>
//#include "vld.h"
#pragma warning (disable:4996)
#define P 31
#define SIZE 100000
#define TRUE 1
#define FALSE 0
#define MEM_ERR -1;
typedef struct hashTableElement {
	char* data;
	struct hashTableElement* next;
	struct hashTableElement* prev;


}hashE_t;
unsigned multipl(char c, unsigned n) {
	unsigned rez = 1;
	for (size_t i = 0; i !=n; ++i)
	{
		rez *= P;
	}
	return rez;
}
unsigned hashFunk(char* s,unsigned n) {
	unsigned sum = 0;
	for (size_t i = 0; i != n; ++i)
		sum += s[i];// multipl(s[i], i);
	return sum;
}
hashE_t** add(hashE_t** oldMass,char* s) {
	unsigned n = strlen(s);
	if (!oldMass) {
		oldMass= (hashE_t**)malloc(sizeof(hashE_t*) * SIZE);
		for (size_t i = 0; i != SIZE; ++i)
			oldMass[i] = NULL;
	}

	unsigned hash = hashFunk(s,n)%SIZE;
	hashE_t* tmp;// = oldMass[hash];
	
		tmp = (hashE_t*)malloc(sizeof(hashE_t));
		tmp->data = NULL;
		 
	
	hashE_t* prev = oldMass[hash],*t=NULL;
	while (prev)
	{
		t = prev;
		prev = prev->next;
	}
	tmp->next = NULL;
	tmp->prev = t;
	if(t)
	t->next = tmp;
	tmp->data= (char*)malloc(n + 1);
	for (int i = 0; i != n; ++i)
		tmp->data[i] = s[i];
	tmp->data[n] = 0;

	if (!oldMass[hash])
		oldMass[hash] = tmp; 
	
	return oldMass;
}
int find(hashE_t** oldMass, char* s) {
	if (!oldMass)
		return FALSE;
	unsigned hash = hashFunk(s, strlen(s)) % SIZE;
	hashE_t* tmp = oldMass[hash];
	if (!tmp)
		return FALSE;
	else
		while (tmp)
		{
			if (!strcmp(s, tmp->data))
				return TRUE;
			tmp=tmp->next;
		}
	return FALSE;
 }
hashE_t** delete(hashE_t** oldMass, char* s) {
	if (!oldMass)
		return NULL;
	unsigned hash = hashFunk(s, strlen(s)) % SIZE;
	hashE_t* tmp = oldMass[hash];
	if (!tmp)
		return oldMass;
	else
		while (tmp)
		{
			if (!strcmp(s, tmp->data)) {
				free(tmp->data);
				if (tmp->next && tmp->prev)
				{
					tmp->next->prev = tmp->prev;
					tmp->prev->next = tmp->next;
				}
				else if (tmp->next) {
					oldMass[hash] = tmp->next;
					tmp->next->prev = NULL;
				}
				else if (tmp->prev) {
					tmp->prev->next = NULL;
				}
				else {
					oldMass[hash] =NULL;

				}
				free(tmp);
				tmp = NULL;
				return oldMass;
			}
			
			tmp = tmp->next;
		}
	return oldMass;
}
void clear(hashE_t** mass) {
	hashE_t* tmp,*del;
	if (mass) {
		for (size_t i = 0; i != SIZE; ++i)
		{
			tmp = mass[i];
			while (tmp)
			{
				free(tmp->data);
				del = tmp;
				tmp = tmp->next;
				free(del);
			}
		}
		free(mass);
	}
}
int main() {
	hashE_t** mass = NULL;
	char elem[100];
	char symbol, command;
	int number;
	while (TRUE) {
		command = getchar();
		if (command != EOF) {
			while (command == '\0' || command == '\n' || isspace(command) != 0)
				symbol = getchar();
			scanf("%s", &elem);
			switch (command) {
			case('a'):
				mass = add(mass, elem);
				
				break;
			case('r'):
				mass = delete(mass, elem);
				break;
			case('f'):
				if (find(mass,elem))
					printf("yes\n");
				else
					printf("no\n");
				break;
			default:
				break;
			}
			symbol = getchar();
		}
		else
			break;
	}
	clear(mass);
	


	return 0;
}
