/*#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#include <stdio.h>
#include "memallocator.h"

#define SUCCESS 0
#define ERROR 1
#define FREE 1
#define FILLED 0

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_t {
    int size;
    int state;
    struct list_t* next;
} list_t;

void *memoryStart = NULL;
int memorySize = 0;
list_t *firstBlock = NULL;
int flag = -1;

int memgetminimumsize() {
    return (int)sizeof(list_t) + sizeof(int);
}

int memgetblocksize() {
    return (int)sizeof(list_t) + sizeof(int);
}

int meminit(void *pMemory, int size) {
    if (pMemory == NULL || size <= 0) {
        return ERROR;
    }

    memoryStart = pMemory;
    firstBlock = (list_t *)memoryStart;
    memorySize = size;

    firstBlock->next = NULL;
    firstBlock->size = memorySize - memgetblocksize();
    firstBlock->state = FREE;
    //*((int *) ((char *) memoryStart + memorySize - sizeof(int))) = firstBlock->size;
    
    return SUCCESS;
}

void memdone() {

    if ((memoryStart == NULL || memorySize <= 0 || firstBlock != NULL && memorySize == firstBlock->size + memgetblocksize()) == 1) {
        printf("Detected memory leaks!\n");
    }

}

void* memalloc(int size) {
    list_t *temp = firstBlock, *p = NULL;
    list_t **next = &firstBlock;
    void *result = NULL;
    int minSize;
    list_t *nextBlock;

    if (size < 0 || memoryStart == NULL || firstBlock == NULL) {
        return NULL;
    }

    minSize = temp->size;

    while ( temp != NULL ) {
        if (temp->size >= size && temp->size <= minSize && temp->state == FREE) {
            minSize = temp->size;
            p = temp;
        }

        next = &temp->next;
        temp = temp->next;
    }

    if (p == NULL) {
        return NULL;
    }

    result = (void *)((char *) p + sizeof(list_t));

    if ( p->size >= memgetblocksize() + size ) {
        nextBlock = (list_t *)((char *)p + memgetblocksize() + size);
        nextBlock->size = p->size - (memgetblocksize() + size);
        *((int *) ((char *) nextBlock + nextBlock->size + sizeof(list_t))) = nextBlock->size;
        nextBlock->next = p->next;
        *next = nextBlock;

        p->size = size;
        *((int *) ((char *) p + p->size + sizeof(list_t))) = p->size;
    }
    else {
        *next = p->next;
    }

    p->next = NULL;

    return result;
}

void memfree(void* p) {
    int state = 0;
    list_t *block;

    if (p == NULL || (char*)p - sizeof(list_t) < (char*)memoryStart || (char*)p > (char*)memoryStart + memorySize) {
        return;
    }

    block = (list_t *)((char *) p - sizeof(list_t));

    if ( (char *) block >= (char *) memoryStart + memgetblocksize() ) {
        list_t *previous = (list_t *) ((char *) block - memgetblocksize() - *((int *) ((char *) block - sizeof(int))));
        list_t *p1 = firstBlock;

        while ( p1 != NULL ) {
            if (p1 == previous) {
                break;
            }

            p1 = p1->next;
        }

        if ( p1 != NULL ) {
            previous->size += memgetblocksize() + block->size;
            *((int *) ((char *) previous + previous->size + sizeof(list_t))) = previous->size;
            block = previous;
            state = 1;
        }
    }

    if ( block + block->size + memgetblocksize() + memgetblocksize() >= (list_t *) memoryStart + memorySize ) {
        list_t *next = (list_t *) ((char *)block + block->size + memgetblocksize());
        list_t **p1 = &firstBlock;

        while ( *p1 != NULL ) {
            if (*p1 == next) {
                break;
            }

            p1 = &(*p1)->next;
        }

        if ( *p1 != NULL ) {
            if ( state ) {
                *p1 = next->next;
            }
            else {
                *p1 = block;
            }

            block->size += memgetblocksize() + next->size;
            *((int *) ((char *) block + block->size + memgetblocksize())) = block->size;

            state = 1;
        }
    }

    if ( state == 0 ) {
        firstBlock = block;
    }
}

#ifdef __cplusplus
}
#endif

#endif */

#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#include <stdio.h>
#include "memallocator.h"

#define SUCCESS 1
#define ERROR 0
#define FREE 1
#define FILLED 0

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct list {
        int size;
        int state;
        struct list* next;
    } list;

    void* first = NULL;
    int memSize = 0;
    list* startBlock = NULL;
    int flag = -1;

    int memgetminimumsize() {
        return sizeof(list);
    }

    int memgetblocksize() {
        return sizeof(list);
    }

    int meminit(void* pMemory, int size) {
        if (size <= 0 || pMemory == NULL || size < memgetminimumsize()) {
            return ERROR;
        }

        first = pMemory;
        memSize = size;

        startBlock = (list*)first;

        startBlock->size = size;
        startBlock->next = NULL;
        startBlock->state = FREE;

        return SUCCESS;
    }

    void memdone() {
        if ((startBlock == NULL || memSize <= 0 || startBlock != NULL && memSize == startBlock->size + memgetblocksize()) == 1) {
            printf("Detected memory leaks!\n");
        }
    }

    void* memalloc(int size) {
        list* temp = (list*)first;
        list* p = NULL;
        list* next;
        int minSize = flag;
        int newSize;

        while (temp != NULL) {
            if ((temp-> size) >= (size + memgetblocksize()) && (temp->size < minSize || minSize == flag) && temp->state == FREE) {
                p = temp;
                minSize = temp->size;
            }
            temp = temp->next;
        }

        if (p == NULL) {
            return NULL;
        }

        size = size + memgetblocksize();

        if (size > memgetblocksize()) {
            p->state = FILLED;

            if (p->size <= memgetblocksize() + size) {
                return (void*)((char*)p + memgetblocksize());
            }

            newSize = p->size - size;
            p->size = size;
            next = (list*)((char*)p + size);
            next->size = newSize;
            next->next = NULL;
            next->state = FREE;
            p->next = next;
            
            return (void*)((char*)p + memgetblocksize());
        }
        
        return NULL;
    }

    void Unite(list* p1, list* p2, list* p3) {
        p1 = p2;

        p3->next = p2->next;
        p3->size += p2->size;
        p1->state = FREE;
        p1->size = flag;
        p1->next = NULL;
    }

    void memfree(void* p) {
        list* free, * previous, * next, * temp;

        if (p == first) {
            return;
        }

        if (!p) {
            return;
        }

        p = (list*)((char*)p - memgetblocksize());
        free = (list*)p;
        previous = (list*)first;
        next = NULL;
        temp = (list*)first;

        while (!((temp == free) || (temp == NULL))) {
            temp = temp->next;
        }

        if ((!temp) || (free->state == FREE)) {
            return;
        }

        while (!((previous == free) || (previous->next == free))) {
            previous = previous->next;
        }

        if (free->next != NULL) {
            next = free->next;
        }

        if ((next != NULL) && (next->state == FREE)) {
            Unite(temp, next, free);
        }

        if ((previous != free) && (previous->state == FREE)) {
            Unite(temp, free, previous);
            free = previous;
        }

        free->state = FREE;

    }


#ifdef __cplusplus
}
#endif

#endif 