
//
// Created by ikuzin on 03.11.2020.
//
#include "cstdlib"

struct memblock { /* заголовок блока: */
    struct memblock *nextPtr;/* след. блок в списке свободных */
    struct memblock *prevPtr;
    int size; /* размер этого блока */
};
typedef struct memblock DESCR;


typedef union memblockEnd {
    int size;
} END_DESCR;

int memgetminimumsize() {
    return sizeof(DESCR) + sizeof(END_DESCR);
}

int memgetblocksize() {
    return sizeof(DESCR) + sizeof(END_DESCR);
}

char *memBase = nullptr;
DESCR *memH = nullptr;
int memSize;

int meminit(void *ptr, int size) {
    if (!ptr || size < memgetminimumsize()) {
        return 0;
    }
    memSize = size;
    memBase = (char *) ptr;
    memH = (DESCR *) ptr;
    memH->nextPtr = nullptr;
    memH->prevPtr = nullptr;
    memH->size = size - memgetblocksize();
    ((END_DESCR *) (memBase + memH->size +sizeof(DESCR)))->size = memH->size;
    return 1;
}

void *memalloc(int size) {
    if (memH == nullptr || size <= 0) {
        return nullptr;
    }
    DESCR *p, *newAlloc;
    char *pEnd;
    END_DESCR *endDescr;
    p = memH;

    for (p; p != nullptr; p = p->nextPtr) {
        if (p->size >= size) { /* достаточно большой */
            if (p->size <= size + memgetblocksize()) {
                if (p->prevPtr != nullptr) {
                    p->prevPtr->nextPtr = p->nextPtr;
                }
                if (p->nextPtr != nullptr) {
                    p->nextPtr->prevPtr = p->prevPtr;
                }
                pEnd = (char *) p + sizeof(DESCR);
                if (p == memH)
                    memH = memH->nextPtr;
            } else {
                endDescr = (END_DESCR *) ((char *) p + sizeof(DESCR) + size);
                endDescr->size = size;

                newAlloc = (DESCR *) ((char *) (endDescr) + sizeof(END_DESCR));
                newAlloc->size = p->size - size - memgetblocksize();
                endDescr = (END_DESCR *) ((char *) newAlloc + sizeof(DESCR) + newAlloc->size);
                endDescr->size = newAlloc->size;
                pEnd = (char *) p + sizeof(DESCR);

                ((DESCR *) (pEnd - sizeof(DESCR)))->size = size;

                if (p->prevPtr != nullptr)
                    p->prevPtr->nextPtr = p->nextPtr;
                if (p->nextPtr != nullptr)
                    p->nextPtr->prevPtr = p->prevPtr;
                else if (memH != nullptr) {
                    memH = memH->nextPtr;
                }
                newAlloc->nextPtr = memH;
                newAlloc->prevPtr = nullptr;
                if (memH != nullptr)
                    memH->prevPtr = newAlloc;
                memH = newAlloc;
            }
            ((DESCR *) (pEnd - sizeof(DESCR)))->nextPtr = nullptr;
            ((DESCR *) (pEnd - sizeof(DESCR)))->prevPtr = nullptr;
            return pEnd;
        }
    }
    return nullptr;
}

void memfree(void *ap) {
    if (!ap || (char *) ap <= memBase || (char *) ap >= memBase + memSize) {
        return;
    }

    DESCR *delBlockPtr = (DESCR *) ((char *) ap - sizeof(DESCR));
    DESCR *curr = memH, *next, *prev, *tmp = nullptr, *tmpPrev = nullptr, *tmpNext = nullptr;
    END_DESCR *end;

    if (memH != nullptr)
        memH->prevPtr = delBlockPtr;
    delBlockPtr->nextPtr = memH;
    delBlockPtr->prevPtr = nullptr;
    if (delBlockPtr->nextPtr == nullptr)
        return;
    if ((char *) delBlockPtr + memgetblocksize() + delBlockPtr->size < memBase + memSize)
        next = (DESCR *) ((char *) delBlockPtr + memgetblocksize() + delBlockPtr->size);
    else
        next = nullptr;

    if ((char *) delBlockPtr > memBase) {
        end = (END_DESCR *) ((char *) delBlockPtr - sizeof(END_DESCR));
        if (end->size >= 0)
            prev = (DESCR *) ((char *) delBlockPtr - memgetblocksize() - end->size);
        else
            prev = nullptr;
    }

    end = (END_DESCR *) ((char *) delBlockPtr - sizeof(DESCR) + delBlockPtr->size);
    if (next != nullptr) {
        end->size = delBlockPtr->size;

        tmp = next;
        tmpNext = tmp->nextPtr;
        tmpPrev = tmp->prevPtr;
    }
    if (prev != nullptr) {
        prev->size += memgetblocksize() + delBlockPtr->size;
        end->size = prev->size;
        tmp = delBlockPtr;
        tmpNext = tmp->nextPtr;
        tmpPrev = tmp->prevPtr;
    }

    if (tmpNext != nullptr)
        tmpNext->prevPtr = tmpPrev;
    if (tmpPrev != nullptr)
        tmpPrev->nextPtr = tmpNext;
    else if (memH != nullptr)
        memH = tmpNext;
}


void memdone() {
    memBase = NULL;
    memSize = 0;
    memH = nullptr;
};// You can implement memory leak checks here;