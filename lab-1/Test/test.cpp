#include "pch.h"
#include "../Alg1/Header.h"



queue* getEmpty() {
	queue* q = (queue*)malloc(sizeof(queue)); 
	q->first = NULL;
	q->last = NULL;
	return q;
}

queueM* getEmptyM() {
	queueM* q = (queueM*)malloc(sizeof(queueM));
	q->first = 0;
	q->last = 0;
	q->qm = NULL;
	return q;
}

queueM* getOneItemM() {
	queueM* q = (queueM*)malloc(sizeof(queueM));
	q->qm = (int*)malloc(sizeof(int));
	q->first = 0;
	q->last = 1;
	q->qm[0] = 1;
	return q;
}


queueM* getFullQueueM() {
	queueM* q = (queueM*)malloc(sizeof(queueM));
	q->qm = (int*)malloc(sizeof(int)*3);
	q->first = 0;
	q->last = 3;
	q->qm[0] = 1;
	q->qm[1] = 2;
	q->qm[2] = 3;
	return q;
}

queue* getFullQueue () {
	queue* q = (queue*)malloc(sizeof(queue));
	list* l1 = (struct list*)malloc(sizeof(struct list));
	list* l2 = (struct list*)malloc(sizeof(struct list));
	list* l3 = (struct list*)malloc(sizeof(struct list));

	l1->a = 1;
	l1->next = l2;
	l2->a = 2;
	l2->next = l3;
	l3->a = 3;
	l3->next = NULL;
	q->first = l1;
	q->last = l3;
	return q;
}

TEST(Queue_With_List, isempty_EmptyQueue_return1) {

	queue* q;
	q = getEmpty();
	EXPECT_TRUE(isempty(q) == 1);

}

TEST(Queue_With_List, isempty_NotEmptyQueue_return0) {

	queue* q;
	q = getFullQueue();
	EXPECT_TRUE(isempty(q) == 0);

}

TEST(Queue_With_List, add_addingInEmptyQueue_return1) {

	queue* q;
	list* l;
	q = getEmpty();
	EXPECT_TRUE(add(q, 1)==1); //проверка условия
	l = q->last;
	EXPECT_TRUE(l->a == 1); //проверка добавления

}

TEST(Queue_With_List, add_addingItemToQueue_return0) {
	int i;
	queue* q;
	list* l;
	q = getFullQueue();
	EXPECT_TRUE(add(q, 4) == 0);
	l = q->first;
	for (i = 1; i < 5; i++) {
		EXPECT_TRUE(l->a == i);
		l = l->next;
	}
	


}

TEST(Queue_With_List, get_getingItemFromQueue_return0) {
	int i,c;
	queue* q;
	list* l;
	q = getFullQueue();
	EXPECT_TRUE(get(q, &c) == 0);
	EXPECT_TRUE(c == 1);


}

TEST(Queue_With_List, get_EmptyQueue_return1) {
	int i, c;
	queue* q;
	list* l;
	q = getEmpty();
	EXPECT_TRUE(get(q, &c) == 1);


}


TEST(Queue_With_Array, isemptyM_EmptyQueue_return1) {

	queueM* q;
	q = getEmptyM();
	EXPECT_TRUE(isemptyM(q) == 1);

}

TEST(Queue_With_Array, isemptyM_NotEmptyQueue_return0) {

	queueM* q;
	q = getFullQueueM();
	EXPECT_TRUE(isemptyM(q) == 0);

}

TEST(Queue_With_Array, addM_addingInEmptyQueue_return1) {

	queueM* q;
	q = getEmptyM();
	EXPECT_TRUE(addM(q, 1)==1);
	EXPECT_TRUE(q->qm[0] == 1);

}

TEST(Queue_With_Array, addM_addingInQueue_return0) {

	queueM* q;
	int i;
	q = getFullQueueM();
	EXPECT_TRUE(addM(q, 4) == 0);

	for (i=0; i<4; i++)
	   EXPECT_TRUE(q->qm[i] == i+1);

}

TEST(Queue_With_Array, getM_getingItemFromQueue_return0) {

	queueM* q;
	int c;
	q = getFullQueueM();
	EXPECT_TRUE(getM(q, &c) == 0);
	EXPECT_TRUE(c == 1);

}

TEST(Queue_With_Array, getM_EmptyQueue_return1) {

	queueM* q;
	int c;
	q = getEmptyM();
	EXPECT_TRUE(getM(q, &c) == 1);
	

}

TEST(Queue_With_Array, getM_QueueWithOneElement_return2) {

	queueM* q;
	int c;
	q = getOneItemM();
	EXPECT_TRUE(getM(q, &c) == 2);


}