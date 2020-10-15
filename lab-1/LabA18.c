#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Структура элемента списка.
typedef struct LNode
{
    // Указатель на ASCIIZ строку.
    char* data;
    // Указатель на следующий элемент списка.
    struct LNode* next;
} LNode;

// Добавить элемент в список.
void push(LNode** head, char* data)
{
    LNode* tmp;

    if (tmp = (LNode*)malloc(sizeof(LNode)))
    {
        tmp->data = data;
        tmp->next = (*head);
    }

    (*head) = tmp;
}

// Очистить список.
LNode* freeList(LNode* head)
{
    LNode* curr = head->next;

    while (curr)
    {
        LNode* tmp = curr;
        curr = curr->next;
        free(tmp->data);
        free(tmp);
    }

    free(head->data);
    head->next = NULL;

    return head;
}


// Сортировка списка методом вставок. Функция возвращает указатель на голову отсортированного списка.
LNode* sort(LNode* head)
{
    LNode* a;
    LNode* b;
    LNode* c;
    LNode* res = NULL;

    // Пока не пуст список.
    while (head != NULL)
    {
        a = head; head = head->next;

        // Поиск места вставки.
        for (b = res, c = NULL; b != NULL && strcmp(a->data, b->data) > 0; c = b, b = b->next);

        // Включение перед первым.
        if (c == NULL)
        {
            a->next = res;
            res = a;
        }
        // Включение после предыдущего.
        else
        {
            a->next = b;
            c->next = a;
        }
    }

    return res;
}



// Вывод элементов списка.
void printList(const LNode* head)
{
    if (head == NULL)
        return;

    while (head->next)
    {
        printf("%s -> ", head->data);
        head = head->next;
    }

    printf("%s", head->data);

    printf("\n");
}


int main(int argc, char* argv[])
{
    LNode* head = NULL;

    push(&head, "abbbbcd");
    push(&head, "bcb");
    push(&head, "bnbb");
    push(&head, "ggfds");
    push(&head, "ggsd");
    push(&head, "ccaa");

    puts("The Initial List:");
    printList(head);

    head = sort(head);
    puts("The Sorted List:");
    printList(head);

    getch();

    return 0;
}
