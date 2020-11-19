#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0
#define BLOCK_USED -1
#define MAGICKEY 3131

typedef enum {
	NO_FIT,
	FIRST_FIT,
	NEXT_FIT,
}FIT;

typedef struct descriptor_t {
	int size;
	int key;
	struct descriptor_t* next;
} DESCR;

typedef struct end_descr_t {
	int size;
} END_DESCR;

struct {
	DESCR* list;
	char* start;
	int total_size;
} memory_system = { (DESCR*)NULL, 0, NULL };

int meminit(void* pMemory, int size) {
	int min = memgetminimumsize();
	if (!pMemory || size < min)
		return FAIL;
	else {
		memory_system.total_size = size;
		memory_system.start = (char*)pMemory;
		memory_system.list = (DESCR*)pMemory;
		memory_system.list->key = MAGICKEY;
		memory_system.list->size = size - min;
		memory_system.list->next = NULL;
		((END_DESCR*)(memory_system.start + sizeof(DESCR) + memory_system.list->size))->size = memory_system.list->size;
		return SUCCESS;
	}
}

void* memalloc(int size) {
	if (!memory_system.list || size <= 0 || size + memgetminimumsize() > memory_system.total_size)
		return NULL;

	DESCR** temp = &memory_system.list;
	DESCR** current = NULL;
	DESCR** first_fit = NULL;
	DESCR* new_descr = NULL;
	FIT fit = NO_FIT;

	while (*temp != NULL) {
		if ((*temp)->size >= size) {
			if (fit == NO_FIT) {
				fit = FIRST_FIT;
				first_fit = temp;
			}
			if (fit == FIRST_FIT) {
				fit = NEXT_FIT;
				break;
			}
		}
		current = temp;
		temp = &(*temp)->next;
	}
	
	if (fit == NO_FIT)
		return NULL;
	else {
		if (fit == FIRST_FIT) 
			current = first_fit;
		if (fit == NEXT_FIT)
			current = temp;

		new_descr = (*current);
		new_descr->key = MAGICKEY;

		int prev_size = (*current)->size;

		if (prev_size <= size + memgetblocksize()) {
			(*current) = (*current)->next;
			((END_DESCR*)((char*)new_descr + sizeof(DESCR) + new_descr->size))->size = BLOCK_USED;
			new_descr->next = NULL;
			return (void*)((char*)new_descr + sizeof(DESCR));
		}
		else {
			(*current) = (DESCR*)((char*)new_descr + memgetblocksize() + size);
			(*current)->size = new_descr->size - memgetblocksize() - size;
			(*current)->key = MAGICKEY;
			(*current)->next = new_descr->next;
			((END_DESCR*)((char*)new_descr + sizeof(DESCR) + new_descr->size))->size = (*current)->size;

			new_descr->size = size;
			new_descr->next = NULL;
			((END_DESCR*)((char*)new_descr + sizeof(DESCR) + new_descr->size))->size = BLOCK_USED;

			return (void*)((char*)new_descr + sizeof(DESCR));
		}
	}
}

void memfree(void* p) {
	if ((char*)p < (char*)memory_system.start || (char*)p >= (char*)memory_system.start + memory_system.total_size || p == NULL)
		return;
	DESCR* current = (DESCR*)((char*)p - sizeof(DESCR));
	END_DESCR* end_current = (END_DESCR*)((char*)p + current->size);

	if (current->key != MAGICKEY)
		return;

	END_DESCR* end_left = (END_DESCR*)((char*)current - sizeof(END_DESCR));
	DESCR* left_descr = (DESCR*)((char*)end_left - end_left->size - sizeof(DESCR));

	if ((char*)end_left < (char*)memory_system.start || end_left->size == BLOCK_USED) {
		current->next = memory_system.list;
		end_current->size = current->size;
		memory_system.list = current;
	}
	else {
		left_descr->size += current->size + memgetblocksize();
		end_current->size = left_descr->size;
		current = left_descr;
	}

	DESCR* right_descr = (DESCR*)((char*)end_current + sizeof(END_DESCR));
	END_DESCR* end_right = (END_DESCR*)((char*)right_descr + right_descr->size + sizeof(DESCR));

	if ((char*)right_descr >= (char*)memory_system.start + memory_system.total_size || right_descr->key != MAGICKEY)
		return;
	if (end_right->size != BLOCK_USED) {
		current->size += right_descr->size + memgetblocksize();
		end_right->size = current->size;
		right_descr->key = 0;
		DESCR* temp = memory_system.list;
		while (temp != right_descr && temp != NULL) {
			temp = temp->next;
		}
		if (temp == right_descr)
			temp = temp->next;
	}
}

void memdone() {
	memory_system.total_size = 0;
	memory_system.start = NULL;
	memory_system.list = NULL;
}

int memgetminimumsize() {
	return (int)(sizeof(DESCR) + sizeof(END_DESCR));
}

int memgetblocksize() {
	return (int)(sizeof(DESCR) + sizeof(END_DESCR));
}
