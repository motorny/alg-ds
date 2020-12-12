#include <stdio.h>
#include <stdlib.h>

#include "LabC3.h"
#pragma warning (disable:4996)


int main(void) {
    int i, j;
    int ind;
    adjacency_list_t list;
    queue_t q;
    

    ind = scanf("%i", &list.numT);
    

    //очередь
    if (CreateQ(&q, list.numT) == FAIL)
        return 0;
    list.tops = (node_t*)calloc(list.numT, sizeof(node_t));

    if (list.tops == NULL) {
        DeleteQ(&q);
        return 0;
    }

    //рёбра
    for (i = 0; i < list.numT; i++) {
        list.tops[i].edges = (int*)calloc(list.numT, sizeof(int));

        if (list.tops[i].edges == NULL) {
            for (j = 0; j < i; j++) {
                free(list.tops[j].edges);
            }

            free(list.tops);
            DeleteQ(&q);
            return 0;
        }
    }



    ReadAdjacencyList(&list);
    BreadthFirstSearch(&list, &q);

    for (i = 0; i < q.tail; i++)
        printf("%i ", q.arr[i]);


    for (i = 0; i < list.numT; i++) {
        if (list.tops[i].edges != NULL) {
            free(list.tops[i].edges);

        }
    }
        

    free(list.tops);
    DeleteQ(&q);
    return 0;
}