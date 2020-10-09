#include <stdio.h>
#include <stdlib.h>


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

void init(struct queue* q) {  // создание корня

	list* lst = (struct list*)malloc(sizeof(struct list));
	q->first = lst;
	q->last = lst;
}

int isempty(struct queue* q) { //проверка на пустую очередь 
							   // 1 если пустая, 0 если есть элементы
	if (q->first == NULL)
		return 1;
	else
		return 0;
}

int add(struct queue* q, int c) { // добавление в конец очереди
								  // 1 если пустая, 0 если уже есть элементы

	if (isempty(q)) {
		init(q);
		q->last->a = c;
		q->last->next = NULL;
		return 1;
	}

	struct list* lst;
	lst = (struct list*)malloc(sizeof(struct list));
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
		return 1;
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

void initM(struct queueM* q) {
	q->first = 0;
	q->last = 1;
	q->qm = (int*)malloc(sizeof(int));
	return;
}

void emptyM(queueM* q) {
	q->first = 0;
	q->last = 0;
	q->qm = NULL;
}

int isemptyM(queueM* q) {
	if (q->last == 0) return 1;
	else return 0;
}

int addM(struct queueM* q, int x) {

	if (isemptyM(q)) {
		initM(q);
		q->qm[0] = x;
		return 1;
	}
	q->last++;
	q->qm = (int*)realloc(q->qm, sizeof(int) * q->last);
	q->qm[q->last - 1] = x;
	return 0;
}

int getM(queueM* q, int* x) {
	int i;

	if (isemptyM(q)) {
		x = NULL;
		return 1;
	}

	*x = q->qm[0];

	q->last--;

	if (isemptyM(q)) {
		free(q->qm);
		emptyM(q);
		return 2;
	}

	for (i = 0; i < q->last; i++) {
		q->qm[i] = q->qm[i + 1];
	}

	q->qm = (int*)realloc(q->qm, sizeof(int) * q->last);
	return 0;
}


