#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"treap.h"

#define ERRORNULL NULL

void  PrintTree(Treap* T);
Treap* GetNodeByValue(Treap* root, int value);
void GetTreeFromConsole(Treap** root);
void DestroyTree(Treap** root);