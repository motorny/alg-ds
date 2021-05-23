#include"HashTable.h"

hashTable_t* CreateHashTable() {
    hashTable_t* table;
    table = (hashTable_t*)malloc(sizeof(hashTable_t) * TABLE_SIZE);
    if (!table)
        return NULL;

    int i = 0;
    for (i = 0; i < TABLE_SIZE; i++)
        table[i].status = DELETED;

    return table;
}

int HashFunc(char* str) {
    int key = 0, i = 0;
    for (i = 0; str[i] != 0; i++)
        key += str[i];

    return key % TABLE_SIZE;
}

int AddStr(hashTable_t* hashTable, char* str) {
    int pos0 = HashFunc(str);
    int pos = pos0, respos = -1, i = 0;
    do {
        if (hashTable[pos].status == NOTFREE && strcmp(hashTable[pos].str, str) == 0)
            return NOT_FINISHED;

        if (hashTable[pos].status == FREE || hashTable[pos].status == DELETED) {
            respos = pos;
            break;
        }
        i++;
        pos = (pos0 + i * 1) % TABLE_SIZE;
    } while (pos != pos0);

    if (respos != -1) {
        hashTable[respos].str = malloc((strlen(str) + 1) * sizeof(char));
        strcpy(hashTable[respos].str, str);
        hashTable[respos].status = NOTFREE;
        return FINISHED;
    }

    return NOT_FINISHED;
}

int FindStr(hashTable_t* hashT, char* str) {
    int pos0 = HashFunc(str), pos = pos0, i = 0;
    do {
        if (hashT[pos].status == FREE)
            return NOT_FINISHED;

        if (hashT[pos].status == NOTFREE && strcmp(hashT[pos].str, str) == 0)
            return FINISHED;

        i++;
        pos = (pos0 + i * 1) % TABLE_SIZE;
    } while (pos != pos0);

    return NOT_FINISHED;
}

int DeleteStr(hashTable_t* hashT, char* str) {
    int pos0 = HashFunc(str), pos = pos0, i = 0;
    do {
        if (hashT[pos].status == FREE)
            return NOT_FINISHED;

        if (hashT[pos].status == NOTFREE && strcmp(hashT[pos].str, str) == 0) {
            free(hashT[pos].str);
            hashT[pos].status = DELETED;
            return FINISHED;
        }
        i++;
        pos = (pos0 + i * 1) % TABLE_SIZE;
    } while (pos != pos0);

    return NOT_FINISHED;
}

void DestroyTable(hashTable_t* table) {
    if (!table)
        return;

    int i = 0;
    for (i = 0; i < TABLE_SIZE; i++)
        if (table[i].status == NOTFREE)
            free(table[i].str);
    free(table);
    return;
}