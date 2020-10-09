#pragma once 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define problem -1
#define word_length 21
typedef struct LIST
{
	char data[100];
	struct LIST* next;
}LIST;
int write(FILE* fp, LIST* List);
int merger(LIST* List1, LIST* List2);
int free_list(LIST* List);