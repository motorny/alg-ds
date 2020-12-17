#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct LIST {
    char data[100];
    struct LIST* left;
    struct LIST* right;
    struct LIST* parent;
} LIST;


LIST* add_block(LIST* parent, char data[]);

void insert_in_tree(char data[]);

LIST* find_min(LIST* current);

LIST* find_max(LIST* current);

LIST* find_data(char data[], LIST* current);

void delete_block(LIST* current);

void deleteValue(LIST* root, char value[]);

void printTree(LIST* root, const char* dir, int level);

void file_read(FILE* fp);

