
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define SUCCESS 1
#define FAIL 0

typedef struct {
    int size;
    int first;
    int last;
    int* arr;
} queue_t;

typedef struct {
    int num;
    int isvisited;
    int* adj;
} node_t;

typedef struct {
    int n;
    node_t* nodes;
} adjacencylist_t;

int Initialization(queue_t* q, int size) {
    if (size <= 0) {
        return FAIL;
    }
    q->arr = (int*)malloc(sizeof(int) * size);
    if (q->arr) {
        q->size = size;
        q->first = 0;
        q->last = 0;
        return SUCCESS;
    }
    return FAIL;
}

int Push(queue_t* q, int elem) {
    if (q->arr && q->last < q->size) {
        q->arr[q->last++] = elem;
        return SUCCESS;
    }
    return FAIL;
}

int Pop(queue_t* q, int* elem) {
    if (q->arr && q->first < q->last) {
        *elem = q->arr[q->first++];
        return SUCCESS;
    }
    return FAIL;
}

int FreeQueue(queue_t* q) {
    free(q->arr);
    q->arr = NULL;
    q->size = 0;
    q->first = 0;
    q->last = 0;
    return SUCCESS;
}
int BFS(adjacencylist_t* list, queue_t* q) {
    int i, elem;
    if (q->arr && list->n && list->nodes && list->n <= q->size) {
        Push(q, 0);
        list->nodes[0].isvisited = 1;
        while (Pop(q, &elem)) {
            for (i = 0; i < list->nodes[elem].num; i++)
                if (!list->nodes[list->nodes[elem].adj[i]].isvisited) {
                    Push(q, list->nodes[elem].adj[i]);
                    list->nodes[list->nodes[elem].adj[i]].isvisited = 1;
                }
        }
        return SUCCESS;
    }
    return FAIL;
}
int main(void) {
    int i, j;
    adjacencylist_t mylist;
    queue_t q;
    scanf("%d", &mylist.n);
    if (Initialization(&q, mylist.n)) {
        mylist.nodes = (node_t*)calloc(mylist.n, sizeof(node_t));
        if (mylist.nodes) {
            for (i = 0; i < mylist.n; i++) {
                mylist.nodes[i].adj = (int*)calloc(mylist.n, sizeof(int));
                if (!mylist.nodes[i].adj) {
                    for (j = 0; j < i; j++) {
                        free(mylist.nodes[j].adj);
                    }
                    free(mylist.nodes);
                    FreeQueue(&q);
                    return FAIL;
                }
            }
            for (i = 0; i < mylist.n; i++) {
                int curv, tmp;
                char s;
                scanf("%i%c", &curv, &s);
                while (s != '\n' && s != '\r' && s != '\0') {
                    scanf("%i%c", &tmp, &s);
                    mylist.nodes[tmp].adj[mylist.nodes[tmp].num++] = curv;
                    mylist.nodes[curv].adj[mylist.nodes[curv].num++] = tmp;
                }
            }
            BFS(&mylist, &q);
            for (i = 0; i < q.last; i++) {
                printf("%d ", q.arr[i]);
            }
            for (i = 0; i < mylist.n; i++) {
                free(mylist.nodes[i].adj);
            }
            free(mylist.nodes);
        }
        FreeQueue(&q);
    }
    return 0;
}