#pragma once
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define ERROR -1
typedef struct elem_t {
  struct elem_t* next;
  int numElements;
  int arr[SIZE];
}elem_t;

elem_t* CreateHead();
elem_t* CreateNewNode(elem_t* prev);
elem_t* GetCurrentNode(elem_t* head);
void AddElement(elem_t* head, int elem);
void DeleteElement(elem_t* head, int num);
int GetElementNum(elem_t* head, int num);
int GetNumKey(elem_t* head, int key);
int GetNextElementKey(elem_t* head, int key);
int GetCountElements(elem_t* head);