#include "Interface.h"

int ReadData(ListNode* head)
{
	FILE* fp;
	char buffer[100];
	fp = fopen("Data.txt", "r");
	if (fp == NULL) return 0;
	while (fgets(buffer, 99, fp) != NULL) //while not EOF // while not an error
	{
		strPtr Parsed = ParseString(buffer, "--", 2);
		ListNode* q = InitListNode(Parsed[0], atoi(Parsed[1]));
		ListNode* p = FindPlaceToPush(head, q->date);
		PushNode(p, q);
	}
	return 1;
}

int PrintAll(ListNode* head)
{
	int count = 0;
	while (head->next != NULL)
	{
		if (head->date!=0) printf("%s--%d\n", head->name, head->date);
		head = head->next;
		count++;
	}
	printf("-------------\n");
	printf("%d at all.\n\n", count);
	return count;
}

int PrintByDate(ListNode* head,int date)
{
	int count = 0;
	ListNodePtrArray Array = FindByDate(head, date, &count);
	for (int i = 0;i < count;i++) printf("%s--%d\n", Array[i]->name, Array[i]->date);
	printf("-------------\n");
	printf("%d at all.\n\n", count);
	return count;
}

void ShowMenu()
{
	int option;
	int year, month, day;
	int date;
	int flag = 1;
	ListNode* head = InitList();

	printf("Reading Data.\n");
	if (ReadData(head) == 0)
	{
		printf("Can't open file\n");
		return;
	}

	while (flag == 1)
	{
		printf("Choose an option:\n");
		printf("1. Print all persons.\n");
		printf("2. Print persons with some BDay.\n");
		printf("3. Exit.\n");
		printf("Your option is: ");
		scanf("%d", &option);
		printf("\n");	
		switch (option)
		{
		case 1:
			printf("All persons: \n");
			PrintAll(head);
			break;
		case 2:
			printf("Date (YYYY MM DD) is: ");
			scanf("%d%d%d", &year,&month,&day);
			date = year * 10000 + month * 100 + day * 1;
			printf("All persons born in %i:\n", date);
			PrintByDate(head, date);
			break;
		case 3:
			printf("Exit.\n");
			DestroyList(head);
			flag = 0;
			break;
		default:
			printf("Wrong choise, try again.\n");
			break;
		}
	}
}