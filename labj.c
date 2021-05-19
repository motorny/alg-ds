#include <stdio.h>
#include <stdlib.h>
#include "labj.h"

#pragma warning(disable : 4996)


int CreateNode(node** newnode) {
    *newnode = malloc(sizeof(node));
    if (!*newnode)
        return 0;
    (*newnode)->next = NULL;
    (*newnode)->value = 0;
    return 1;
}

hashtable* CreateTable(int size) {
    if (size == 0)
        return NULL;
    hashtable* newtable = malloc(sizeof(struct hashtable));
    if (!newtable)
        return NULL;
    newtable->size = size;
    newtable->table = (node**)malloc(sizeof(node*) * size);
    if (newtable->table == NULL) {
        free(newtable);
        return NULL;
    }
    for (int i = 0; i < (int)(newtable->size); i++)
        newtable->table[i] = NULL;
    return newtable;
}


int Search(hashtable* table, int value) {
    node* seachnode = table->table[abs(value) % table->size];
    while (seachnode) {
        if (seachnode->value == value)
            return 1;
        seachnode = seachnode->next;
    }
    return 0;
}

void Add(hashtable* table, int value) {
    if (Search(table, value))
        return;
    node** newnode = &table->table[abs(value) % table->size];
    node** next = newnode;
    if (!*next) {
        if (!CreateNode(next))
            return;
        (*next)->value = value;
    }
    else {
        while (*next) {
            newnode = next;
            next = &(*next)->next;
        }
        if (!CreateNode(next))
            return;

        (*newnode)->next = *next;
        (*next)->value = value;
        
    }

}

void Remove(hashtable* table, int value) {
    node* newnode = table->table[abs(value) % table->size];
    node* previousnode = newnode;

    if (!Search(table, value))
        return;

    if (newnode->value == value) {
        table->table[abs(value) % table->size] = newnode->next;
        free(newnode);
    }
    else {
        while (newnode != NULL) {
            if (newnode->value == value) {
                previousnode->next = newnode->next;
                free(newnode);
                return;
            }
            previousnode = newnode;
            newnode = newnode->next;
        }
    }
}

void DeleteAll(hashtable* table) {
    if (!table)
        return;
    for (int i = 0; i < (int)(table->size); i++) {
        node* newnode = table->table[i];
        while (newnode) {
            node* dnode = newnode;
            newnode = newnode->next;
            free(dnode);
        }
    }
    free(table->table);
    free(table);
}


int main() {
    hashtable* table = CreateTable(100000);
    char* var = (char*)malloc(12 * sizeof(char));
    int value;
    if (!var)
        return 0;
    while (fgets(var, 12, stdin)) {
        value = strtol(var + 2, NULL, 10);
        if (var[0] == 'a')
            Add(table, value);
        else if (var[0] == 'r') {
            Remove(table, value);
            
        }
        else if (var[0] == 'f') {
            if (Search(table, value))
                printf("yes\n");
            else
                printf("no\n");
        }
    }
    DeleteAll(table);
    free(var);
    return 0;
}