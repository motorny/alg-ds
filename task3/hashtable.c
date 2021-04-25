#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static unsigned int HashFunc(HashTable_ptr hashTable, int value)
{
    return abs(value) % hashTable->size;
}

static node* CreateNewNode(int value)
{
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode)
        return NULL;

    newNode->next = NULL;
    newNode->value = value;
    return newNode;
}

static void InsertNodeInField(node** field, int value)
{
    if (field == NULL)
        return;

    if (*field == NULL)
    {
        *field = CreateNewNode(value);
        return;
    }

    node* temp = *field;
    node* old = *field;
    while (temp != NULL)
    {
        if (temp->value == value)
            return;
        old = temp;
        temp = temp->next;
    }

    old->next = CreateNewNode(value);
}

static node* FindValueInField(node** field, int value)
{
    if (field == NULL)
        return NULL;

    node* temp = *field;
    while (temp != NULL)
    {
        if (temp->value == value)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

static void RemoveNodeFromField(node** field, int value)
{
    if (field == NULL)
        return;
    if (*field == NULL)
        return;

    if ((*field)->value == value)
    {
        node* itemToDelete = *field;
        *field = (*field)->next;
        free(itemToDelete);
        return;
    }

    node* temp = *field;
    while (temp->next != NULL)
    {
        if (temp->next->value == value)
        {
            node* itemToDelete = temp->next;
            temp->next = itemToDelete->next;
            free(itemToDelete);
            return;
        }
        temp = temp->next;
    }
}

HashTable_ptr CreateHashTable(unsigned int size)
{
    if (size == 0)
        return NULL;

    HashTable_ptr hashTable = (HashTable_ptr)malloc(sizeof(struct HashTable));
    if (!hashTable)
        return NULL;

    hashTable->size = size;
    hashTable->table = (node**)malloc(sizeof(node*) * size);
    if (!hashTable->table)
    {
        free(hashTable);
        return NULL;
    }

    for (unsigned i = 0; i != hashTable->size; ++i)
        hashTable->table[i] = NULL;

    return hashTable;
}

void HashTableAdd(HashTable_ptr hashTable, int value)
{
    if (!hashTable)
        return;

    int index = HashFunc(hashTable, value);
    InsertNodeInField(&hashTable->table[index], value);
}

void HashTableRemove(HashTable_ptr hashTable, int value)
{
    if (!hashTable)
        return;

    int index = HashFunc(hashTable, value);
    RemoveNodeFromField(&hashTable->table[index], value);
}

bool HashTableFind(HashTable_ptr hashTable, int value)
{
    if (!hashTable)
        return false;

    int index = HashFunc(hashTable, value);
    return FindValueInField(&hashTable->table[index], value) != NULL;
}

void HashTablePrint(HashTable_ptr hashTable)
{
    if (!hashTable)
        return;

    for (unsigned int i = 0; i != hashTable->size; ++i)
    {
        node* element = hashTable->table[i];
        printf("row %d:\t", i);
        while (element != NULL)
        {
            printf("%d  ", element->value);
            element = element->next;
        }
        printf("\n");
    }
}

void DestroyHashTable(HashTable_ptr hashTable)
{
    if (!hashTable)
        return;

    for (unsigned int i = 0; i != hashTable->size; ++i)
    {
        node* field = hashTable->table[i];
        while (field != NULL)
        {
            node* deleted = field;
            field = field->next;
            free(deleted);
        }
    }

    free(hashTable->table);
    free(hashTable);
}
