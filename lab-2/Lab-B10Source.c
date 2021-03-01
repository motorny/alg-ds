#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"memallocator.h"

int DIM;
void* onset;
typedef struct blockMry {
	int release;
	struct blockMry* forward;
	int dim;
} blockMry;

int memgetminimumsize() {
	return sizeof(blockMry);
}
int memgetblocksize() {
	return sizeof(blockMry);
}

int meminit(void* ptrMem, int dim) {
	if (!ptrMem || (dim < memgetminimumsize())) {
		return 0;
	}
	onset = ptrMem;
	DIM = dim;
	blockMry* block = (blockMry*)onset;
	block->dim = DIM;
	block->release = 1;
	block->forward = NULL;
	return 1;
}

blockMry* getBlock(int dim) {
	blockMry* block = (blockMry*)onset;
	while (block) {
		if (block->release && (block->dim) >= dim) {
			return block;
		}
		block = block->forward;
	}
	return NULL;
}

void* memalloc(int dim) {
	if (dim <= 0) {
		return NULL;
	}
	dim = dim + memgetblocksize();
	blockMry* block = getBlock(dim);
	if (!block) {
		return NULL;
	}
	block->release = 0;
	if ((block->dim - dim) <= memgetblocksize()) {
		return (void*)((char*)block + memgetblocksize());
	}
	int lastDim = block->dim - dim;
	block->dim = dim;
	blockMry* forward = (blockMry*)((char*)block + dim);
	forward->release = 1;
	forward->dim = lastDim;
	forward->forward = NULL;
	block->forward = forward;
	return (void*)((char*)block + memgetblocksize());
}

void memfree(void* ptr) {
	if (!ptr || (ptr == onset)) {
		return;
	}
	else {
		ptr = (blockMry*)((char*)ptr - memgetblocksize());
	}
	blockMry* releaseb = (blockMry*)ptr;
	blockMry* backward = (blockMry*)onset;
	blockMry* forward = NULL;
	blockMry* save = NULL;
	save = (blockMry*)onset;
	while ((save!=releaseb) && (save!=NULL)){
		save = save->forward;
	}
	if ((!save) || (releaseb->release == 1)) {
		return;
	}
	while ((backward != releaseb) && (backward->forward != releaseb)) {
		backward = backward->forward;
	}
	if (releaseb->forward != NULL) {
		forward = releaseb->forward;
	}
	if ((forward != NULL) && (forward->release == 1)) {
		save = forward;
		releaseb->forward = forward->forward;
		releaseb->dim = releaseb->dim + forward->dim;
		save->dim = -1;
		save->release = 1;
		save->forward = NULL;
	}
	if ((backward != releaseb) && (backward->release == 1)) {
		save = releaseb;
		backward->forward = releaseb->forward;
		backward->dim = backward->dim + releaseb->dim;
		save->dim = -1;
		save->release = 1;
		save->forward = NULL;
		releaseb = backward;
	}
	releaseb->release = 1;
}
void memdone() {
	blockMry* block = (blockMry*)onset;
	while (block) {
		if (block->release == 0) {
			block->release = 1;
		}
		block = block->forward;
	}
}






