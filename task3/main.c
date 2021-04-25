#include "hashtable.h"

#include <stdio.h>

int main()
{
    unsigned int size = 999983;
    HashTable_ptr table = CreateHashTable(size);

    char c = getchar();
    int number;
    while (c != EOF)
    {
        scanf("%d", &number);
        switch (c)
        {
        case 'a':
            HashTableAdd(table, number);
            break;
        case 'r':
            HashTableRemove(table, number);
            break;
        case 'f':
            if (HashTableFind(table, number))
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            printf("Incorrect input");
            return 0;
        }

        c = getchar();
        if(c == '\r')
            c = getchar();
        if(c == '\n')
            c = getchar();
    }

    DestroyHashTable(table);
    table = NULL;
    return 0;
}
