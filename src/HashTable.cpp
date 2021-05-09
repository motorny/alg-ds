//
// Created by ikuzin on 29.04.2021.
//

#include <cstring>
#include <cmath>
#include "HashTable.h"

void hashTableAdd(HASH_TABLE *htable, char *string) {
    unsigned int hstr = hashcode(string);
    int h1 = getH1(hstr, htable->size);
    int h2 = getH2(hstr, htable->size);

    HASH_ITEM *item;
    int hash, i = -1;

    do {
        ++i;
        hash = (int) ((h1 + i * h2) % htable->size);
        item = htable->list[hash];
        if (item == nullptr) {
            htable->list[hash] = (HASH_ITEM *) malloc(sizeof(HASH_ITEM));
            htable->list[hash]->string = string;
            htable->list[hash]->deleted = f;
        } else if (item->deleted == t)
            item = nullptr;
    } while (!item);
};

void hashTableDelete(HASH_TABLE *htable, const char *string) {
    unsigned int hstr = hashcode(string);
    int h1 = getH1(hstr, htable->size);
    int h2 = getH2(hstr, htable->size);

    HASH_ITEM *item = nullptr;
    int hash, i = 0;

    while (!item) {
        hash = (int) ((h1 + i * h2) % htable->size);
        item = htable->list[hash];
        if (item && item->string == string) {
            item->deleted = t;
            return;
        } else {
            ++i;
        }
    }
};

HASH_ITEM *hashTableFind(HASH_TABLE *htable, const char *string) {
    unsigned int hstr = hashcode(string);
    int h1 = getH1(hstr, htable->size);
    int h2 = getH2(hstr, htable->size);

    HASH_ITEM *item = nullptr;
    int hash, i = 0;

    while (!item) {
        hash = (int) ((h1 + i * h2) % htable->size);
        item = htable->list[hash];
        if (item && item->string == string) {
            return item;
        } else {
            ++i;
        }
    }
    return nullptr;
};

void hashTableClear(HASH_TABLE *htable) {
    for (int i = 0; i < htable->size; i++) {
        free(htable->list[i]);
    }
    free(htable);
};

int getH1(unsigned int hstr, unsigned int hsize) {
    return (int) (hstr % hsize);
};

int getH2(unsigned int hstr, unsigned int hsize) {
    return 1 + (int) (hstr % (hsize - 1));
};


unsigned hashcode(char const *const s) {
    long int mod = 1e6 + 7;
    unsigned int hash = 0;
    for (int i = 0; i < strlen(s); i++)
        hash = (hash + (s[i] * (unsigned int) pow(31, i) % mod)) % mod;
    return hash;
}
