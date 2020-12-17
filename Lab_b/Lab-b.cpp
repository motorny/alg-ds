#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "memallocator.h"


#define good 1
#define problem -1

typedef struct LIST 
{
    struct LIST* next;
    struct LIST* prev;
    int size_t;
} list;

static struct
{
    LIST* place_in_mem;
    LIST* current_pointer;
    int totalSize;
} InfoMem = { (LIST*)NULL, (LIST*)NULL, 0 };



int memgetminimumsize(void) 
{
    return 2 * (sizeof(LIST) + sizeof(int));
}


int memgetblocksize(void)
{
    return sizeof(LIST) + sizeof(int);
}


int meminit(void* p, int size) 
{
    int minsize = memgetminimumsize();
    int Size_header_and_ender = memgetblocksize();

    if (!p || size < minsize)
    {
        return problem;
    }
    InfoMem.place_in_mem = (LIST*)p;
    InfoMem.totalSize = size;
    InfoMem.place_in_mem->next = (LIST*)((char*)p + Size_header_and_ender);
    InfoMem.place_in_mem->prev = (LIST*)((char*)p + Size_header_and_ender);
    InfoMem.place_in_mem->size_t = 0;
    *(int*)(InfoMem.place_in_mem + 1) = 0;
    InfoMem.place_in_mem->next->next = InfoMem.place_in_mem;
    InfoMem.place_in_mem->next->prev = InfoMem.place_in_mem;
    InfoMem.place_in_mem->next->size_t = size - minsize;
    *(int*)((char*)p + size - sizeof(int)) = InfoMem.place_in_mem->next->size_t;
    InfoMem.current_pointer = InfoMem.place_in_mem->next;
    return good;
    
}


void* memalloc(int size) 
{
    int status = 0;
    LIST* current;
    LIST* NEW;
    void* res = NULL;
    if (size > InfoMem.totalSize)
        return res;
    int Size_header_and_ender = memgetblocksize();

    if (InfoMem.place_in_mem) 
    {
        current = InfoMem.current_pointer;
        do 
        {

            if (current->size_t < size)
            {
                current = current->next;
            }
            else if (current->size_t < size + Size_header_and_ender)
            {
                res = (void*)(current + 1);
                memset(res, 0, current->size_t);
                current->prev->next = current->next;
                current->next->prev = current->prev;
                InfoMem.current_pointer = current->next;
                current->next = NULL;
                *(int*)((char*)(current + 1) + current->size_t) = current->size_t;
                break;
            }
            else 
            {
                NEW = (LIST*)((char*)current + size + Size_header_and_ender);
                NEW->prev = current->prev;
                NEW->next = current->next;
                NEW->next->prev = NEW;
                NEW->prev->next = NEW;
                current->next = NULL;
                NEW->size_t = current->size_t - size - Size_header_and_ender;
                *(int*)((char*)(NEW + 1) + NEW->size_t) = NEW->size_t;
                current->size_t = size;
                *(int*)((char*)(current + 1) + size) = size;
                res = (void*)(current + 1);
                memset(res, 0, size);
                InfoMem.current_pointer = NEW;
                break;
            }
        } while (current != InfoMem.current_pointer);
    }

    return res;
}


void memfree(void* pointer) 
{
    int Size_header_and_ender = memgetblocksize();
    LIST* current;
    LIST* nextList;
    LIST* prevList;
    LIST* end = (LIST*)((char*)InfoMem.place_in_mem + InfoMem.totalSize);

    if (pointer != NULL) 
    {
        current = (LIST*)((char*)pointer - sizeof(LIST));
        nextList = (LIST*)((char*)pointer + current->size_t + sizeof(int));
        prevList = (LIST*)((char*)current - Size_header_and_ender - *(int*)((char*)pointer - Size_header_and_ender));
        if (nextList != end && nextList->next != NULL) 
        {
            current->size_t += nextList->size_t + Size_header_and_ender;
            if (nextList == InfoMem.current_pointer)
            {
                InfoMem.current_pointer = nextList->next;
            }
            nextList->prev->next = nextList->next;
            nextList->next->prev = nextList->prev;
            *(int*)((char*)(current + 1) + current->size_t) = current->size_t;
        }
        if (prevList != InfoMem.place_in_mem && prevList->next != NULL)
        {
            prevList->size_t += current->size_t + Size_header_and_ender;
            if (current == InfoMem.current_pointer)
            {
                InfoMem.current_pointer = prevList;
            }
            *(int*)((char*)(prevList + 1) + prevList->size_t) = prevList->size_t;
            return;
        }
        current->next = InfoMem.place_in_mem->next;
        InfoMem.place_in_mem->next->prev = current;
        current->prev = InfoMem.place_in_mem;
        InfoMem.place_in_mem->next = current;
    }
}
int CheckMemoryLeaks()
{
    LIST* testhead = InfoMem.current_pointer->next;
    return InfoMem.current_pointer == InfoMem.place_in_mem && testhead->size_t+ 32 == InfoMem.totalSize;
}
void memdone(void) 
{
    memset(InfoMem.place_in_mem, 0, InfoMem.totalSize);
    InfoMem.place_in_mem = NULL;
    InfoMem.current_pointer = NULL;
    InfoMem.totalSize = 0;
}
