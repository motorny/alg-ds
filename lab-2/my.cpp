#ifdef __cplusplus
extern "C" {
#endif

#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#define ABS(x) ((x)>=0?(x):(-x))

	typedef struct descriptor {
		int size;
		struct descriptor* next;
	}descriptor;

	typedef struct {
		descriptor* desc;
	}memAllocator;

	memAllocator Allocator = { (descriptor*)NULL };
	int memgetminimumsize() {
		return sizeof(descriptor);
	}

	int memgetblocksize() {
		return sizeof(descriptor);
	}

	int meminit(void* InitMem, int size) {
		if (!InitMem || size <= memgetminimumsize())
			return 0;
		descriptor desc = { -(size - memgetminimumsize()),NULL };
		*((descriptor*)InitMem) = desc;
		Allocator.desc = (descriptor*)InitMem; 
		return 1;
	}

	void* memalloc(int size) {
		if (size <= 0 || !Allocator.desc)
			return NULL;
		void* PtrToReturn = NULL;
		int FoundCounter = 0, sizebefore;
		descriptor* usual = Allocator.desc, *required = NULL, *addnext = NULL, *firstfit = NULL;
		while (usual) {
			if (usual->size < 0 && ABS(usual->size) >= size) {
				if (FoundCounter == 0) {
					FoundCounter++;
					firstfit = usual;
				}
				else if (FoundCounter == 1) {
					FoundCounter++;
					break;
				}
			}
			required = usual;
			usual = usual->next;
		}
		if (FoundCounter) {
			if (FoundCounter == 1)
				required = firstfit;
			else 
				required = usual;
			sizebefore = -(required->size);
			PtrToReturn = (void*)(required + 1); 
			required->size = size;
			if (sizebefore - size > memgetblocksize()) {
				addnext = (descriptor*)((char*)PtrToReturn + size);
				addnext->next = required->next; 
				addnext->size = -(sizebefore - size - memgetblocksize());
				required->next = addnext;
			}
			else required->size = sizebefore; 
			return PtrToReturn;
		}
		else 
			return NULL;
	}

	void memfree(void* memory) {
		int block = memgetblocksize();
		descriptor* iter = Allocator.desc, *prev = NULL, *next = NULL;
		while (iter) {
			if ((char*)memory - (char*)(iter + 1) > 0) {
				prev = iter;
				iter = iter->next;
			}
			else if ((char*)(iter + 1) == (char*)memory)
				break;
			else return;
		}
		if (!iter || iter->size < 0) 
			return;
		iter->size = -iter->size;
		if (prev && prev->size < 0) {
			prev->size = -(ABS(prev->size) + block + ABS(iter->size));
			prev->next = iter->next;
		}
		next = iter->next;
		if (next && next->size < 0) {
			if (prev && prev->size < 0)
				iter = prev;
			iter->size = -(ABS(iter->size)+ block + ABS(next->size));
			iter->next = next->next;
		}
	}

	void memdone() {
		descriptor* desc = Allocator.desc;
		int leaks = 0;
		while (desc) {
			if (desc->size > 0) {
				leaks = 1;
				//printf("\nMemory leak: %i bytes of %p\n", desc->size, desc);
			}
			desc = desc->next;
		}
	}

#ifdef __cplusplus
}
#endif 