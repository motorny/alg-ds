
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
typedef struct Vert_t {
      struct Vert_t* vert;
      int num;
} Vert_t;

typedef struct {
    Vert_t* begin;
    Vert_t* end;
} adjList;
void Delete(adjList* list) {
    Vert_t* Elem = list->begin;
    while (Elem != NULL) {
        list->begin = list->begin->vert;
        free(Elem);
        Elem = list->begin;
    }
}

int Read(adjList adjLists[], int length, FILE* fl) {
    int i, k;
    char dig;
    for (i = 0; i < length; i++) {
        fscanf(fl, "%d%c", &k, &dig);
        while (dig == ' ') {
            fscanf(fl, "%d%c", &k, &dig);
            if (!adjLists[i].begin) {
                adjLists[i].begin = (Vert_t*)malloc(sizeof(Vert_t));
                if (adjLists[i].begin == NULL) {
                    for (i = 0; i < length; i++) {
                        Delete(&adjLists[i]);
                    }
                    return 1;
                }
                adjLists[i].end = adjLists[i].begin;
            }
            else {
                adjLists[i].end->vert = (Vert_t*)malloc(sizeof(Vert_t));
                if (adjLists[i].end->vert == NULL) {
                    for (i = 0; i < length; i++) {
                        Delete(&adjLists[i]);
                    }
                    return 1;
                }
                adjLists[i].end = adjLists[i].end->vert;
            }
            adjLists[i].end->num = k;
            adjLists[i].end->vert = NULL;
            if (i < k) {
                if (!adjLists[k].begin) {
                    adjLists[k].begin = (Vert_t*)malloc(sizeof(Vert_t));
                    if (adjLists[k].begin == NULL) {
                        for (i = 0; i < length; i++) {
                            Delete(&adjLists[i]);
                        }
                        return 1;
                    }
                    adjLists[k].end = adjLists[k].begin;
                }
                else {
                    adjLists[k].end->vert = (Vert_t*)malloc(sizeof(Vert_t));
                    if (adjLists[k].end->vert == NULL) {
                        for (i = 0; i < length; i++) {
                            Delete(&adjLists[i]);
                        }
                        return 1;
                    }
                    adjLists[k].end = adjLists[k].end->vert;
                }
                adjLists[k].end->num = i;
                adjLists[k].end->vert = NULL;
            }
        }
    }
    return 0;
}

int* DFS(adjList adjLists[], int length, int* lengthDFS) {
    int* dfs = (int*)malloc(sizeof(int) * length);
    struct {
        int* elem;
        int  top;
    } stack;
    int i = 0, j;
    Vert_t* curVert;

    stack.elem = (int*)malloc(sizeof(int) * length);
    if (!dfs || !stack.elem) {
        free(dfs);
        free(stack.elem);
        return 0;
    }
    dfs[0] = 0;
    *lengthDFS = 1;
    stack.elem[0] = 0;
    stack.top = 0;

    while (stack.top != -1) {
        curVert = adjLists[i].begin;
        for (j = 0; j < *lengthDFS; j++) {
            if (curVert != NULL && curVert->num == dfs[j]) {
                curVert = curVert->vert;
                j = 0;
            }
        }
        if (curVert == NULL) {
            i = stack.elem[stack.top - 1];
            stack.top--;
        }
        else {
            stack.top++;
            stack.elem[stack.top] = curVert->num;
            (*lengthDFS)++;
            dfs[*lengthDFS - 1] = curVert->num;
            i = curVert->num;
        }
    }

    return dfs;
}
int main(void) {
    adjList* adjLists;
    int n, i, lengthDFS;
    int OUT;
    int* res;
    scanf("%d", &n);
    adjLists = (adjList*)malloc(sizeof(adjList) * n);
    if (adjLists == NULL) {
        return 1;
    }
    for (i = 0; i < n; i++) {
        adjLists[i].begin = NULL;
        adjLists[i].end = NULL;
    }

    OUT = Read(adjLists, n, stdin);
    if (OUT == 1) {
        free(adjLists);
        return 1;
    }
    res = DFS(adjLists, n, &lengthDFS);
    for (i = 0; i < lengthDFS; i++) {
        printf("%d ", res[i]);
    }
    for (i = 0; i < n; i++) {
        Delete(&adjLists[i]);
    }
    free(adjLists);
    return 0;
}