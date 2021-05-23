#include"Hash.h"
#pragma warning(disable:4996)

int main() {

    Hash_t* table;
    table = Create(SIZE);
    char key[100];
    char command;
    char symbol;

    while (1) {
        command = getchar();
        if (command == EOF)
            break;
        while (command == '\0' || command == '\n' || isspace(command) != 0)
            symbol = getchar();
        scanf("%s", &key);
        switch (command) {
        case('a'):
            Insert(table, key, SIZE);
            break;
        case('r'):
            Delete(table, key, SIZE);
            break;
        case('f'):
            if (Find(table, key, SIZE) == SUCCESS)
                puts("yes");
            else
                puts("no");
            break;
        default:
            break;
        }
        symbol = getchar();
    }
    Free(table, SIZE);
    return 0;
}