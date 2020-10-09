#include "List.h" 
#pragma warning(disable:4996) 
int main()
{
	LIST* current;
	LIST* List_1 = (LIST*)malloc(sizeof(LIST));
	if (List_1 == NULL)
	{
		return problem;
	}
	LIST* List_2 = (LIST*)malloc(sizeof(LIST));
	if (List_2 == NULL)
	{
		return problem;
	}
	LIST* List_3 = (LIST*)malloc(sizeof(LIST));
	if (List_3 == NULL)
	{
		return problem;
	}
	FILE* fp1;
	fp1 = fopen("name1.txt", "r");
	FILE* fp2;
	fp2 = fopen("name2.txt", "r");
	FILE* fp3;
	fp3 = fopen("name3.txt", "w");
	write(fp1, List_1);
	write(fp2, List_2);
	merger(List_1, List_2,List_3);
	current = List_3;
	while (current->next != NULL)
	{
		fputs(current->data, fp3);
		current = current->next;
	}

	free_list(List_1);
	free_list(List_2);
	return 0;
}