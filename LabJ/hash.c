#include"hash.h"

hashTable_t* CreateHashT() {

    hashTable_t* hashTable;

    hashTable = (hashTable_t*)malloc(sizeof(hashTable_t) * SIZE);
    if (hashTable == NULL)
        return NULL;

    for (int i = 0; i < SIZE; i++)
        hashTable[i].status = DELETED;

    return hashTable;

}

static int Hash(char* str) {

    int index = 0;

    for (int i = 0; str[i] != 0; i++)
        index += str[i];

    return index % SIZE;

}

int Add(hashTable_t* hashTable, char* str) {
    int pos0 = Hash(str);
    int pos = pos0, respos = -1, i = 0;
    do {
        if (hashTable[pos].status == NOTFREE && strcmp(hashTable[pos].str, str) == 0)
            return FALSE;

        if (hashTable[pos].status == FREE || hashTable[pos].status == DELETED) {
            respos = pos;
            break;
        }
        i++;
        pos = (pos0 + i * 1) % SIZE;
    } while (pos != pos0);
    if (respos != -1) {
        hashTable[respos].str = malloc((strlen(str) + 1) * sizeof(char));
        strcpy(hashTable[respos].str, str);
        hashTable[respos].status = NOTFREE;
        return TRUE;
    }
    return FALSE;
}

int Find(hashTable_t* hashT, char* str) {
    int pos0 = Hash(str), pos = pos0, i = 0;
    do {
        if (hashT[pos].status == FREE) {
            return FALSE;
        }
        if (hashT[pos].status == NOTFREE && strcmp(hashT[pos].str, str) == 0)
            return TRUE;
        i++;
        pos = (pos0 + i * 1) % SIZE;
    } while (pos != pos0);
    return FALSE;
}

int Delete(hashTable_t* hashT, char* str) {
    int p0 = Hash(str), pos = p0, i = 0;
    do {
        if (hashT[pos].status == FREE) {
            return FALSE;
        }
        if (hashT[pos].status == NOTFREE && strcmp(hashT[pos].str, str) == 0) {
            free(hashT[pos].str);
            hashT[pos].status = DELETED;
            return TRUE;
        }
        i++;
        pos = (p0 + i * 1) % SIZE;
    } while (pos != p0);
    return FALSE;
}

void hashDestroy(hashTable_t* hashTable) {

    for (int i = 0; i < SIZE; i++)
        if (hashTable[i].status == NOTFREE)
            free(hashTable[i].str);
    free(hashTable);

}