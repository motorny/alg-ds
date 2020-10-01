#include "stack.h"
#include <stdlib.h>

int CheckNullStack(stack_t* stack) {
    return stack == NULL;
}

stack_t* CreateStack(int size) {
    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    if (CheckNullStack(stack)) {
        return NULL;
    }
    stack->data_size = size;
    stack->last = 0;
    stack->data = (type_t*)malloc(sizeof(type_t) * stack->data_size);
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }
    return stack;
}

type_t Peek(stack_t* stack) {
    return stack->data[stack->last - 1];
}

int ReallocAndCheckNull(stack_t *stack) {
    type_t* buffer = NULL;
    if (stack->last < stack->data_size) {
        stack->data_size++;
        buffer = (type_t*)realloc(stack->data, stack->data_size * sizeof(type_t));
        if (buffer == NULL) {
            return 0;
        }
        stack->data = buffer;
        return 1;
    }
    return 1;
}

void Push(stack_t* stack, type_t value) {
    if (ReallocAndCheckNull(stack)) {
        stack->data[stack->last] = value;
        stack->last++;
    }
}

type_t Pop(stack_t* stack) {
    type_t a = 0;
    if (!CheckNullStack(stack) && stack->last > 0) {
        stack->last--;
        a = stack->data[stack->last];
        return a;
    }
    return a;
}

void RemoveStack(stack_t* stack) {
    if (!CheckNullStack(stack)) {
        free(stack->data);
        free(stack);
    }
}

int CheckNullHead(stackList_t* head) {
    return head == NULL;
}

void PushList(stackList_t **head ,type_t value) {
    stackList_t* list = (stackList_t*)malloc(sizeof(stackList_t));
    if (list == NULL || CheckNullHead(*head))
        return;
    list->next = (*head);
    list->value = value;
    (*head) = list;
}

type_t PopList(stackList_t** head) {
    type_t value;
    stackList_t* out;
    if (CheckNullHead(*head))
        return 0;
    value = (*head)->value;
    out = (*head);
    (*head) = (*head)->next;
    free(out);
    return value;
}

type_t PeekList(stackList_t *head) {
    return CheckNullHead(head) ? 0 : head->value;
}

type_t IsEmptyList(stackList_t* head) {
    return head ? 1 : 0;
}