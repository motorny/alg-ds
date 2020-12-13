#include <malloc.h>
#include <stdio.h>
#include "memallocator.h"

#define ERROR_INIT 1
#define ERROR_MEMORY_LEAK 2
#define NOT_ERRORS 0

#define CHECK_NUM 516                     

typedef struct block_t {
    int size;
    struct block_t* next;
    int check;
} block_t;

typedef struct {
    int size;
}last_t;

int error_my = NOT_ERRORS; //переменная для передачи ошибок


char* pHead = NULL;  //голова
int wholeSize = 0; //сколько всего памяти мы взяли для осуществления локатора           
block_t* startBlock = NULL; //указатель на место с которого начинаем искать память

int memgetminimumsize()
{
    return sizeof(block_t) + sizeof(int);
}

int memgetblocksize()
{
    return sizeof(block_t) + sizeof(int);
}


int meminit(void* pMemory, int size) {
    if (!pMemory) {
        error_my = ERROR_INIT;
        return ERROR_INIT;
    }
    if (size <= memgetblocksize()) {
        error_my = ERROR_MEMORY_LEAK;
        return ERROR_MEMORY_LEAK;
    }

    pHead = (char*)pMemory;
    wholeSize = size;

    startBlock = (block_t*)pMemory;
    startBlock->size = size - memgetminimumsize();
    startBlock->next = NULL;
    ((last_t*)((char*)startBlock + sizeof(block_t) + startBlock->size))->size = startBlock->size;

    return 0;
}

void* memalloc(int size) {
    block_t** nextBlock = &startBlock; 
    block_t** tFreeBlock = NULL;
    block_t* pMemory = NULL;
    int i = 0;
   



    if (pHead == NULL || size + memgetminimumsize() > wholeSize || size < 0) {
        return NULL;
    }

    while (*nextBlock) {
        if ((*nextBlock)->size >= size) {
            tFreeBlock = nextBlock;
            i++;
            if (i == 2) {
                break;
            }
        }
        nextBlock = &(*nextBlock)->next;
    }

    if (tFreeBlock == NULL) {
        return NULL;
    }

    pMemory = *tFreeBlock;

    if (pMemory->size > size + memgetminimumsize()) {
        (*tFreeBlock) = (block_t*)((char*)pMemory + memgetminimumsize() + size);
        (*tFreeBlock)->size = pMemory->size - memgetminimumsize() - size;
        (*tFreeBlock)->next = pMemory->next;
        ((last_t*)((char*)pMemory + pMemory->size + sizeof(block_t)))->size = (*tFreeBlock)->size;

        pMemory->size = size;
        pMemory->next = NULL;
        pMemory->check = CHECK_NUM;
        ((last_t*)((char*)pMemory + pMemory->size + sizeof(block_t)))->size = -1;

        return (char*)pMemory + sizeof(block_t);
        
    }

    *tFreeBlock = (*tFreeBlock)->next;
    ((last_t*)((char*)pMemory + pMemory->size + sizeof(block_t)))->size = -1;
    pMemory->next = NULL;
    pMemory->check = CHECK_NUM;

    return (char*)pMemory + sizeof(block_t);
   
}


void memfree(void* p) {
    block_t* tFreeBlock = (block_t*)((char*)p - sizeof(block_t));
    block_t* head = NULL;
    last_t* last = NULL;
    block_t** temp = NULL;
    int relation = 0;

  
  
   

    if (!p || !pHead || (pHead + wholeSize < (char*)p + sizeof(int) || ((char*)p - sizeof(block_t) < pHead))) {
        return;
    }
    if (tFreeBlock->check != CHECK_NUM) {
        return;
    }
    if (((last_t*)((char*)tFreeBlock + tFreeBlock->size + sizeof(block_t)))->size > 0) {
        return;
    }


    last = (last_t*)((char*)tFreeBlock - sizeof(last_t));

    if (last->size != -1 && (char*)last > pHead) {
        head = (block_t*)((char*)last - last->size - sizeof(block_t));
        if ((char*)head >= pHead) {
            head->size = head->size + tFreeBlock->size + memgetminimumsize();
            tFreeBlock->check = 0;
            ((last_t*)((char*)head + head->size + sizeof(block_t)))->size = head->size;
            tFreeBlock = head;
            relation = 1;
        }
    }

    head = (block_t*)((char*)tFreeBlock + tFreeBlock->size + memgetminimumsize());

    if ((char*)head - wholeSize < pHead) {
        last = (last_t*)((char*)head + head->size + sizeof(block_t));
        if (last->size != -1 && (char*)last - wholeSize < pHead) {
            tFreeBlock->size = tFreeBlock->size + head->size + memgetminimumsize();
            last->size = tFreeBlock->size;

            temp = &startBlock;
            while ((*temp) != NULL && (*temp) != head) {
                temp = &(*temp)->next;
            }
            *temp = tFreeBlock;

            if (relation) {
                if (head->next != tFreeBlock) {
                    if (tFreeBlock->next == head) {
                        tFreeBlock->next = head->next;
                    }
                    else {
                        *temp = head->next;
                    }
                }
            }
            else {
                tFreeBlock->next = head->next;
            }
            relation = 1;
        }
    }

    if (relation) {
        return;
    }
    else {
        tFreeBlock->next = startBlock;
        startBlock = tFreeBlock;
        ((last_t*)((char*)tFreeBlock + tFreeBlock->size + sizeof(block_t)))->size = tFreeBlock->size;
    }
}

void memdone() {
    if (wholeSize <= 0 || pHead == NULL || startBlock != NULL && (wholeSize == startBlock->size + memgetblocksize())) {
        return;
    }
    else {
        error_my = ERROR_MEMORY_LEAK;
    }
}