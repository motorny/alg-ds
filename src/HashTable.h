//
// Created by ikuzin on 29.04.2021.
//

#ifndef LH_HASHTABLE_H
#define LH_HASHTABLE_H

enum binType {
    f = 1,
    t = 0
};
typedef struct HashItem {
    char *string;
    binType deleted;
} HASH_ITEM;

typedef struct HashTable {
    unsigned int size;
    HASH_ITEM *list[];
} HASH_TABLE;

void hashTableAdd(HASH_TABLE *, char *);

void hashTableDelete(HASH_TABLE *, const char *);

HASH_ITEM *hashTableFind(HASH_TABLE *, const char *);

void hashTableClear(HASH_TABLE *);

//-------hash-------//

int getH1(unsigned int, unsigned int);

int getH2(unsigned int, unsigned int);

unsigned int hashcode(char const *const);


#endif //LH_HASHTABLE_H
