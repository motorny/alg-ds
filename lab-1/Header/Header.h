#include <stdio.h>
#include <stdlib.h>

#define arLen 1000
#define MALLOC_ERROR 11
#define EMPTY_LIST 1
#define EMPTY_ARRAY 1
#define ONE_ITEM_LEFT 2

//////////////////// Реализация через линейный список////////////////////////////

typedef struct list { //структура списка
	int a; //поле с данными
	struct list* next;
}list;

typedef struct queue {
	struct list* first, * last;
} queue;


void empty(struct queue* q) { //инициализация

	q->first = NULL;
	q->last = NULL;
}

int init(struct queue* q) {  // создание корня

	list* lst = (struct list*)malloc(sizeof(struct list));
	if (lst == NULL) return MALLOC_ERROR;
	q->first = lst;
	q->last = lst;
	return 0;
}

int isempty(struct queue* q) { //проверка на пустую очередь 
							   // 1 если пустая, 0 если есть элементы
	if (q->first == NULL)
		return EMPTY_LIST;
	else
		return 0;
}

int add(struct queue* q, int c) { // добавление в конец очереди
								  // 1 если пустая, 0 если уже есть элементы

	if (isempty(q)) {
		init(q);
		q->last->a = c;
		q->last->next = NULL;
		return  EMPTY_LIST;
	}

	struct list* lst;
	lst = (struct list*)malloc(sizeof(struct list));
	if (lst == NULL) return MALLOC_ERROR;

	lst->a = c;
	lst->next = NULL;
	q->last->next = lst;
	q->last = lst;
	return 0;

}

int get(queue* q, int* c) { // извлечение элемента
				            // 1 если пустая, 0 если есть элементы

	if (isempty(q)) {
		c = NULL;
		return  EMPTY_LIST;
	}

	list* lst = q->first;
	*c = lst->a;
	q->first = lst->next;
	free(lst);

	return 0;

}

/////////////////////////////Реализация через массив///////////////////////////////////////////

typedef struct queueM {
	int* qm;
	int first, last;
}queueM;

int initM(struct queueM* q) {
	q->first = 0;
	q->last = 1;
	q->qm = (int*)malloc(sizeof(int)*arLen);
	if (q->qm == NULL) return MALLOC_ERROR;
	return 0;
}

void emptyM(queueM* q) {
	q->first = 0;
	q->last = 0;
	q->qm = NULL;
}

int isemptyM(queueM* q) {
	if (q->last == 0)
		return EMPTY_ARRAY;
	else return 0;
}

int addM(struct queueM* q, int x) {
	int* save;

	if (isemptyM(q)) {
		initM(q);
		q->qm[0] = x;
		return EMPTY_ARRAY;
	}
	q->last++;

	if (q->last % arLen == 0) {
		save = (int*)realloc(q->qm, sizeof(int) * (q->last + arLen));
		if (save == NULL) return MALLOC_ERROR;
		q->qm = save;
	}

	q->qm[q->last - 1] = x;

	return 0;
}

int getM(queueM* q, int* x) {
	int i;
	int* save;

	if (isemptyM(q)) {
		x = NULL;
		return EMPTY_ARRAY;
	}

	*x = q->qm[0];

	q->last--;

	if (isemptyM(q)) {
		free(q->qm);
		emptyM(q);
		return ONE_ITEM_LEFT;
	}

	for (i = 0; i < q->last; i++) {
		q->qm[i] = q->qm[i + 1];
	}


	if (q->last % arLen == 0) {
		save = (int*)realloc(q->qm, sizeof(int) * (q->last));
		if (save == NULL) return MALLOC_ERROR;
		q->qm = save;
	}
	return 0;
}


