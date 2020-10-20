#include "memallocator.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAGICKEY 1337

typedef struct Node{
    struct Node *next, *prev;
    int size;
    int magicKey;
}node;

node* head = NULL;
char* listOrigin = NULL;
int memorySize;

int memgetminimumsize()
{
    return sizeof(node) + sizeof(int);
}

int memgetblocksize()
{
    return sizeof(node) + sizeof(int);
}

int meminit(void *pMemory, int size)
{
    if(pMemory == NULL || size < memgetminimumsize())
        return 0;

    memorySize = size;
    listOrigin = (char*)pMemory;

    head = (node*)pMemory;
    head->next = NULL;
    head->prev = NULL;
    head->size = size;

    *(int*)((char*)head + size - sizeof(int)) = size;

    return 1;
}

void* memalloc(int size)
{
    if(size <= 0 || head == NULL)
        return NULL;

    node* block = head;
    bool finded = false;

    while(block != NULL)
    {
        if(block->size >= size + memgetminimumsize())
        {
            finded = true;
            break;
        }
        block = block->next;
    }

    if(finded == false)
        return  NULL;

    block->magicKey = MAGICKEY; //to check on memfree

    int* blockEnd = (int*)((char*)block + block->size - sizeof(int));
    node* newBlock = (node*)((char*)block + size + memgetminimumsize());

    if((char*)newBlock + sizeof(node) >= (char*)blockEnd) //give up the whole block, as there is too little space left in the block
    {
        *blockEnd = -(*blockEnd); //show that the block is now NOT free

        if(block->prev != NULL)
            (block->prev)->next = block->next;
        else
            head = block->next;

        if(block->next != NULL)
            (block->next)->prev = block->prev;
    }
    else
    {
        *(int*)((char*)newBlock - sizeof(int)) = -(size + memgetminimumsize()); //show that the block is now NOT free

        newBlock->size = block->size - size - memgetminimumsize();
        newBlock->next = block->next;
        newBlock->prev = block->prev;

        if(block->prev != NULL)
            (block->prev)->next = newBlock;
        else
            head = newBlock;

        if(block->next != NULL)
            (block->next)->prev = newBlock;

        *(int*)((char*)newBlock + newBlock->size - sizeof(int)) = newBlock->size;

        block->next = NULL;
        block->size = size + memgetminimumsize();
    }
    return (char*)block + sizeof(node);
}

void memfree(void* p)
{
    //bad pointer check
    if(((char*)p < listOrigin + sizeof(node) || ((char*)p > listOrigin + memorySize - sizeof(int))))
        return;

    node* block = (node*)((char*)p - sizeof(node));
    int* blockEnd = (int*)((char*)block + block->size - sizeof(int));

    if(block->magicKey != MAGICKEY) //node is damaged
        return;

    block->magicKey = 0;

    node* tmp = block;
    int* prevTmpEnd;

    while((char*)tmp > listOrigin) //step back in search of a free block
    {
        prevTmpEnd = (int*)((char*)tmp - sizeof(int));
        tmp = (node*)((char*)tmp - abs(*prevTmpEnd));
        if(*prevTmpEnd > 0) //free block check
            break;
    }

    *blockEnd = -(*blockEnd);  //show that the block is now free

    if(*prevTmpEnd > 0 && tmp != block) //if 'tmp' is a free block
    {
        block->next = tmp->next;
        block->prev = tmp;
        tmp->next = block;
        if(block->next != NULL)
            (block->next)->prev = block;
    }
    else //make the block heading
    {
        block->prev = NULL;

        if(head != NULL)
            head->prev = block;

        block->next = head;
        head = block;
    }

    if(((char*)tmp + tmp->size == (char*)block) && (*prevTmpEnd > 0)) //trying to link the block to the block on the LEFT
    {
        tmp->next = block->next;
        tmp->size += block->size;
        *blockEnd = tmp->size;
        block = tmp;
    }

    if(block->next != NULL)
        if((char*)block + block->size == (char*)block->next) //trying to link the block to the block on the RIGHT
        {
            block->size += block->next->size;
            block->next = block->next->next;
            *(int*)((char*)block + block->size - sizeof(int)) = block->size;
        }
}

void memdone() //do nothing
{
}

int CheakMemoryLeaks() //function for test
{
    node* testhead = head;
    return (char*)head == listOrigin && head->size == memorySize;
}
