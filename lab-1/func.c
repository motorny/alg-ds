#include "List.h" 
int write(FILE* fp, LIST* List)
{
	
	char reade[101];
	List->next = NULL;
	int count_runs = 0;
	LIST* current;
	LIST* prew;
	while (fgets(reade, word_length, fp) != NULL)
		{
			int longl = strlen(reade);
			if (count_runs == 0)
			{
				for (unsigned int i = 0; i < strlen(reade); i++)
				{
					List->data[i] = reade[i];
				}
				List->data[strlen(reade)] = '\0';
			}
			else {
				current = List;
				prew = current;
				LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
				if (NewBlock == NULL)
				{
					return problem;
				}
				while (current != NULL && strcmp(current->data, reade) < 0)
				{
					prew = current;
					current = current->next;
				}
				for (unsigned int i = 0; i < strlen(reade); i++)
				{
					NewBlock->data[i] = reade[i];
				}
				NewBlock->data[strlen(reade)] = '\0';
				if (current == List)
				{
					for (unsigned int i = 0; i <= strlen(reade); i++)
					{
						reade[i] = List->data[i];
						List->data[i] = NewBlock->data[i];
						NewBlock->data[i] = reade[i];
					}
					NewBlock->next = List->next;
					List->next = NewBlock;
					List->data[longl - 1] = '\n';
					List->data[longl] = '\0';
				}
				else
				{
					NewBlock->next = current;
					prew->next = NewBlock;
				}
			}
			count_runs++;
		}
	if (count_runs == 0)
	{
		List->data[0]='\0';
	}
	return 0;
}

int merger(LIST* List1, LIST* List2, LIST* List3)
{
	LIST* current_List2;
	LIST* prev_List2;
	LIST* current_List1;
	LIST* current_List3;
	LIST* prev_List1;
	LIST* prev_List3;
	current_List1 = List1;
	current_List2 = List2;
	current_List3 = List3;
	while (current_List1 != NULL && current_List2 != NULL)
	{
		LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
		current_List3->next = NewBlock;
		if (strcmp(current_List1->data, current_List2->data) < 0 && current_List1->data[0] != '\0')
		{
			for (int i = 0; i < word_length; i++)
			{
				current_List3->data[i] = current_List1->data[i];
			}
			current_List1 = current_List1->next;
			current_List3->next = NewBlock;
			current_List3 = current_List3->next;
		}
		else if (strcmp(current_List1->data, current_List2->data) > 0 && current_List2->data[0] != '\0')
		{
			for (int i = 0; i < word_length; i++)
			{
				current_List3->data[i] = current_List2->data[i];
			}
			current_List2 = current_List2->next;
			current_List3->next = NewBlock;
			current_List3 = current_List3->next;
		}
		else if (strcmp(current_List1->data, current_List2->data) == 0)
		{
			for (int i = 0; i < word_length; i++)
			{
				current_List3->data[i] = current_List2->data[i];
			}
			current_List2 = current_List2->next;
			current_List3->next = NewBlock;
			current_List3 = current_List3->next;
			for (int i = 0; i < word_length; i++)
			{
				current_List3->data[i] = current_List1->data[i];
			}
			current_List1 = current_List1->next;
			LIST* NewBlock2 = (LIST*)malloc(sizeof(LIST));
			current_List3->next = NewBlock2;
			current_List3 = current_List3->next;
		}
		if (current_List1 != NULL&& current_List2 != NULL)
		{
			if (current_List1->data[0] == '\0')
			{
				while (current_List2 != NULL)
				{
					LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
					for (int i = 0; i < word_length; i++)
					{
						current_List3->data[i] = current_List2->data[i];
					}
					current_List2 = current_List2->next;
					current_List3->next = NewBlock;
					current_List3 = current_List3->next;
					
				}
				current_List3->next = NULL;
				return 0;
			}
			if (current_List2 != NULL)
			{
				if (current_List2->data[0] == '\0')
				{
					while (current_List1 != NULL)
					{
						LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
						for (int i = 0; i < word_length; i++)
						{
							current_List3->data[i] = current_List1->data[i];
						}
						current_List1 = current_List1->next;
						current_List3->next = NewBlock;
						current_List3 = current_List3->next;
					}
					current_List3->next = NULL;
					return 0;
				}
			}
		}
		//prev_List3 = current_List3;
		//current_List3->next = NewBlock;
		//current_List3 = current_List3->next;
	}
	if (current_List1 != NULL)
	{
		while (current_List1 != NULL)
		{
			for (int i = 0; i < word_length; i++)
			{
				current_List3->data[i] = current_List1->data[i];
			}
			current_List1 = current_List1->next;
			LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
			current_List3->next = NewBlock;
			current_List3 = current_List3->next;
		}
		current_List3->next = NULL;
		return 0;
	}
	else if (current_List2 != NULL)
	{
		if (current_List2 != NULL)
		{
			for (int i = 0; i < word_length; i++)
			{
				current_List3->data[i] = current_List2->data[i];
			}
			current_List3->next = NULL;
			return 0;
		}
	}
	current_List3->next = NULL;
	return 0;
}

int free_list(LIST* List)
{
	LIST* prew;
	LIST* current;
	int status = 0;
	current = List->next;
	prew = List;
	while (current != NULL)
	{
		free(prew);
		prew = current;
		current = current->next;
		status = 1;
	}
	if (status == 0)
	{
		free(prew);
	}
	return 0;
}
