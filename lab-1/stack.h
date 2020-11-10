#pragma once

typedef double type_t;

typedef struct {
    type_t* data;
    int last;
    int data_size;
} stack_t;

typedef struct stackList_t {
    type_t value;
    struct stackList_t* next;
}stackList_t;

stack_t* CreateStack(int size);

type_t Peek(stack_t* stack);

void Push(stack_t* stack, type_t a);

type_t Pop(stack_t* stack);

void RemoveStack(stack_t* stack);

void PushList(stackList_t** head, type_t value);

type_t PopList(stackList_t** head);

type_t PeekList(stackList_t* head);