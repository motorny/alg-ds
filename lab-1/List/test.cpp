#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _EmployerInfo
{
	struct tm mytime;
	char firstName[255];
	char secondName[255];
	int payload;
}EmployerInfo;

typedef struct node
{
	void* data;
	struct node* next;
}node;

static int created = 0, destroyed = 0;

void* AllocMemory(size_t size)
{
	void* mem = malloc(size);
	if (mem)
		created++;
	return mem;
}

void DestoryMemory(void* ptr)
{
	free(ptr);
	destroyed++;
}

void InsertNodeInList(node** head, node* ptr, bool(*predicate)(void*, void*))
{
	if (*head == NULL)
	{
		*head = ptr;
		return;
	}

	node zero, * temp = &zero;
	zero.next = *head;
	while (temp->next != NULL)
	{
		if (predicate(temp->next->data, ptr->data))
		{
			node* swap = temp->next;
			temp->next = ptr;
			ptr->next = swap;
			break;
		}
		temp = temp->next;
	}

	if (temp->next == NULL)
		temp->next = ptr;
	*head = zero.next;
}

void DestroyList(node** head)
{
	node* temp = *head;
	while (temp != NULL)
	{
		*head = temp;
		temp = temp->next;
		DestoryMemory((*head)->data);
		DestoryMemory(*head);
	}
	*head = NULL;
}

void PrintList(node** list, int N)
{
	node* temp = *list;
	EmployerInfo* ei;
	char date[30];

	while (temp != NULL)
	{
		ei = (EmployerInfo*)temp->data;
		if (ei->payload >= N)
			printf("%i.%i.%i  %s\n", ei->mytime.tm_mday, ei->mytime.tm_mon, ei->mytime.tm_year, ei->secondName);
		temp = temp->next;
	}
}

bool EmployersPredicate(void* old, void* next)
{
	EmployerInfo* one, * two;
	one = (EmployerInfo*)old;
	two = (EmployerInfo*)next;
	if (one->payload == two->payload)
	{
		int result = strcmp(one->secondName, two->secondName);

		if (result == 0)  //строка одинаковая
		{
			result = strcmp(one->firstName, two->firstName);
			if (result > 0)
				return true;    //old должен быть ПОСЛЕ next
			else
				return false;   //old должен быть ПЕРЕД next
		}
		else if (result > 0)
			return true;    //old должен быть ПОСЛЕ next
		else if (result < 0)
			return false;   //old должен быть ПЕРЕД next
	}
	return one->payload > two->payload;
}

int ReadFromFile(char* FileName, node** head)
{
	FILE* myFile = NULL;
	fopen_s(&myFile, FileName, "rb");
	if (myFile == NULL)
		return -1;

	char str[255];
	while (fgets(str, 255, myFile) != NULL)
	{
		node* temp = (node*)AllocMemory(sizeof(node));
		EmployerInfo* ei = (EmployerInfo*)AllocMemory(sizeof(EmployerInfo));
		memset(ei, 0, sizeof(EmployerInfo));
		temp->data = ei;
		temp->next = NULL;

		char* token;

		token = strtok(str, ".");
		ei->mytime.tm_mday = atoi(token);

		token = strtok(NULL, ".");
		ei->mytime.tm_mon = atoi(token);

		token = strtok(NULL, ",");
		ei->mytime.tm_year = atoi(token);

		token = strtok(NULL, ",");
		strcpy(ei->firstName, token);

		token = strtok(NULL, ",");
		strcpy(ei->secondName, token);

		token = strtok(NULL, "\n");
		ei->payload = atoi(token);

		InsertNodeInList(head, temp, EmployersPredicate);
	}

	fclose(myFile);

	return 0;
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	int N = 0;

	node* list = NULL;
	int fail = ReadFromFile("C:\\Users\\Евгений\\source\\repos\\Sample-Test1\\text.txt", &list);
	if (fail == -1)
		return -1;

	PrintList(&list, N);
	DestroyList(&list);
	printf("\nCreated %i, Destroyed %i", created, destroyed);
	return 0;
}

TEST(TestReadFromFile, UnexstingFile)
{
	node* list = NULL;
	int result = ReadFromFile("NULL", &list);
	EXPECT_EQ(result, -1);
}

TEST(TestList, IncorrectAdd)
{
	node* list = NULL;
	EmployerInfo* mydata = (EmployerInfo*)malloc(sizeof(EmployerInfo));
	
	node* temp = (node*)malloc(sizeof(node));
	temp->data = mydata;
	temp->next = NULL;

	strcpy(mydata->firstName, "Zhenya");
	strcpy(mydata->secondName, "Redchenko");
	mydata->payload = 150;
	mydata->mytime.tm_year = 2002;
	mydata->mytime.tm_mon = 1;
	mydata->mytime.tm_mday = 15;

	InsertNodeInList(&list, temp, EmployersPredicate);

	EXPECT_EQ(((EmployerInfo*)list->data)->payload, 150);
	EXPECT_EQ(((EmployerInfo*)list->data)->mytime.tm_year, 2002);
	EXPECT_EQ(((EmployerInfo*)list->data)->mytime.tm_mon, 1);
	EXPECT_EQ(((EmployerInfo*)list->data)->mytime.tm_mday, 15);
	EXPECT_TRUE(!strcmp(((EmployerInfo*)list->data)->firstName, "Zhenya"));
	EXPECT_TRUE(!strcmp(((EmployerInfo*)list->data)->secondName, "Redchenko"));
}

TEST(TestEmplyaerPredicate, WrongSort)
{
	EmployerInfo one, two;

	one.payload = 100;
	two.payload = 120;
	bool result = EmployersPredicate(&one, &two);
	EXPECT_EQ(result, 0);

	two.payload = 80;
	result = EmployersPredicate(&one, &two);
	EXPECT_EQ(result, 1);

	two.payload = 100;
	strcpy(one.secondName, "Redchenko");
	strcpy(two.secondName, "Neredchenko");
	result = EmployersPredicate(&one, &two);
	EXPECT_EQ(result, 1);

	strcpy(two.secondName, "Redchenko");
	strcpy(one.firstName, "Zhenia");
	strcpy(two.firstName, "Nezhenia");
	result = EmployersPredicate(&one, &two);
	EXPECT_EQ(result, 1);
}