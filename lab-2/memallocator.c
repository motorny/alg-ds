#include "memallocator.h"

int meminit(void* pMemory, int size) { //иницилизируем выделенную память для библиотеки
    if (pMemory == NULL || size <= 0) {
        error_my = ERROR_INIT;
        return ERROR_INIT;
    }

    pHead = pMemory;
    wholeSize = size;

    startBlock = (block_t*)pHead;// начало 
    startBlock->next = NULL;//следующего блока нету
    startBlock->size = wholeSize - memgetblocksize();


    *((int*)((char*)pHead + wholeSize - sizeof(int))) = wholeSize - memgetblocksize(); 
    //идет в конец чтобы поставить число размерности

    return NOT_ERRORS;
}


void memdone() {
    if (wholeSize <= 0 || pHead == NULL || startBlock != NULL && (wholeSize == startBlock->size + memgetblocksize())) {
        return;
    }
    else {
        error_my = ERROR_MEMORY_LEAK;
    }
}

void* memalloc(int size) {
    block_t* freeBlock = startBlock;
    block_t* tFreeBlock;
    block_t** nextBlock = &startBlock;

    void* pMem = NULL;
    block_t* nextFree = NULL;

    if (size < 0 || pHead == NULL || startBlock == NULL)
        return NULL;




    //бегаем по свободным блокам, те ищем подходящий
    while (freeBlock != NULL) {
        if (freeBlock->size >= size) { 
            break; 
        }
        else {
            nextBlock = &freeBlock->next;
            freeBlock = freeBlock->next;
        }
       
    }
    //не нашли
    if (freeBlock == NULL) {
        return NULL;
    }
    //сохраняем этот указатель
    tFreeBlock = freeBlock;



    //здесь ищем след свободный
    freeBlock = freeBlock->next;
    while (freeBlock != NULL) {
        if (freeBlock->size >= size) break;
        nextBlock = &freeBlock->next;
        freeBlock = freeBlock->next;
    }
    
    if (freeBlock == NULL) {
        freeBlock = tFreeBlock;
    }



    pMem = (char*)freeBlock + sizeof(block_t);

    //связываем блоки
    if (freeBlock->size >= memgetblocksize() + size) {//проверка на достаточность памяти
        nextFree = (block_t*)((char*)freeBlock + memgetblocksize() + size);
        *((int*)((char*)nextFree + sizeof(block_t) + nextFree->size)) = nextFree->size;
        nextFree->size = freeBlock->size - (memgetblocksize() + size);
        nextFree->next = freeBlock->next;


        *nextBlock = nextFree;

        freeBlock->size = size;
        *((int*)((char*)freeBlock + freeBlock->size + sizeof(block_t))) = freeBlock->size;
    }
    else {
        *nextBlock = freeBlock->next;
    }

    freeBlock->next = NULL;

    return pMem;
}

void memfree(void* p) {
    int relation = NOT_RELATION;
    block_t* partMem;


    if (!p || ((char*)pHead + wholeSize < (char*)p) || ((char*)p - sizeof(block_t) < (char*)pHead)) {
        return;
    }

    partMem = (block_t*)((char*)p - sizeof(block_t));

    if (((char*)pHead + memgetblocksize())<= (char*)partMem) {
        block_t* prevBlock = (block_t*)((char*)partMem - memgetblocksize() - *((int*)((char*)partMem - sizeof(int))));
        block_t* findBlock = startBlock;

        while (findBlock != NULL) {
            if (findBlock == prevBlock) {
                break;
            }
            findBlock = findBlock->next;
        }

        if (findBlock != NULL) {
            prevBlock->size += memgetblocksize() + partMem->size;
            *((int*)((char*)prevBlock + prevBlock->size + sizeof(block_t))) = prevBlock->size;
            partMem = prevBlock;
            relation = HAVE_RELATION;
        }
    }

    if (((block_t*)pHead + wholeSize)<=(partMem + partMem->size + memgetblocksize() + memgetblocksize())) {
        block_t* nextBlock = (block_t*)((char*)partMem + partMem->size + memgetblocksize());
        block_t** findBlock = &startBlock;

        while (*findBlock) {
            if (*findBlock == nextBlock) { 
                break; 
            }
            findBlock = &(*findBlock)->next;
        }

        if (*findBlock) {

            if (relation == HAVE_RELATION) {
                *findBlock = nextBlock->next;
            }
            else 
                *findBlock = partMem;

            partMem->size += memgetblocksize() + nextBlock->size;
            *((int*)((char*)partMem + partMem->size + memgetblocksize())) = partMem->size;
            relation = HAVE_RELATION;
        }
    }

    if (relation == NOT_RELATION) {
        startBlock = partMem;
    }
}

int memgetminimumsize() {
    return((int)sizeof(block_t) + sizeof(int));
}

int memgetblocksize() {
    return ((int)sizeof(block_t) + sizeof(int));

}