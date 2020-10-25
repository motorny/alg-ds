#include "pch.h"


//Off errors on the unsafe use of "old" C features: Отключение ошибок об использовании небезопасных "старых" функций Си.
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>



// The structure of the list item: Структура элемента списка.
typedef struct LNode
{
    // Pointer to an ASCIIZ string: Указатель на ASCIIZ строку.
    char* data;
    // Pointer to the next item in the list: Указатель на следующий элемент списка.
    struct LNode* next;
} LNode;


//Add an item to the list: Добавить элемент в список.
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


// Sorting the list using the insert method. The function returns a pointer to the head of the sorted list: Сортировка списка методом вставок. Функция возвращает указатель на голову отсортированного списка.
LNode* sort(LNode* head)
{
    LNode* a;
    LNode* b;
    LNode* c;
    LNode* res = NULL;

    // Until the list is empty: Пока не пуст список.
    while (head != NULL)
    {
        a = head; head = head->next;

        //Search for an insertion point: Поиск места вставки.
        for (b = res, c = NULL; b != NULL && strcmp(a->data, b->data) > 0; c = b, b = b->next);

        // Enabling before the first one: Включение перед первым.
        if (c == NULL)
        {
            a->next = res;
            res = a;
        }
        //Enabling after the previous one: Включение после предыдущего.
        else
        {
            a->next = b;
            c->next = a;
        }
    }

    return res;
}


// Test for adding an element to a list 0: adding an "empty" element (a pointer to a NULL string)
//Тест добавления элемента в список 0: добавляем "пустой" элемент (указатель на строку NULL).
TEST(TestPush, Test0)
{
    LNode* head = NULL;

    push(&head, NULL);
    //the list is Expected to be created where the added element will contain data
    // Ожидается, что список будет создан, где добавленный элемент будет содержать данные
    // a pointer to a NULL string     — указатель на строку NULL.
    ASSERT_FALSE(head == NULL);
}


// Test for adding an item to the list 1: adding an empty string.
//Тест добавления элемента в список 1: добавляем пустую строку.
TEST(TestPush, Test1)
{
    LNode* head = NULL;

    push(&head, "");

    //  The list is expected to be created where the added item will contain data
   //Ожидается, что список будет создан, где добавленный элемент будет содержать данные
    //   empty string   — пустую строку.
    EXPECT_STREQ(head->data, "");
}


//Test for adding an item to the list 2: adding the specified one: Тест добавления элемента в список 2: добавляем заданную.
TEST(TestPush, Test2)
{
    LNode* head = NULL;

    push(&head, "abc");

    // The list is expected to be created where the added item will contain data: Ожидается, что список будет создан, где добавленный элемент будет содержать данные
    //     the specified string — заданную строку.
    EXPECT_STREQ(head->data, "abc");
}


// Sorting test 0: sorting an empty list
//Тест сортировки 0: сортировка пустого списка.
TEST(TestSort, Test0)
{
    LNode* head = NULL;

    head = sort(head);

    //It is expected that after sorting an empty list, we will get an empty list: Ожидается, что после сортировки пустого списка получим пустой список.
    ASSERT_TRUE(head == NULL);
}


//Sorting test 1: sorting a list of ASCIIZ strings
// Тест сортировки 1: сортировка списка ASCIIZ строк.
TEST(TestSort, Test1)
{
    LNode* head = NULL;

    // Test data: Тестовые данные.
    push(&head, "abcd");
    push(&head, "gggg");
    push(&head, "bbbb");

    head = sort(head);

    // We expect the sorted list to match these results
    //Ожидаем, что отсортированный список будет соответствовать данным результатам.
    EXPECT_STREQ(head->data, "abcd");
    EXPECT_STREQ(head->next->data, "bbbb");
    EXPECT_STREQ(head->next->next->data, "gggg");
}
