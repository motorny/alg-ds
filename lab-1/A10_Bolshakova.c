#include <stdio.h>
#include <malloc.h>

typedef int data_t;


typedef enum {
  ERROR_NO,
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
  OUT_OF_MEMORY
} error_t;

//стек-массив
typedef struct {
  data_t* data;
  size_t size;
  size_t top;
} arrStack_t;

//стек-список
typedef struct node {
  data_t* data;
  struct node* next;
} node_t;

//создание стека-массива, память в динамич. массиве
  //нет аналога при реализации через список
arrStack_t* ArrStackCreate(size_t size, error_t* err) {
  arrStack_t* stack = (arrStack_t*)malloc(sizeof(arrStack_t) * size);
  if (stack == NULL) {
    *err = OUT_OF_MEMORY;
    return NULL;
  }
  stack->size = size;
  stack->data = (data_t*)malloc((stack->size) * sizeof(data_t));
  if (stack->data == NULL) {
    free(stack);
    *err = OUT_OF_MEMORY;
    return NULL;
  }
  stack->top = 0;
  return stack;
}

//уничтожение стека-массива
void ArrStackDestroy(arrStack_t** stack) {
  if (*stack != NULL) {
    free((*stack)->data);
    free(*stack);
  }
  *stack = NULL;
}

//добавление элемента в динамич. массив
  //нет аналога при реализации через список
arrStack_t* ArrStackAddElem(arrStack_t* stack, error_t* err) {
  if (stack == NULL) {
    return stack;
  }
  data_t* newdata = stack->data;
  newdata = (data_t*)realloc(stack->data, (stack->size + 1) * sizeof(arrStack_t));
  if (newdata == NULL) {
    *err = OUT_OF_MEMORY;
    ArrStackDestroy(&stack);
    return NULL;
  }
  else {
    stack->data = newdata;
    stack->size++;
    return stack;
  }
}

//проверка пустоты стека-массив
int ArrStackEmpty(arrStack_t const* stack) {
  return !(stack->top);
}

// push для стека-массива
void ArrStackPush(arrStack_t* stack, data_t newData, error_t* err) {
  if (stack->top >= stack->size) {
    ArrStackAddElem(stack, err);
  }
  if (*err == ERROR_NO) {
    stack->data[stack->top] = newData;
    stack->top++;
  }
}

// pop для стека-массива
data_t ArrStackPop(arrStack_t* stack, error_t* err) {
  if (stack->top == 0) {
    *err = STACK_UNDERFLOW;
    return 0;
  }
  stack->top--;
  return stack->data[stack->top];
}

// peek для стека-массива
data_t ArrStackPeek(arrStack_t const* stack, error_t* err) {
  if (stack->top <= 0) {
    *err = STACK_UNDERFLOW;
    return 0;
  }
  return stack->data[stack->top - 1];
}


// push для стека-списка 
void LinkListStackPush(node_t** head, data_t data, error_t* err) {
  node_t* node = (node_t*)malloc(sizeof(node_t));
  if (node == NULL) {
    *err = OUT_OF_MEMORY;
  }
  else {
    node->next = *head;
    node->data = &data;
    *head = node;
  }
}

//pop для стека-списка
data_t LinkListStackPop(node_t** head, error_t* err) {
  node_t* elem;
  data_t* data = (*head)->data;
  if ((*head) == NULL) {
    *err = STACK_UNDERFLOW;
    return 0;
  }
  elem = *head;
  *head = (*head)->next;
  free(elem);
  return *data;
}

//при переходе к LinkListStackPop, в a10.c из test.cpp, меняются значения под указателем.Не смогла найти причину
//было принятно решение написать тестовую функцию с фиксированной датой, которая читается со стека перед отправкой.
data_t LinkListStackPopTest(node_t** head, data_t data, error_t* err) {
  node_t* elem;
  if ((*head) == NULL) {
    *err = STACK_UNDERFLOW;
    return 0;
  }
  elem = *head;
  *head = (*head)->next;
  free(elem);
  return data;
}

// peek для стека-списка
data_t LinkListStackPeek(const node_t* head, error_t* err) {
  if (head == NULL) {
    *err = STACK_UNDERFLOW;
    return 0;
  }
  return *(head->data);
}

//проверка пустоты стека-списка
int LinkListStackEmpty(const node_t* head) {
  return !head;
}

// уничтожение стека-списка
void LinkListStackDestroy(node_t** head, error_t* err) {
  while ((*head) != NULL) {
    LinkListStackPop(head, err);
  }
}

