#pragma once
#define TABLE_SIZE 67
#define STR_SIZE 100 

typedef struct list {
    char str[STR_SIZE];
    int count;
    struct list* next;
} list;

list* (hash[TABLE_SIZE]);

int Hash(char* str);
void Addelem(char* str);
void Deleteelem(char* str);
int Findelem(char* str);
