    #include<stdio.h>
#include"list.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#pragma warning(disable:4996)


void ListDestroy(list_t* list) {
	list_t* tmp = list;

	while (tmp->next != NULL) {
		list = tmp->next;
		free(tmp);
		tmp = list;
	}
	free(list);
}

int Length(char s[][maxLength], int n) {
	int len = 0;
	int i = 0;
	for (; i < n; i++) {
		len += (int)strlen(s[i]);
	}
	return len;
}

char* Merge(list_t* list, int len) {
	int lenStr = 0, count = 0;
	if (!list)
		return NULL;
	char* str = malloc((len + 1) * sizeof(char));
	if (!str)
		return NULL;
	while (list) {
		lenStr = (int)strlen(list->str);
		memcpy(str + count, list->str, lenStr);
		list = list->next;
		count += lenStr;
	}
	str[count] = '\0';
	return str;
}

list_t* InsertStrToList(char word[]) {

	list_t* elem = (list_t*)malloc(sizeof(list_t));
	if (!elem)
		return NULL;

	elem->str = word;
	elem->next = NULL;
	return elem;
}

list_t* InsertTextToList(char s[][maxLength], int n) {
	int i = 0;
	list_t* list = NULL;
	if (n < 1)
		return NULL;
	list = InsertStrToList(s[i]);
	if (!list)
		return NULL;
	i++;
	list_t* e = list;
	while (i < n) {
		list->next = InsertStrToList(s[i]);
		list = list->next;
		i++;
	}

	return e;
}




    
