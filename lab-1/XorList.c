#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define TRUE 1
#define FALSE 0

// Элемент списка
struct Elem {
	char* data; // где лежит строка в памяти
	struct Elem* xor_addr;	// xor адрес (адрес пред xor адрес след)
};

typedef struct Elem Elem;

// Список целиком
struct List {
	Elem* first;
	Elem* last;
};

typedef struct List List;

// функция вычиляет XOR для двух элементов
Elem* XOR(Elem* a, Elem* b) {
	return (Elem*)((unsigned long long)a ^ (unsigned long long)b);
}


void init(List* list) {
	list->first = NULL;
	list->last = NULL;
}

// добавление элемента
// list - указатель на список в который добавляем строку
// str - указатель на добавляемую строку
int addElem(List* list, char* str) {

	if (list == NULL || str == NULL)
		return FALSE;

	// Сохраняем строку в ОП
	int len = strlen(str);  // определяем длину строки
	char* p = (char*)malloc(len + 1); // выделяем память под строку
	// Создаем элемент списка
	Elem* new_elem = (Elem*)malloc(sizeof(Elem));

	if (p == NULL || new_elem == NULL) {
		free(p);
		free(new_elem);
		return FALSE;
	}

	strcpy(p, str); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль

	new_elem->data = p; // значение элемента (адрес строки)

	// Встраиваем элемент в конец списка
	if (list->first == NULL) {// если список пуст 
		new_elem->xor_addr = XOR(0, 0);
		list->first = new_elem;
	}
	else {// уже есть больше одного элемента

		new_elem->xor_addr = XOR(list->last, 0);
		Elem* prev = XOR(list->last->xor_addr, 0); // адрес предпоследнего элемента

		// обновление xor-адреса последнего элемента списка
		list->last->xor_addr = XOR(prev, new_elem);
	}
	list->last = new_elem;

	return TRUE;
}

//нахождение элемента по ключу
Elem* FindElemByKey(List* list, char* key) {
	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	Elem* p1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {

		if (strcmp(p1->data, key) == 0) {
			//printf("%p\n%s\n", p1->xor_addr, p1->data);
			return p1;
		}
		else {
			printf("Don't have\n");//нет такого элемента
			return NULL;
		}
	}

	//если в списке более одного эемента
	if (list->first != list->last) {

		Elem* p2 = XOR(p1->xor_addr, 0); //указатель на второй элемент

		if (strcmp(p1->data, key) == 0) {

			return p1;
		}

			while (strcmp(p2->data, key) != 0) {
				
				// след = адрес_пред ^ xor_текущего
				Elem* next = XOR(p1, p2->xor_addr);
				

				//если список не содержит элемента
				if ((p2 == list->last) && (strcmp(p2->data, key) != 0)) {
					printf("Don't have1\n");
					return NULL;
				}

				p1 = p2;
				p2 = next;
			}

			//printf("%p\n%s\n", p2->xor_addr, p2->data);
			return p2;
	}
}

//удаление элемента по ключу
int DeleteElemByKey(List* list, char* key) {

	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	Elem* p1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {

		if (strcmp(p1->data, key) == 0) {

			//printf("Element removed\n");
			list->first = NULL;
			list->last = NULL;
			free(p1);
			return TRUE;
		}
		else
		{
			//нет такого элемента
			printf("There isn't such element in list\n");
			return NULL;
		}
	}

	//если в списке более одного эемента
	if (list->first != list->last) {
		//указатель на второй элемент
		Elem* p2 = XOR(p1->xor_addr, 0);

		//если нужно удалить первый элемент списка
		if (strcmp(p1->data, key) == 0) {
			//printf("Removed first element\n");
			free(p1);

			Elem* p3 = XOR(p1, p2->xor_addr);
			p2->xor_addr = XOR(0, p3);
			list->first = p2;
			return TRUE;
		}

		while (strcmp(p2->data, key) != 0) {
			// след = адрес_пред ^ xor_текущего
			Elem* next = XOR(p1, p2->xor_addr);
			p1 = p2;
			p2 = next;

			//если список не содержит элемента
			if (p2 == NULL) {
				printf("No such element\n");
				return NULL;
			}
		}

		if (p2 == list->last) {
			p1->xor_addr = XOR(XOR(p1->xor_addr, p2), 0);
			list->last = p1;
		}
		else {
			// адрес следующего (3-его) элемента в ОП
			Elem* p3 = XOR(p1, p2->xor_addr);
			p1->xor_addr = XOR(XOR(p1->xor_addr, p2), p3);

			if (p3 != NULL) {
				p3->xor_addr = XOR(p1, XOR(p2, p3->xor_addr));
			}

		}

		// удаление элемента p2
		printf("Removed element\n");
		free(p2);
		return TRUE;
	}
}


