#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct LIST {
    struct LIST* next;
    int index;
}LIST;

void add_every_block_in_array(LIST** list, int index_add)
{
    LIST* current = *list;
    while (current->next!=NULL)
    {
        current = current->next;
    }
    LIST* NEW = (LIST*)malloc(sizeof(LIST));
    NEW->next = NULL;
    NEW->index = index_add;
    current->next = NEW;
}

void print_one_node(LIST** list, int* printed, int index)
{
    if (printed[index] > 0)
    {
        return;
    }
    printed[index]++;
    printf("%i ", index);
    LIST* first = list[index];
    while (first != NULL)
    {
        print_one_node(list, printed, first->index);
        first = first->next;
    }
}

void print_nodes(LIST** list, int count)
{
    int* printed = calloc(sizeof(int), count);
    for (int i = 0; i < count; i++)
    {
        printed[i] = 0;
    }
    print_one_node(list, printed, 0);
    free(printed);
}


int main()
{
    int count=0;
    int digit = 0;
    int current_index=0;
    char res;
    scanf("%d", &count);
    res = getchar();
    res = getchar();
    LIST** list = calloc(count, sizeof(LIST*));
    for (int i = 0; i < count; i++)
    {
        list[i]=(LIST*)malloc(sizeof(LIST));
        (list[i])->index = i;
        (list[i])->next = NULL;
    }
    while (res != EOF)
    {
        scanf("%d", &digit);
        res = getchar();
        if (res == EOF)
        {
            break;
        }
        while ((res != '\n') && (res != '\r'))
        {
            scanf("%d", &current_index);
            add_every_block_in_array(&list[digit], current_index);
            add_every_block_in_array(&list[current_index], digit);
            res = getchar();
        }
        res = getchar();

    }
    print_nodes(list, count);
    free(list);
    return 0;
}