#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#include <stdio.h>
#include "memallocator.h"

#define SUCCESSED 1
#define FAILED 0
#define FREEBLOCK 1
#define NOTFREEBLOCK 0

#ifdef __cplusplus
extern "C" {
#endif

typedef struct block {
    int blockSize;
    int status;
    struct block* next;
} block;

void* headBlock = NULL;
int memSize = 0;
block* pStartBlock = NULL;
int flag = -1;

int memgetminimumsize() {
    return sizeof(block);
}

int memgetblocksize() {
    return sizeof(block);
}

int meminit(void* pMemory, int size) {
    if (size <= 0)
        return FAILED;
    if (pMemory != NULL && (size >= memgetminimumsize())){
        memSize = size;
        headBlock = pMemory;
       
        pStartBlock = (block*)headBlock;


        pStartBlock->next = NULL;
        pStartBlock->blockSize = size;
        pStartBlock->status = FREEBLOCK;

        return SUCCESSED;
    }
    else
        return FAILED;
}

void memdone() {
     headBlock = NULL;
     memSize = 0;
}

void* memalloc(int size) {
    block* tmp = (block*)headBlock;
    block* b = NULL;
    int bestFit = flag;
    int malSize;
    while (tmp != 0) {
        if ((tmp->blockSize) >= (size + memgetblocksize()) && (tmp->blockSize < bestFit || bestFit == flag) && tmp->status==FREEBLOCK) {//проверка на доступность
            b = tmp;
            bestFit = tmp->blockSize;
        }
        tmp = tmp->next;
    }
    size = size + memgetblocksize();

    if (size > memgetblocksize()&&b) {
        b->status = NOTFREEBLOCK;
        if (b->blockSize <= memgetblocksize() + size) {
            return (void*)((char*)b + memgetblocksize());
        }
        malSize = b->blockSize - size;
        b->blockSize = size;
        block* nextb = (block*)((char*)b + size);
        nextb->blockSize = malSize;
        nextb->next = NULL;
        nextb->status = FREEBLOCK;
        b->next = nextb;
        return (void*)((char*)b + memgetblocksize());
    }
    else return NULL;
}

void helpOp(block* b1, block* b2, block* b3) {
    b1 = b2;
    b3->next = b2->next;
    b3->blockSize += b2->blockSize;
    b1->status = FREEBLOCK;
    b1->blockSize = flag;
    b1->next = NULL;
}

void memfree(void* p) {
    if (p == headBlock)
        return;
    if (!p)
        return;
    p = (block*)((char*)p - memgetblocksize());
    block* freeb, * previous, * nextb, * tmp;
    freeb = (block*)p;
    previous = (block*)headBlock;
    nextb = NULL;
    tmp = (block*)headBlock;

    while (!((tmp == freeb) || (tmp == NULL))) {
        tmp = tmp->next;
    }

    if ((!tmp) || (freeb->status == FREEBLOCK))
        return;

    while (!((previous == freeb) || (previous->next == freeb))) {
        previous = previous->next;
    }

    if (freeb->next != NULL) {
        nextb = freeb->next;
    }
    if ((nextb != NULL) && (nextb->status == FREEBLOCK)) {
        helpOp(tmp, nextb, freeb);
    }
    if ((previous != freeb) && (previous->status == FREEBLOCK)) {
        helpOp(tmp, freeb, previous);
        freeb = previous;
    }
    freeb->status = FREEBLOCK;

}


#ifdef __cplusplus
}
#endif

#endif 