//удаление элемента по ключу
int DeleteElemByAddress(List* list, Elem* p) {

	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	Elem* p1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {
		
		if (p1 == p) {
			printf("Element removed\n");
			list->first = NULL;
			list->last = NULL;
			free(p1);
			return TRUE;
		}
		else {
			//нет такого элемента
			printf("There isn't such element in list\n");
			return NULL;
		}
	}

	//если в списке более одного эемента
	if (list->first != list->last) {
		//указатель на второй элемент
		Elem* p2 = XOR(p1->xor_addr, 0);

		//если нужно удалить первый элемент списка
		if (p1 == p) {
			printf("Removed first element\n");
			free(p1);

			Elem* p3 = XOR(p1, p2->xor_addr);
			p2->xor_addr = XOR(0, p3);
			list->first = p2;
			return TRUE;
		}

		while (p2 != p) {
			// след = адрес_пред ^ xor_текущего
			Elem* next = XOR(p1, p2->xor_addr);
			p1 = p2;
			p2 = next;

			//если список не содержит элемента
			if (p2 == NULL) {
				printf("No such element\n");
				return NULL;
			}
		}

		if (p2 == list->last) {
			p1->xor_addr = XOR(XOR(p1->xor_addr, p2), 0);
			list->last = p1;
		}
		else {
			// адрес следующего (3-его) элемента в ОП
			Elem* p3 = XOR(p1, p2->xor_addr);
			p1->xor_addr = XOR(XOR(p1->xor_addr, p2), p3);

			if (p3 != NULL) {
				p3->xor_addr = XOR(p1, XOR(p2, p3->xor_addr));
			}

		}

		// удаление элемента p2
		printf("Removed element\n");
		free(p2);
		return TRUE;
	}
}

//функция возвращяет адрес первого элемента
Elem* First(List* list) {
	return list->first;
}

//функция возвращяет адрес последнего элемента
Elem* Last(List* list) {
	return list->last;
}

//переход к следующему элементу
Elem* Next(List* list, Elem* a) {

	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	Elem* p1 = list->first;
	//в списке находиться один элемент
	if (list->first == list->last) {
		printf("It is last and first element\n");
		return NULL;
	}

	Elem* p2 = XOR(p1->xor_addr, 0);

	if (p1 == a)
		return p2;

	if (a == list->last) {
		printf("It is last element\n");
		return NULL;
	}

	if ((list->first != list->last) && (p1 != a)) {

		while (p1 != a) {
			// след = адрес_пред ^ xor_текущего
			Elem* next = XOR(p1, p2->xor_addr);
			p1 = p2;
			p2 = next;
		}
		return p2;
	}

	return NULL;
}

void clearList(List* list) {

	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return;
	}

	Elem* p1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {
		
		//printf("Element removed\n");
		list->first = NULL;
		list->last = NULL;
		free(p1);
		return;
	}

	//если в списке более одного элемента
	if (list->first != list->last) {

		Elem* p2 = XOR(p1->xor_addr, 0);

		if (p2 == list->last) {

		}free(p1);
		free(p2);
		list->first = NULL;
		list->last = NULL;
		return;

		Elem* next = XOR(p1, p2->xor_addr);

		if (next == list->last) {
			free(p1);
			free(p2);
			free(next);
			list->first = NULL;
			list->last = NULL;
			return;
		}
		
		
		while (next != list->last) {

			next = XOR(p1, p2->xor_addr);
			free(p1);
			p1 = p2;
			p2 = next;
		}
		
		free(p1);
		free(p2);
		free(next);
		list->first = NULL;
		list->last = NULL;
		return;
	}

}

// печать списка
void print(List* list) {

	if (list->first == NULL) {
		printf("Empty list\n");
		return;
	}

	Elem* p1 = list->first;
	//printf("%s ", p1->data);
	printf("%s (%p, XOR_ADDR=%p)\n", p1->data, p1, p1->xor_addr);


	if (list->first != list->last) {
		Elem* p2 = XOR(p1->xor_addr, 0); // указатель на 2-ой элемент
//		printf("%s ", p2->data);
		printf("%s (%p, XOR_ADDR=%p)\n", p2->data, p2, p2->xor_addr);

		while (p2 != list->last) {

			// след = адрес_пред ^ xor_текущего
			Elem* next = XOR(p1, p2->xor_addr);
			p1 = p2;
			p2 = next;
			printf("%s (%p, XOR_ADDR=%p)\n", p2->data, p2, p2->xor_addr);
		}
	}

	printf("\n");
}

