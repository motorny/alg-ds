#include"Hashtable.h"

Hashtable* create_hash() 
{
    Hashtable* myHash;
    myHash = (Hashtable*)malloc(sizeof(Hashtable) * SIZE);
    if (myHash == NULL)
        return NULL;

    for (int i = 0; i < SIZE; i++)
        myHash[i].status = DELETED;

    return myHash;

}

static int hash(char* str)
{
    int index = 0;
    for (int i = 0; str[i] != 0; i++)
        index += str[i];

    return index % SIZE;

}

int add(Hashtable* myHash, char* str) {
    int pos0 = hash(str);
    int pos = pos0, respos = -1, i = 0;
    do {
        if (myHash[pos].status == NOTFREE && strcmp(myHash[pos].str, str) == 0)
            return FALSE;

        if (myHash[pos].status == FREE || myHash[pos].status == DELETED) {
            respos = pos;
            break;
        }
        i++;
        pos = (pos0 + i * 1) % SIZE;
    } while (pos != pos0);
    if (respos != -1) {
        myHash[respos].str = malloc((strlen(str) + 1) * sizeof(char));
        strcpy(myHash[respos].str, str);
        myHash[respos].status = NOTFREE;
        return TRUE;
    }
    return FALSE;
}

int find(Hashtable* myHash, char* str) {
    int pos0 = hash(str), pos = pos0, i = 0;
    do {
        if (myHash[pos].status == FREE) {
            return FALSE;
        }
        if (myHash[pos].status == NOTFREE && strcmp(myHash[pos].str, str) == 0)
            return TRUE;
        i++;
        pos = (pos0 + i * 1) % SIZE;
    } while (pos != pos0);
    return FALSE;
}

int Delete(Hashtable* myHash, char* str) {
    int p0 = hash(str), pos = p0, i = 0;
    do {
        if (myHash[pos].status == FREE) {
            return FALSE;
        }
        if (myHash[pos].status == NOTFREE && strcmp(myHash[pos].str, str) == 0) {
            free(myHash[pos].str);
            myHash[pos].status = DELETED;
            return TRUE;
        }
        i++;
        pos = (p0 + i * 1) % SIZE;
    } while (pos != p0);
    return FALSE;
}

void hashDestroy(Hashtable* myHash) {

    for (int i = 0; i < SIZE; i++)
        if (myHash[i].status == NOTFREE)
            free(myHash[i].str);
    free(myHash);

} 