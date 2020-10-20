#include "Functions.h"

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
		free((*head)->data);
		free(*head);
	}
	*head = NULL;
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
		return CANNOT_OPEN_FILE;

	char str[255];
	while (fgets(str, 255, myFile) != NULL)
	{
		node* temp = (node*)malloc(sizeof(node));
		EmployerInfo* ei = (EmployerInfo*)malloc(sizeof(EmployerInfo));

		if (temp == NULL || ei == NULL)
		{
			free(temp);
			free(ei);
			return NOT_ENOUGH_MEMORY;
		}

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