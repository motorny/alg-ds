#include "pch.h"


//Off errors on the unsafe use of "old" C features: ���������� ������ �� ������������� ������������ "������" ������� ��.
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>



// The structure of the list item: ��������� �������� ������.
typedef struct LNode
{
    // Pointer to an ASCIIZ string: ��������� �� ASCIIZ ������.
    char* data;
    // Pointer to the next item in the list: ��������� �� ��������� ������� ������.
    struct LNode* next;
} LNode;


//Add an item to the list: �������� ������� � ������.
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


// Sorting the list using the insert method. The function returns a pointer to the head of the sorted list: ���������� ������ ������� �������. ������� ���������� ��������� �� ������ ���������������� ������.
LNode* sort(LNode* head)
{
    LNode* a;
    LNode* b;
    LNode* c;
    LNode* res = NULL;

    // Until the list is empty: ���� �� ���� ������.
    while (head != NULL)
    {
        a = head; head = head->next;

        //Search for an insertion point: ����� ����� �������.
        for (b = res, c = NULL; b != NULL && strcmp(a->data, b->data) > 0; c = b, b = b->next);

        // Enabling before the first one: ��������� ����� ������.
        if (c == NULL)
        {
            a->next = res;
            res = a;
        }
        //Enabling after the previous one: ��������� ����� �����������.
        else
        {
            a->next = b;
            c->next = a;
        }
    }

    return res;
}


// Test for adding an element to a list 0: adding an "empty" element (a pointer to a NULL string)
//���� ���������� �������� � ������ 0: ��������� "������" ������� (��������� �� ������ NULL).
TEST(TestPush, Test0)
{
    LNode* head = NULL;

    push(&head, NULL);
    //the list is Expected to be created where the added element will contain data
    // ���������, ��� ������ ����� ������, ��� ����������� ������� ����� ��������� ������
    // a pointer to a NULL string     � ��������� �� ������ NULL.
    ASSERT_FALSE(head == NULL);
}


// Test for adding an item to the list 1: adding an empty string.
//���� ���������� �������� � ������ 1: ��������� ������ ������.
TEST(TestPush, Test1)
{
    LNode* head = NULL;

    push(&head, "");

    //  The list is expected to be created where the added item will contain data
   //���������, ��� ������ ����� ������, ��� ����������� ������� ����� ��������� ������
    //   empty string   � ������ ������.
    EXPECT_STREQ(head->data, "");
}


//Test for adding an item to the list 2: adding the specified one: ���� ���������� �������� � ������ 2: ��������� ��������.
TEST(TestPush, Test2)
{
    LNode* head = NULL;

    push(&head, "abc");

    // The list is expected to be created where the added item will contain data: ���������, ��� ������ ����� ������, ��� ����������� ������� ����� ��������� ������
    //     the specified string � �������� ������.
    EXPECT_STREQ(head->data, "abc");
}


// Sorting test 0: sorting an empty list
//���� ���������� 0: ���������� ������� ������.
TEST(TestSort, Test0)
{
    LNode* head = NULL;

    head = sort(head);

    //It is expected that after sorting an empty list, we will get an empty list: ���������, ��� ����� ���������� ������� ������ ������� ������ ������.
    ASSERT_TRUE(head == NULL);
}


//Sorting test 1: sorting a list of ASCIIZ strings
// ���� ���������� 1: ���������� ������ ASCIIZ �����.
TEST(TestSort, Test1)
{
    LNode* head = NULL;

    // Test data: �������� ������.
    push(&head, "abcd");
    push(&head, "gggg");
    push(&head, "bbbb");

    head = sort(head);

    // We expect the sorted list to match these results
    //�������, ��� ��������������� ������ ����� ��������������� ������ �����������.
    EXPECT_STREQ(head->data, "abcd");
    EXPECT_STREQ(head->next->data, "bbbb");
    EXPECT_STREQ(head->next->next->data, "gggg");
}
