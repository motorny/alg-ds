#include <stdio.h>
#include "hashTable.h"
#pragma warning(disable:4996)

enum mode_t {
    ADD,
    DELETE,
    FIND,
    PRINT,
    ERROR = -1
};

int ReadAction(FILE* fp, data_t keys) {
    char c, n;
    int check;
     check = fscanf(fp, "%c", &c);
    if (check == -1)
        return ERROR;

    fscanf(fp, "%s", keys);
    fscanf(fp, "%c", &n); //it's for \n

    switch (c) {
    case 'a':
        return ADD;
    case 'r':
        return DELETE;
    case 'f':
        return FIND;
    case 'p':
        return PRINT;
    default:
        return ERROR;
    }
}

int main(void) {
    int mode = 0;
    data_t num[100];

    hash_t* table = CreateTable(TABLE_SIZE);
    if (table == NULL)
        return -1;

    mode = ReadAction(stdin, num);
    if (mode == ERROR)
        return -1;


    do {
        switch (mode) {
        case ADD:
            Add(table, num);
            break;
        case DELETE:
            Del(table, num);
            break;
        case FIND:
            if (Find(table, num) >= 0)
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            break;
        }
        mode = ReadAction(stdin, num);

    } while (mode != ERROR);

    Destroy(table);

    return 0;
}