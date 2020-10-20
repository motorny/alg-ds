#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	int N = 0;

	node* list = NULL;

	if (argc != 2)
	{
		printf("usage: %s <path>", argv[0]);
		return INCORRECT_START;
	}

	switch (ReadFromFile(argv[1], &list))
	{
	case NOT_ENOUGH_MEMORY:
		printf("not enough memory");
		return 1;
		break;
	case CANNOT_OPEN_FILE:
		printf("file cannot be opened");
		return 1;
		break;
	}

	PrintList(&list, N);
	DestroyList(&list);
	return 0;
}

TEST(TestReadFromFile, UnexstingFile)
{
	node* list = NULL;
	int result = ReadFromFile("NULL", &list);
	EXPECT_EQ(result, CANNOT_OPEN_FILE);
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