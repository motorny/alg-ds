#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable:4996)
extern LIST* list;

int main()
{
    FILE* fp = fopen("test.txt", "r");
    //LIST* parent=(LIST*)malloc(sizeof(LIST));
    file_read(fp);
    printTree(list, "root", 0);
    return 0;
}