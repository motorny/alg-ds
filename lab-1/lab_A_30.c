#include "lab_A.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

plenty_t* CreateZeroPlenty(void) {
	plenty_t* A = (plenty_t*)malloc(sizeof(plenty_t));
	A->head = NULL;
	//A->head = malloc(sizeof(node_t));
	//A->head->data = (data_t)INT_MIN;
	//A->head->next = NULL;
	return A;
}
void FillPlenty(plenty_t* A, int size, data_t step) {
	assert(A != 0);
	assert(size > 0);

	node_t* p;
	int i;
	A->head = (node_t*)malloc(sizeof(node_t));
	if (A->head == NULL) {
		return;
	}
	p = A->head;
	for (i = 1; i <= size; i++) {
		p->data = step * i;
		if (i != size) {
			p->next = (node_t*)malloc(sizeof(node_t));
			p = p->next;
		}
	}
	p->next = NULL;
}
void DestroyPlenty(plenty_t* A) {
	assert(A != 0);
	if (A->head == NULL) {
		free(A);
		return;
	}
	node_t* p = A->head, * t = NULL;
	do {
		t = p->next;
		free(p);
		p = t;
	} while (t != NULL);
	free(A);
}

void AddInPlenty(plenty_t* A, data_t item) {
	assert(A != 0);
	node_t *p, *t = (node_t*)malloc(sizeof(node_t)), *h;
	if (t == NULL) {
		return;
	}
	t->next = NULL;

	//if one element
	if (A->head == NULL) {
		A->head = t;
		A->head->data = item;
		return;
	}

	p = A->head;
	while (p->data < item) {
		if (p->next == NULL) {
			t->data = item;
			p->next = t;
			return;
		}
		p = p->next;
	}
	h = p->next;
	t->data = p->data;
	p->data = item;
	p->next = t;
	t->next = h;
}
int DelFromPlenty(plenty_t* A, data_t item, int delType) {
	if (A == NULL || A->head == NULL) {
		return NaN;
	}
	node_t* p = A->head, * t, * first = NULL;

	//if first element
	if (p->data == item) {
		first = p;
		if (p->next != NULL && p->next->data != item) {
				t = first->next;
				free(first);
				A->head = t;
				return TRUE;
		}
		if (p->next == NULL) {
			free(first);
			A->head = NULL;
			return TRUE;
		}
	}
	
	//find element
	while (p->next != NULL && p->next->data != item) {
		p = p->next;
		if (p->next->next == NULL) {
			if (first != NULL)
				goto __first;
			else 
				return FALSE;
		}
	}

	//how to delete?
	if (delType == ALL) {
		do {
			t = p->next->next;
			free(p->next);
			p->next = t;
		} while (p->next != NULL && p->next->data == item);
	}
	if (delType == FIRST) {
		t = p->next->next;
		free(p->next);
		p->next = t;
	}

__first : 
	if (first != NULL) {
		t = first->next;
		free(first);
		A->head = t;
	}
	return TRUE;
}
int IsIncludeInPlenty(plenty_t* A, data_t item) {
	if (A == NULL || A->head == NULL) {
		return NaN;
	}
	node_t* p = A->head;
	do {
		if (p->data == item)
			return TRUE;
		p = p->next;
	} while (p != NULL);
	return FALSE;
}

plenty_t* PlentyMerge(plenty_t* A, plenty_t* B) {
	node_t* h1 = A->head, * h2 = B->head;
	plenty_t* C = CreateZeroPlenty();

	while (h1 != NULL && h2 != NULL) {
		if (h1->data < h2->data) {
			AddInPlenty(C, h1->data);
			h1 = h1->next;
			continue;
		}
		if (h2->data < h1->data) {
			AddInPlenty(C, h2->data);
			h2 = h2->next;
			continue;
		}
		if (h1->data == h2->data) {
			AddInPlenty(C, h1->data);
			h1 = h1->next;
			h2 = h2->next;
			continue;
		}
	}
	while (h1 != NULL) {
		AddInPlenty(C, h1->data);
		h1 = h1->next;
	}
	while (h2 != NULL) {
		AddInPlenty(C, h2->data);
		h2 = h2->next;
	}
	return C;
}
plenty_t* PlentyUnion(plenty_t* A, plenty_t* B) {
	node_t* h1 = A->head, * h2 = B->head;
	plenty_t* C = CreateZeroPlenty();

	while (h1 != NULL && h2 != NULL) {
		if (h1->data < h2->data) {
			h1 = h1->next;
			continue;
		}
		if (h2->data < h1->data) {
			h2 = h2->next;
			continue;
		}
		if (h1->data == h2->data) {
			AddInPlenty(C, h1->data);
			h1 = h1->next;
			h2 = h2->next;
			continue;
		}
	}
	return C;
}

void PrintPlenty(plenty_t* A) {
	if (A->head == NULL) {
		printf("{ - }");
		return;
	}
	node_t* p = A->head;
	printf("{ ");
	while(p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("}\n");
}

