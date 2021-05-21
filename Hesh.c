#include <stdlib.h>
#include <string.h>
#include "Hesh.h"

#pragma warning(disable: 4996)


hash_table_t* HashInit(int hashTSize) {

    if (hashTSize <= 0)
        return NULL;

    hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));

    if (!table)
        return NULL;

    table->size = hashTSize;
    table->table = (hash_elem_t*)malloc(sizeof(hash_elem_t) * hashTSize);

    if (!table->table) {
        free(table);
        return NULL;
    }

    for (int i = 0; i < hashTSize; i++)
        table->table[i].status = FREE;

    return table;

}

static unsigned HashFunc(char* str, int size) {

    int sum = 0;

    for (int i = 0; str[i] != 0; i++)
        sum += str[i];

    return sum % size;

}

int HashAdd(hash_table_t* hash, char elem[]) {

    if (!hash)
        return FAIL;

    int pos0 = HashFunc(elem, hash->size), curPos = pos0;
    int pos = -1;
    int i = 0;

    do {
        if (hash->table[curPos].status == FREE) {
            if (pos == -1)
                pos = curPos;
            break;
        }
        else
            if (hash->table[curPos].status == DELETED) {
                if (pos == -1)
                    pos = curPos;
            }
            else if (strcmp(hash->table[curPos].str, elem) == 0)
                return ALREADY_EXISTS;

        i++;
        curPos = (pos0 + i * 1) % hash->size;
    } while (curPos != pos0);

    if (pos != -1) {
        hash->table[pos].str = (char*)malloc(sizeof(char) * (strlen(elem) + 1));

        if (!hash->table[pos].str)
            return FAIL;

        strcpy(hash->table[pos].str, elem);
        hash->table[pos].status = FULL;

        return SUCCESS;
    }

    return FAIL;

}

hash_elem_t* HashFind(hash_table_t* hash, char elem[]) {

    if (!hash)
        return NULL;

    int pos0 = HashFunc(elem, hash->size), curPos = pos0;
    int i = 0;

    do {
        if (hash->table[curPos].status == FREE)
            return NULL;

        if (hash->table[curPos].status == FULL && strcmp(hash->table[curPos].str, elem) == 0)
            return &hash->table[curPos];

        i++;
        curPos = (pos0 + i * 1) % hash->size;
    } while (curPos != pos0);

    return NULL;

}


void Clear(hash_table_t* hash) {
    if (!hash)
        return;

    for (int i = 0; i < hash->size; i++)
        if (hash->table[i].status == FULL)
            free(hash->table[i].str);
    free(hash->table);
    free(hash);
}

int HashDelete(hash_table_t* hash, char elem[]) {

    if (!hash)
        return FAIL;

    int pos0 = HashFunc(elem, hash->size), curPos = pos0;
    int i = 0;

    do {
        if (hash->table[curPos].status == FREE)
            return FAIL;

        if (hash->table[curPos].status == FULL && strcmp(hash->table[curPos].str, elem) == 0) {
            unsigned pos1 = (pos0 + (i + 1) * 1) % hash->size;

            free(hash->table[curPos].str);
            hash->table[curPos].status = DELETED;
            if (hash->table[pos1].status == FREE) {
                while (hash->table[curPos].status == DELETED) {
                    hash->table[curPos].status = FREE;
                    i--;
                    if (i >= 0) {
                        curPos = (pos0 + i * 1) % hash->size;
                        if (curPos == pos0)
                            break;
                    }
                    else
                        break;
                }
            }

            return SUCCESS;
        }

        i++;
        curPos = (pos0 + i * 1) % hash->size;
    } while (curPos != pos0);

    return FAIL;

}

int main(void) {


    return 0;
}