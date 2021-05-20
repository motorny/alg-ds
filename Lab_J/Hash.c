#include <stdlib.h>
#include <string.h>
#include "Header.h"

int FuncForInit(htCell_t** ht, int htSize) 
{
    *ht = (htCell_t*)malloc(sizeof(htCell_t) * htSize);
    if (*ht == NULL)
    {
        return LABJ_FALSE;
    }
    for (int i = 0; i < htSize; i++)
    {
        (*ht)[i].status = 0;
    }
    return LABJ_TRUE;
}

unsigned int HashFunc1(char* str, int size) 
{
    unsigned int res = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        res += (unsigned int)str[i];
        res %= size;
    }

    return res;
}

unsigned int HashFunc2(char* str, int size) 
{
    unsigned int res = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        res += (unsigned int)str[i] + res * 2;
        res %= size;
    }
    return res;
}

int FuncForInsert(htCell_t* ht, int htSize, char* str) 
{
    unsigned int x, y;

    if (strlen(str) > 100)
    {
        return LABJ_FALSE;
    }

    x = HashFunc1(str, htSize), y = HashFunc2(str, htSize);
    for (int i = 0; i < htSize; i++) 
    {
        if (ht[x].status == 0 || ht[x].status == 2) 
        {
            strcpy(ht[x].str, str);
            ht[x].status = 1;
            return LABJ_TRUE;
        }
        else if (ht[x].status == 1 && strcmp(ht[x].str, str) == 0)
        {
            return LABJ_FALSE;
        }
        else
        {
            x = (x + y) % htSize;
        }
    }
    return LABJ_FALSE;
}

int FuncForFind(htCell_t* ht, int htSize, char* str) 
{
    unsigned int x, y;

    if (strlen(str) > 100)
    {
        return LABJ_FALSE;
    }

    x = HashFunc1(str, htSize), y = HashFunc2(str, htSize);
    for (int i = 0; i < htSize; i++) 
    {
        if (ht[x].status == 1 && strcmp(ht[x].str, str) == 0)
        {
            return LABJ_TRUE;
        }
        else if (ht[x].status == 0)
        {
            return LABJ_FALSE;
        }
        x = (x + y) % htSize;
    }
    return LABJ_FALSE;
}

int FuncForDelete(htCell_t* ht, int htSize, char* str) 
{
    unsigned int x, y;
    if (strlen(str) > 100)
    {
        return LABJ_FALSE;
    }
    x = HashFunc1(str, htSize), y = HashFunc2(str, htSize);
    for (int i = 0; i < htSize; i++)
    {
        if (ht[x].status == 1 && strcmp(ht[x].str, str) == 0) 
        {
            ht[x].status = 2;
            return LABJ_TRUE;
        }
        else if (ht[x].status == 0)
        {
            return LABJ_FALSE;
        }
        x = (x + y) % htSize;
    }
    return LABJ_FALSE;
}

int FuncForClear(htCell_t** ht, int htSize)
{
    free(*ht);
    *ht = NULL;
    return LABJ_TRUE;
}