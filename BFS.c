#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

typedef struct
{
    int n, was_visited;
    int num_neighborhoods;
    int* neighborhoods;
} node_t;

typedef struct
{
    int vertices_num;
    node_t* vertices;
} adjacency_list_t;

typedef struct
{
    int* data;
    int head, tail;
    int size;

} queue_t;

int init_queue(queue_t* queue, int size)
{
    if (queue == NULL)
        return FAIL;


    queue->data = (int*)malloc(queue->size * sizeof(int));
    if (queue->data == NULL)
        return FAIL;

    queue->size = size;
    queue->head = 0;
    queue->tail = 0;


    return SUCCESS;
}

int push_queue(int value, queue_t* q)
{
    if (q->data == NULL || q->tail >= q->size)
        return FAIL;
    q->data[q->tail] = value;
    (q->tail)++;


    return SUCCESS;
}

int pop_queue(queue_t* q, int* value)
{
    if (q->data == NULL || q->head >= q->tail)
        return FAIL;

    *value = q->data[q->head];
    (q->head)++;


    return SUCCESS;
}

int delete_queue(queue_t* q)
{
    free(q->data);
    q->data = NULL;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    return SUCCESS;
}

int read_adjacency_list(adjacency_list_t* list)
{
    int curr, line_num;
    char ch;
    int i;

    if (list == NULL)
        return FAIL;

    scanf("%i", &list->vertices_num);
    list->vertices = (node_t*)malloc(list->vertices_num * sizeof(node_t));
    if (list->vertices == NULL)
        return FAIL;

    for (i = 0; i < list->vertices_num; i++)
    {
        list->vertices[i].was_visited = 0;
        list->vertices[i].num_neighborhoods = 0;
        list->vertices[i].neighborhoods = (int*)malloc(list->vertices_num * sizeof(int));
        if (list->vertices[i].neighborhoods == NULL)
        {
            i--;
            for (i; i >= 0; i--)
                free(list->vertices[i].neighborhoods);
            free(list->vertices);
            list->vertices = NULL;
            return FAIL;
        }
    }

    for (line_num = 0; line_num < list->vertices_num; line_num++) {
        scanf("%i%c", &i, &ch);
        list->vertices[i].n = i;
        while (ch == ' ')
        {
            scanf("%i%c", &curr, &ch);
            list->vertices[i].neighborhoods[list->vertices[i].num_neighborhoods] = curr;
            list->vertices[i].num_neighborhoods++;
            list->vertices[curr].neighborhoods[list->vertices[curr].num_neighborhoods] = i;
            list->vertices[curr].num_neighborhoods++;
        }
    }

    return SUCCESS;
}

int free_adjacency_list(adjacency_list_t* list)
{
    int curNode;

    if (list == NULL || list->vertices == NULL)
        return FAIL;

    for (curNode = 0; curNode < list->vertices_num; curNode++)
        if (list->vertices[curNode].neighborhoods != NULL)
            free(list->vertices[curNode].neighborhoods);
    free(list->vertices);
    list->vertices = NULL;

    return SUCCESS;
}

int bfs(adjacency_list_t* list)
{
    queue_t q;
    int vertices_num, neighbor_num;

    if (list == NULL || list->vertices == NULL || !init_queue(&q, list->vertices_num))
        return FAIL;

    push_queue(list->vertices[0].n, &q);
    list->vertices[0].was_visited = 1;

    while (q.tail != q.head)
    {
        pop_queue(&q, &vertices_num);
        printf("%i ", vertices_num);
        for (neighbor_num = 0; neighbor_num < list->vertices[vertices_num].num_neighborhoods; neighbor_num++) {
            if (list->vertices[list->vertices[vertices_num].neighborhoods[neighbor_num]].was_visited == 0) {
                push_queue(list->vertices[vertices_num].neighborhoods[neighbor_num], &q);
                list->vertices[list->vertices[vertices_num].neighborhoods[neighbor_num]].was_visited = 1;
            }
        }
    }


    delete_queue(&q);
    return SUCCESS;
}

int main(void)
{
    adjacency_list_t list;
    read_adjacency_list(&list);
    bfs(&list);
    free_adjacency_list(&list);

    return 0;
}