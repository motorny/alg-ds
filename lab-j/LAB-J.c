#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define HASH_SIZE 64
#define MAX_STR_SIZE 256 

typedef struct list{
    char str[MAX_STR_SIZE];
    int count;
    struct list *next;
} list;

list* (hash[HASH_SIZE]);

int hashFunction(char *str){
    if(str == NULL) return 0;
    int length = strlen(str);
    int sum = 0;
    for (int i = 0; i < length; i++)
        sum += (int)str[i];
    return sum % HASH_SIZE;
}

void addStr(char *str){
    if(!str) return;
    int index = hashFunction(str);
    int is = 0;
    
    if(hash[index] == NULL){
        list* iNewList = (list *)malloc(sizeof(list));
        if(!iNewList) {
            return;
        }
        strcpy(iNewList->str, str);
        iNewList->count = 1;
        iNewList->next = NULL;
        hash[index] = iNewList;
    }
    else
    {
        is = strcmp(str, hash[index]->str);
        if( is <= 0){
            if (is = 0)
            {
                hash[index]->count++;
            }
            else
            {
                list* iNewList = (list *)malloc(sizeof(list));
                if(!iNewList) {
                    return;
                }
                strcpy(iNewList->str, str);
                iNewList->next = hash[index];
                iNewList->count = 1;
                hash[index] = iNewList;
            }
        }else{
            list *iList = hash[index];
            while (iList->next != NULL && strcmp(str, iList->next->str) >= 0)
            {
                iList = iList->next;
            }

            if(strcmp(str, iList->next->str) == 0){
                iList->next->count++;
            }
            else
            {
                list* iNewList = (list *)malloc(sizeof(list));
                if(!iNewList) {
                    return;
                }
                strcpy(iNewList->str, str);
                iNewList->next = iList->next;
                iNewList->count = 1;
                iList->next = iNewList;
            }
        }
    }   
}

void rmStr(char *str){
    if(!str) return;
    int index = hashFunction(str);
    int is = 0;

    if(hash[index] != NULL){
        if(strcmp(str, hash[index]->str) == 0){
            if(hash[index]->count == 1)
            {
                list *tmp = hash[index];
                hash[index] = tmp->next;
                //free(tmp->str);
                free(tmp);
            }
            else
            {
                hash[index]->count--;
            }
        }
        else
        {
            list *iList = hash[index];
            while (iList->next != NULL)
            {
                is = strcmp(str, iList->next->str);
                if(is <= 0){
                    if(is < 0) break;
                    if(iList->next->count > 1)
                    {
                        list *tmp = iList->next;
                        iList->next = tmp->next;
                        free(tmp->str);
                        free(tmp);
                    }
                    else
                    {
                        iList->next->count--;
                    }
                    break;
                }
                iList = iList->next;
            }
        }
    }
}

int findStr(char *str){
    if(!str) return 0;
    int index = hashFunction(str);
    int is = 0;
    if(hash[index] != NULL){
        list *iList = hash[index];
        while (iList != NULL)
        {
            is = strcmp(str, iList->str);
            if(is <= 0) 
                if(is < 0) return 0;
                else return 1;
            iList = iList->next;
        }
    }
    return 0;
}

#ifndef GTEST
int main(void){
    char ch = getchar();
    char str[MAX_STR_SIZE];


    while ( ch != EOF ){
        scanf("%s", str);
        switch ( ch ) {
        case 'a':
            // add
            addStr(str);
            break;
        case 'r':
            // remove
            rmStr(str);
            break;
        case 'f':
            if ( findStr(str) )
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            return 0;
        }

        ch = getchar();
        if ( ch == '\r' )
            ch = getchar();
        if ( ch == '\n' )
            ch = getchar();
    }

    return 0;
}
#endif // !GTEST