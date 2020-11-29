#pragma once
#ifndef ULL_H_INCLUDED
#define ULL_H_INCLUDED
#pragma once
#define SIZE 4
#define ERROR -1
struct LinkedBlock {
	struct LinkedBlock* nextBlock;
	int arrSize;
	int arr[SIZE];
};

typedef struct LinkedBlock ull_t;

ull_t* CreateHead();
ull_t* CreateNewNode(ull_t* prev);
ull_t* GetCurrentNode(ull_t* head);
void AddElement(ull_t* head, int elem);
void DeleteElement(ull_t* head, int num);
int GetElementNum(ull_t* head, int num);
int GetNumKey(ull_t* head, int key);
int GetNextElementKey(ull_t* head, int key);
int GetCountElements(ull_t* head);

#endif//ULL_H_INCLUDED