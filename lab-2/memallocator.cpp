#include "stdio.h"
#include "memallocator.h"

#define TRUE 1
#define FALSE 0
#define NULL 0
#define KEY 42

typedef unsigned char byte;

typedef struct node_t node_t;
struct node_t {
    int size;
    char isAvalibale;
    int Key;
    node_t * next;
    node_t * prev;
};

typedef struct nodeEnd_t {
    int size;
} nodeEnd_t;

byte * allocMem = NULL;
int allocSize = 0;

node_t * freeMem = NULL;

int meminit(void * pMemory, int size) {
    if (size <= 0 || size < memgetminimumsize() || pMemory == NULL)
        return FALSE;

    allocMem = (byte *) pMemory;
    allocSize = size;
    freeMem = (node_t *) pMemory;

    freeMem->next = NULL;
    freeMem->prev = NULL;
    freeMem->size = size - memgetblocksize();
    freeMem->Key = KEY;
    freeMem->isAvalibale = TRUE;

    ((nodeEnd_t *) ((byte *) freeMem + freeMem->size + sizeof(node_t)))->size = freeMem->size;
    return TRUE;
}

void memdone() {
    allocMem = NULL;
    allocSize = 0;
    freeMem = NULL;
}

void deleteFromList(node_t * node) {
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        freeMem = freeMem->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
}

void makeDefragmentation(node_t * memoryBlock) {
    node_t * prev = NULL, * next = NULL;
    nodeEnd_t * endPrev = NULL, * endOfBlock = NULL, * endNext = NULL;

    if (memoryBlock == NULL || memoryBlock->Key != KEY)
        return;

    endOfBlock = (nodeEnd_t *) ((byte *) memoryBlock + sizeof(node_t) + memoryBlock->size);
    if ((byte *) endOfBlock + sizeof(nodeEnd_t) < allocMem + allocSize - 2) {
        next = (node_t *) ((byte *) endOfBlock + sizeof(nodeEnd_t));
        endNext = (nodeEnd_t *) ((byte *) next + next->size + sizeof(node_t));
    }
    if ((byte *) memoryBlock - sizeof(nodeEnd_t) > allocMem) {
        endPrev = (nodeEnd_t *) ((byte *) memoryBlock - sizeof(nodeEnd_t));
        prev = (node_t *) ((byte *) endPrev - endPrev->size - sizeof(node_t));
    }

    if (next != NULL && next->Key == KEY && next->isAvalibale) {
        deleteFromList(next);

        memoryBlock->size += sizeof(nodeEnd_t) + sizeof(node_t) + next->size;
        endNext->size = memoryBlock->size;
        next->Key = 0;
        endOfBlock = endNext;
    }
    if (prev != NULL && prev->Key == KEY && prev->isAvalibale) {
        deleteFromList(memoryBlock);

        prev->size += sizeof(nodeEnd_t) + sizeof(node_t) + memoryBlock->size;
        endOfBlock->size = prev->size;
        memoryBlock->Key = 0;
        endPrev = endOfBlock;
    }
}

void * memalloc(int size) {
    node_t * toFindInList = freeMem, * newMemoryBlock;
    nodeEnd_t * firstEnd, * secondEnd;

    if (allocMem == NULL || size <= 0 || freeMem == NULL)
        return NULL;

    while (toFindInList != NULL) {
        if (toFindInList->size >= size) {
            // split mem block
            if (toFindInList->size > size + sizeof(node_t) + sizeof(nodeEnd_t)) {
                deleteFromList(toFindInList);

                firstEnd = (nodeEnd_t *) ((byte *) toFindInList + sizeof(node_t) + size);
                firstEnd->size = size;

                node_t * newMemBlock = (node_t *) ((byte *) firstEnd + sizeof(nodeEnd_t));
                newMemBlock->isAvalibale = TRUE;
                newMemBlock->Key = KEY;
                newMemBlock->next = freeMem;
                newMemBlock->prev = NULL;
                newMemBlock->size = toFindInList->size - size - sizeof(nodeEnd_t) - sizeof(node_t);
                if (freeMem)
                    freeMem->prev = newMemBlock;
                freeMem = newMemBlock;

                secondEnd = (nodeEnd_t *) ((byte *) newMemBlock + sizeof(node_t) + newMemBlock->size);
                secondEnd->size = newMemBlock->size;

                toFindInList->size = size;
                toFindInList->Key = KEY;
            } else
                deleteFromList(toFindInList);

            toFindInList->isAvalibale = FALSE;
            toFindInList->next = NULL;
            toFindInList->prev = NULL;

            return (void *) ((byte *) toFindInList + sizeof(node_t));
        }
        toFindInList = toFindInList->next;
    }
    return NULL;
}

void memfree(void * p) {
    node_t * ptrToDelete;

    if (p == NULL || (byte *) p - allocMem < 0 || (byte *) p - allocMem > allocSize ||
        ((node_t *) ((byte *) p - sizeof(node_t)))->Key != KEY)
        return;

    ptrToDelete = (node_t *) ((byte *) p - sizeof(node_t));
    ptrToDelete->isAvalibale = TRUE;
    ptrToDelete->next = freeMem;
    ptrToDelete->prev = NULL;
    if (freeMem)
        freeMem->prev = ptrToDelete;
    freeMem = ptrToDelete;
    makeDefragmentation(ptrToDelete);
}

int memgetblocksize() {
    return sizeof(node_t) + sizeof(nodeEnd_t);
}

int memgetminimumsize() {
    return sizeof(node_t) + sizeof(nodeEnd_t);
}