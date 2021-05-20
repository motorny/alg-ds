#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#pragma warning (disable:4996)


int Hash(char* str) {
    if (!str)
        return 0;
    int len = strlen(str), summa = 0, i = 0;
    for (i = 0; i < len; i++)
        summa += (unsigned int)str[i];
    return summa % TABLE_SIZE;
}

void Addelem(char* str) {
    if (!str)
        return;
    int index = Hash(str), comparing = 0;

    if (hash[index] == NULL) {
        list* newelem = (list*)malloc(sizeof(list));
        if (!newelem) {
            return;
        }
        strcpy(newelem->str, str);
        newelem->count = 1;
        newelem->next = NULL;
        hash[index] = newelem;
    }
    else
    {
        comparing = strcmp(str, hash[index]->str);
        if (comparing == 0)
        {
            hash[index]->count++;
        }
        else if (comparing < 0)
        {
            list* newelem = (list*)malloc(sizeof(list));
            if (!newelem) {
                return;
            }
            strcpy(newelem->str, str);
            newelem->next = hash[index];
            newelem->count = 1;
            hash[index] = newelem;
        }
        else if (comparing > 0) {
            list* helplist = hash[index];
            while (helplist->next != NULL && strcmp(str, helplist->next->str) >= 0)
                helplist = helplist->next;

            if (strcmp(str, helplist->next->str) == 0)
                helplist->next->count++;
            else
            {
                list* newlist = (list*)malloc(sizeof(list));
                if (!newlist) {
                    return;
                }
                strcpy(newlist->str, str);
                newlist->next = helplist->next;
                newlist->count = 1;
                helplist->next = newlist;
            }
        }
    }
}

void Deleteelem(char* str) {
    if (!str)
        return;
    int index = Hash(str), comparing = 0;

    if (hash[index] != NULL) {
        comparing = strcmp(str, hash[index]->str);
        if (comparing == 0) {
            if (hash[index]->count == 1)
            {
                list* helplist = hash[index];
                hash[index] = helplist->next;
                free(helplist);
            }
            else
                hash[index]->count--;
        }
        else
        {
            list* helplist = hash[index];
            while (helplist->next)
            {
                comparing = strcmp(str, helplist->next->str);
                if (comparing < 0)
                    break;
                if (comparing == 0) {
                    if (helplist->next->count > 1)
                    {
                        list* buf = helplist->next;
                        helplist->next = buf->next;
                        free(buf->str);
                        free(buf);
                    }
                    else
                        helplist->next->count--;
                    break;
                }
                helplist = helplist->next;
            }
        }
    }
}

int Findelem(char* str) {
    if (!str)
        return 0;
    int index = Hash(str), comparing = 0;
    if (hash[index] != NULL) {
        list* helplist = hash[index];
        while (helplist != NULL)
        {
            comparing = strcmp(str, helplist->str);
            if (comparing <= 0)
                if (comparing < 0)
                    return 0;
                else
                    return 1;
            helplist = helplist->next;
        }
    }
    return 0;
}
