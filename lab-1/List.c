#include<stdio.h>
#include<stdlib.h>
#include"List.h"

StackList_t* CreateStackList() {
    StackList_t* stack = (StackList_t*)malloc(sizeof(StackList_t));

    if (stack == NULL) {
        return NULL;
    }

    if (stack) {
        stack->next = NULL;
    }
    return stack;
}

Bool_t PushStackList(StackList_t** head, int value) {
    StackList_t* tmp = malloc(sizeof(StackList_t));
    if (*head == NULL)
        return FAILED;
    if (tmp == NULL) 
        return FAILED;
    
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
    return SUCCESS;
}

int PopStackList(StackList_t** head) {
    StackList_t* out;
    int value;
    if (*head == NULL)
        return NULL;
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

void DestroyStackList(StackList_t** head) {
    StackList_t* tmp;
    if (*head == NULL) {
        free(*head);
        return;
    }
    while (*head != NULL) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

StackArray_t* CreateStackArray() {
    StackArray_t* stack = (StackArray_t*)malloc(sizeof(StackArray_t));
    stack->top = 0;
    stack->size = INIT_SIZE;
    stack->value = (int*)malloc(sizeof(int) * INIT_SIZE);
    if (stack->value == NULL)
        return NULL;
    return stack;
}

Bool_t PushStackArray(StackArray_t* stack, int data) {
    if (stack == NULL)
        return FAILED;

    if (stack->top == stack->size)
    {
        int* newData = (int*)malloc(sizeof(int) * (stack->size + INIT_SIZE));
        if (newData == NULL) 
            return FAILED;
        
        else {
            for (int i = 0; i != stack->top; ++i)
                newData[i] = stack->value[i];
            stack->size += INIT_SIZE;
            free(stack->value);
            stack->value = newData;
        }
    }

    stack->value[stack->top] = data;
    stack->top++;
    return SUCCESS;
}

int PopStackArray(StackArray_t* stack) {
    if (stack->top == 0) 
        return NULL; 

    return stack->value[(stack->top--) - 1];
}

void DestroyStackArray(StackArray_t* stack) {
    free(stack->value);
    free(stack);
}