#include <stdio.h>
#include <stdlib.h>
#include "Skip_List.h"


int RandomLevel() {
    int level = 0;
    do {
        level++;
    } while (level < MAX_LEVEL && rand() < RAND_MAX / 2);
    return level;
}

void PrintSkipList(SkipList* sl) {
    Node* p;
    int k = sl->level;
    
    for (int i = k; i >= 0; i--) {
        p = sl->header->forward[i];
        printf("level[%d]: ", i);
        while (p->forward[i] != sl->tail) {
            printf("(%d,%d) -> ", p->key, p->value);
            p = p->forward[i];
        }
        printf("(%d,%d)\n", p->key, p->value);
    }
    printf("\n");
}

Node* Create(int level, int key, int value) {
    int size = sizeof(Node) + level * sizeof(Node*);
    Node* node = (Node*)malloc(size);
    if (node == NULL) {
        return NULL;
    }
    node->key = key;
    node->value = value;
    return node;
}

SkipList* CreateSkipList() {
    SkipList* sl = (SkipList*)malloc(sizeof(SkipList));
    if (sl == NULL) {
        return NULL;
    }
    sl->level = 0;
    sl->header = Create(MAX_LEVEL, 0, 0);
    sl->tail = Create(0,  MAX_KEY, 0);
    for (int i = 0; i <= MAX_LEVEL; i++) {
        sl->header->forward[i] = sl->tail;
    }
    return sl;
}

int Insert(SkipList* sl, int key, int value) {
    Node* update[MAX_LEVEL];
    Node* p,* q;
    p = sl->header;
    int k = sl->level;
    for (int i = k; i >= 0; i--) {
        while (p->forward[i]->key < key) {
            p = p->forward[i];
        }
        update[i] = p;
    }
    q = p->forward[0];
    if (q->key == key) {
        return  NOT_DONE;
    }

    k = RandomLevel();
    //printf("NewLevel: %d, CurLevel: %d\n", k, sl->level);
    if (k > sl->level) {
        for (int i = sl->level + 1; i <= k; i++)
            update[i] = sl->header;
        sl->level = k;
    }

    q = Create(k, key, value);
    for (int i = 0; i <= k; i++) {
        q->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = q;
    }
    
    return  DONE;
}

int Delete(SkipList* sl, int key) {
    Node* update[MAX_LEVEL];
    Node* p,* q;
    p = sl->header;
    int k = sl->level;
    for (int i = k; i >= 0; i--) {
        while (p->forward[i]->key < key) {
            p = p->forward[i];
        }
        update[i] = p;
    }
    q = p->forward[0];
    if (q && q->key == key) {
        for (int i = 0; i <= sl->level; i++) {
            if (update[i]->forward[i] != q)
                break;
            update[i]->forward[i] = q->forward[i];
        }
        free(q);
        for (int i = sl->level; i > 0; i--) {
            if (sl->header->forward[i] == sl->tail) {
                sl->level--;
            }
        }
        return  DONE;
    }
    else {
        return  NOT_DONE;
    }
}

int Search(SkipList* sl, int key) {
    Node* p,* q;
    p = sl->header;
    int k = sl->level;
    for (int i = k; i >= 0; i--) {
        while ((q = p->forward[i]) && q->key <= key) {
            if (q->key == key)
                return q->value;
            p = q;
        }
    }
    return NULL;
}

