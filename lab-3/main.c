#include <stdio.h>
#include <stdlib.h>

typedef struct pair_node{
    struct pair_node *next;
    int index;
}pair_node_t;

void insert_in_pair_list(pair_node_t **list, int element)
{
    if (*list == NULL)
    {
        *list = (pair_node_t*)malloc(sizeof(pair_node_t));
        (*list)->next = NULL;
        (*list)->index = element;
        return;
    }

    if ((*list)->index == element)
        return;

    if ((*list)->index > element)
    {
        pair_node_t* new = (pair_node_t*)malloc(sizeof(pair_node_t));
        new->index = element;
        new->next = *list;
        *list = new;
        return;
    }

    pair_node_t *temp = *list;
    while (temp->next != NULL)
    {
        if (temp->next->index == element)
            return;

        if (temp->next->index > element)
        {
            pair_node_t* new = (pair_node_t*)malloc(sizeof(pair_node_t));
            new->index = element;
            new->next = temp->next;
            temp->next = new;
            return;
        }
        temp = temp->next;
    }

    pair_node_t* new = (pair_node_t*)malloc(sizeof(pair_node_t));
    new->index = element;
    new->next = NULL;
    temp->next = new;
    return;
}

void make_pair(pair_node_t** array, int first, int last)
{
    insert_in_pair_list(&array[first], last);
    insert_in_pair_list(&array[last], first);
}

void print_one_node(pair_node_t** nodes, int* printed, int index)
{
    if (printed[index] > 0)
        return;
    printed[index]++;
    printf("%i ", index);

    pair_node_t *first = nodes[index];
    while (first != NULL)
    {
        print_one_node(nodes, printed, first->index);
        first = first->next;
    }
}

void print_nodes(pair_node_t** nodes, int count)
{
    int *printed = calloc(sizeof(int), count);
    for (int i = 0; i < count; i++)
        printed[i] = 0;
    print_one_node(nodes, printed, 0);
    free(printed);
}

void scan_pairs(pair_node_t** array, int count)
{
    for (int i = 0; i < count; i++)
    {
        int node = -1, right = -1;
        int res = 0;
        scanf("%d", &node);
        res = getchar();
        if (res == '\n' || res == EOF || res == '\r')
        {
            if(res == '\r')
                getchar();
            continue;
        }

        do {
            if (scanf("%d", &right) == 1)
                make_pair(array, node, right);
            res = getchar();
        } while((res != '\n') && (res != '\r') && (res != EOF));
        if(res == '\r')
            getchar();
    }
}

void destroy_all_pairs(pair_node_t*** array, int count)
{
    for (int i = 0; i < count; i++)
    {
        pair_node_t *first = (*array)[i];
        while (first != NULL)
        {
            pair_node_t *del = first;
            first = first->next;
            free(del);
        }
    }

    free(*array);
    *array = NULL;
}

int main()
{
    int count = 0;
    scanf("%d", &count);

    if (count > -1)
    {
        pair_node_t** array = calloc(sizeof(pair_node_t*), count + 1);
        scan_pairs(array, count);
        print_nodes(array, count);
        destroy_all_pairs(&array, count);
    }
    return 0;
}
