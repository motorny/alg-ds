#include "List.h" 
#pragma warning(disable:4996) 
int main()
{
	char proverka[100];
	LIST* current;
	LIST* List_1 = (LIST*)malloc(sizeof(LIST));//; 
	if (List_1 == NULL)
	{
		return 1;
	}
	LIST* List_2 = (LIST*)malloc(sizeof(LIST));//; 
	if (List_2 == NULL)
	{
		return 2;
	}
	FILE* fp1;
	fp1 = fopen("name1.txt", "r");
	FILE* fp2;
	fp2 = fopen("name2.txt", "r");
	FILE* fp3;
	fp3 = fopen("name3.txt", "w");
	write(fp1, List_1);
	write(fp2, List_2);
	if (List_2->data[0] == '\0')
	{
		LIST* List_3 = (LIST*)malloc(sizeof(LIST));//; 
		List_3 = List_2;
		List_2 = List_1;
		List_1 = List_3;
	}
	merger(List_1, List_2);
	current = List_2;
	while (current != NULL)
	{
		fputs(current->data, fp3);
		current = current->next;
	}

	free_list(List_1);
	free_list(List_2);
	return 0;
}