#include <stdio.h>
#include <stdlib.h>
#include "lab_j.h"

#pragma warning(disable : 4996)

hashtable_t* CreateTable(int size) {
    if (size == 0)
        return NULL;
    hashtable_t* table = malloc(sizeof(struct hashtable_t));
    if (!table)
        return NULL;
    table->size = size;
    table->table = (node_t**)malloc(sizeof(node_t*) * size);
    if (!table->table) {
        free(table);
        return NULL;
    }
    for (int i = 0; i < table->size; i++)
        table->table[i] = NULL;
    return table;
}

bool_t CreateNewNode(node_t** field) {
    *field = malloc(sizeof(node_t));
    if (!*field)
        return FALSE;
    (*field)->next = NULL;
    (*field)->value = 0;
    return TRUE;
}

int HashFunc(hashtable_t* table, int value) {
    int res = abs(value) % table->size;
    return res;
}

bool_t HashTableFind(hashtable_t* hashtable, int value) {
    int num = HashFunc(hashtable, value);
    node_t* comp = hashtable->table[num];
    while (comp) {
        if (comp->value == value)
            return TRUE;
        comp = comp->next;
    }
    return FALSE;
}

void HashTableAdd(hashtable_t* table, int value) {
    if (HashTableFind(table, value))
        return;
    int num = HashFunc(table, value);
    node_t** field = &table->table[num];
    node_t** next = field;
    if (!*next) {
        if (!CreateNewNode(next))
            return;
        (*next)->value = value;
    }
    else {
        while (*next) {
            field = next;
            next = &(*next)->next;
        }
        if (!CreateNewNode(next))
            return;
        (*next)->value = value;
        (*field)->next = *next;
    }

}

void HashTableRemove(hashtable_t* table, int value) {
    if (!HashTableFind(table, value))
        return;
    int num = HashFunc(table, value);
    node_t* field = table->table[num];
    node_t* prev = field;
    if (field->value == value) {
        table->table[num] = field->next;
        free(field);
    }
    else {
        while (field) {
            if (field->value == value) {
                prev->next = field->next;
                free(field);
                return;
            }
            prev = field;
            field = field->next;
        }
    }
}

void HashTableDestroy(hashtable_t* table) {
    if (!table)
        return;
    for (int i = 0; i < table->size; i++) {
        node_t* field = table->table[i];
        while (field) {
            node_t* toDelete = field;
            field = field->next;
            free(toDelete);
        }
    }
    free(table->table);
    free(table);
}

void WhatToDo() {
    int size = MAX_SIZE;
    hashtable_t* table = CreateTable(size);
    char c = getchar();
    int value;
    while (c != EOF) {
        scanf("%d", &value);
        switch (c)
        {
        case 'a':
            HashTableAdd(table, value);
            break;
        case 'r':
            HashTableRemove(table, value);
            break;
        case 'f':
            if (HashTableFind(table, value))
                printf("yes\n");
            else
                printf("no\n");
            break;
        }
        c = getchar();
        if (c == '\r')
            c = getchar();
        if (c == '\n')
            c = getchar();
    }
    HashTableDestroy(table);
    table = NULL;
}