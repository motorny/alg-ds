
#include "pch.h"
#include "memallocator.h"
#include <stdio.h>

#define ERROR -1
#define DONE 1
#define INT_MAX 2147483647

	typedef struct blockmem_t {
		int size;
		struct blockmem_t* next;
		struct blockmem_t* prev;
		int is_available;
	}blockmem_t;


	
	blockmem_t* memlist = NULL;// list of free blocks
	int allsize = 0;


	int memgetminimumsize() {
		return sizeof(blockmem_t) + sizeof(int);
	}

	int memgetblocksize() {
		return sizeof(blockmem_t);
	}

	int meminit(void* pMem, int size) {
		if (pMem == NULL || size < memgetminimumsize() || size <= 0)
			return ERROR;
		allsize = size;
		memlist = (blockmem_t*)pMem;
		memlist->size = size - memgetblocksize();
		memlist->next = NULL;
		memlist->prev = NULL;
		memlist->is_available = 1;//a list of initialized
		return DONE;
	}

	void* memalloc(int size) {
		if (size <= 0 || memlist == NULL) // no free memory or memory didn't initializate
			return NULL;
		int bestfitsize = INT_MAX;
		void* p = NULL;
		blockmem_t* blockmem = memlist;
		blockmem_t* newblockmem = NULL;
		blockmem_t* bestfitmem = NULL;
		while (blockmem != NULL) {
			if (blockmem->size >= size + memgetblocksize() && blockmem->size < bestfitsize) {
				bestfitsize = blockmem->size;
				bestfitmem = blockmem;
			}
			blockmem = blockmem->next;
		}
		if (bestfitmem == NULL || bestfitsize == INT_MAX)
			return NULL;

		// change list of free memory;
		if (bestfitsize < size + memgetblocksize()) {
			bestfitmem->is_available = 0;
			if (bestfitmem->prev != NULL)
				bestfitmem->prev->next = bestfitmem->next;
			else
				memlist = bestfitmem->next;
			if (bestfitmem->next != NULL)
				bestfitmem->next->prev = bestfitmem->prev;
			newblockmem->next = bestfitmem->next;

			if (bestfitmem->next == NULL && bestfitmem->prev == NULL)
				memlist = NULL;
		}
		else {
			bestfitmem->size = size + memgetblocksize();
			newblockmem = (blockmem_t*)((char*)bestfitmem + size + memgetblocksize());
			newblockmem->size = bestfitsize - size - memgetblocksize();
			newblockmem->next = bestfitmem->next;
			newblockmem->prev = bestfitmem->prev;
			if (newblockmem->prev != NULL)
				newblockmem->prev->next = newblockmem;
			else memlist = newblockmem;
			if (newblockmem->next != NULL)
				newblockmem->next->prev = newblockmem;
			newblockmem->is_available = 1;
		}
		p = (void*)((char*)bestfitmem + sizeof(blockmem_t));
		return p;
	}

	void memfree(void* p) {
		blockmem_t* freemem = NULL;
		blockmem_t* newfreemem = NULL;
		int freesize = memgetblocksize();
		if (p == NULL)
			return;
		if (p && memlist) {
			newfreemem = (blockmem_t*)((char*)p - freesize);
			if (newfreemem >= memlist && newfreemem <= memlist + allsize && newfreemem->is_available == 0) {
				newfreemem->is_available = 1;
				if (newfreemem->next) {
					if (newfreemem->next->is_available) {
						freemem = newfreemem;
						freemem->size += freemem->next->size + freesize;
						if (freemem->next->next) {
							freemem->next->next->prev = freemem;
							freemem->next = freemem->next->next;
						}
						else freemem->next = NULL;
						if (freemem->prev)
							freemem->prev->next = freemem;
						else freemem->prev = NULL;
					}
				}
				if (newfreemem->prev) {
					if (newfreemem->prev->is_available)
						freemem = newfreemem->prev;
					if (freemem->next)
						freemem->size += freemem->next->size + freesize;
					if (freemem->next) {
						if (freemem->next->next) {
							freemem->next->next->prev = freemem;
							freemem->next = freemem->next->next;
						}
						else
							freemem->next = NULL;
					}
				}
			}
		}
	}

	void memdone() {
		memlist = NULL;
		allsize = 0;
	}
