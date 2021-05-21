#include <stdio.h>
#include <string.h>

#include "hash_table.h"

int main() {

    ht_t* ht = NULL;
    ht = createHash(ht, INIT_SIZE);
    int c = getchar();
    char str[100];

    while (c != EOF){
        scanf("%s", str);
//        printf("%s\n", str);
        switch(c){
            case 'a':
                ht = insertHash(ht, str);
                break;
            case 'f':
                printf(findHash(ht, str) == NULL ? "no\n" : "yes\n");
                break;
            case 'r':
                ht = deleteHash(ht, str);
                break;
            default:
                freeHash(ht);
                return 0;
        }

        if((c = getchar()) == '\n')
            c = getchar();
    }
    freeHash(ht);
    return 0;
}