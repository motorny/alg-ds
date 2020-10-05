#include "Header.h"

void Read_in_list(list** head, FILE* f) {
	char buf[100];
	int num;
	char* word = NULL;
	buf[99] = '\0';
	if (fscanf(f, "%s", buf) != 0) {

		while (!feof(f)) {

			word = (char*)malloc(strlen(buf) + 1);
			if (word == NULL) {
				error_my = NOT_ENOUGH_MEMORY;
				Clear_list(head);
				return;
			}

			strcpy(word, buf);
			
			if (fscanf(f, "%i", &num) != 0) {
				Add_in_list(head, word, num);
			}
			else {
				error_my = ERROR_READ;
			}
			free(word);

			if (error_my) {
				Clear_list(head);
				return;
			}

			if (fscanf(f, "%s", buf) == 0)
			{
				error_my = ERROR_READ;
				Clear_list(head);
				return;
			}

		}

	}

	return;
}


void Add_in_list(list** List, char* word, int number) {
	list* block = NULL;
	list* a = NULL;

	if ((*List) == NULL) {
		Create_list(List, word, number);
		return;
	}

	if((*List)->next!=NULL && ((*List)->number<number)){
		a = get_Nth_list(*List, number);

		if (error_my)
			return;

		Create_list(&block, word, number);
		if (error_my)
			return;

		block->next = a->next;
		a->next = block;
	}
	else {																	//в случае с одним элементом список не промотаешь
		if ((*List)->number <= number) {										//или если этот элемент уже меньше твоего

			if ((*List)->number == number) {
				Error_repeat_number();
				error_my = REPEAT_NUMBER;
				return;
			}
				

			Create_list(&block, word, number);
			if (error_my)
				return;

			block->next = (*List)->next;
			(*List)->next = block;


		}
		else {													
			Create_list(&block, word, number);
			if (error_my)
				return;

			block->next = *List;
			*List = block;
		}
	}
	
	
	return;
}

void Create_list(list** List1, char* word, int number) {
	*List1 = (list*)malloc(sizeof(list));

	if (*List1 == NULL) {
		error_my = NOT_ENOUGH_MEMORY;
		return;
	}

	(*List1)->number = number;
	(*List1)->word = (char*)malloc(strlen(word)+1);

	if ((*List1)->word == NULL) {
		error_my = NOT_ENOUGH_MEMORY;
		free(*List1);
		return;
	}

	strcpy((*List1)->word, word);
	(*List1)->next = NULL;
	return;
}

list* get_Nth_list(list* List, int n) {

	while (List->next != NULL) {
		if (List->next->number < n)
			List = List->next;
		else
			break;
	}
	
	
	if (List->next != NULL) {
		if (List->next->number == n) {
			Error_repeat_number();
			error_my = REPEAT_NUMBER;
		}
	}
		
	return List;
}








/*void Add_in_list(list** List, char* word, int number) {
	list* block = NULL;
	list* tmp = NULL;
	list* a = NULL;
	//Если список пуст, то просто добавляем элемент
	if (*List == NULL) {

		*List = (list*)malloc(sizeof(list));
		if (*List == NULL) {
			error_memory = NOT_ENOUGH_MEMORY;
			return;
		}

		(*List)->word = (char*)malloc(strlen(word) + 1);
		if ((*List)->word == NULL) {
			error_memory = NOT_ENOUGH_MEMORY;
			free(*List);
			return;
		}
		else {
			strcpy((*List)->word, word);
			(*List)->number = number;
			(*List)->next = NULL;
			return;
		}

	}

	//Находим нужный элемент. Если вышли за пределы списка, то выходим из цикла,
	a = get_Nth_list(*List, number);
	block = (list*)malloc(sizeof(list));
	if (block == NULL) {
		error_memory = NOT_ENOUGH_MEMORY;
		return;
	}

	block->word = (char*)malloc(strlen(word) + 1);
	if (block->word == NULL) {
		error_memory = NOT_ENOUGH_MEMORY;
		free(block);
		return;
	}
	else {
		strcpy(block->word, word);
		block->number = number;


		if (a->number > number) {
			block->next = a;
			a = block;
			return;
		}
		else {
			block->next = a->next;
			a->next = block;
		}

	}
}


	//Create_list(list * *List1, char* word, int number);
list* get_Nth_list(list* List, int n) {
	while (List->number <= n && List->next) {
		List = List->next;
	}
	return List;
}
*/