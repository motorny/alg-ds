#pragma once
#include <stdio.h>
#include <stdlib.h>


#define MAX_LEVEL 16

typedef struct Node {
    int key;
    int value;
    struct Node* forward[1];
}Node;


typedef struct SkipList {
    int level;
    Node* header;
    Node* tail;
}SkipList;


int RandomLevel();
void PrintSkipList(SkipList* sl);
Node* Create(int level, int key, int value);
SkipList* CreateSkipList();
int Insert(SkipList* sl, int key, int value);
int Delete(SkipList* sl, int key);
int Search(SkipList* sl, int key);

