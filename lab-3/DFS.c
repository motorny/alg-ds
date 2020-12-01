#include "DFS.h"
#include <stdio.h>
#include <stdlib.h>

void FindDFS(t_Graf *graf, int *ask, int *askNum, int *visit, int row) {
    visit[row] = 1;
    ask[(*askNum)++] = row;
    for ( int i = 0; i < graf->size; i++ ) {
        if ( graf->matrix[row][i] && !visit[i] )
            FindDFS(graf, ask, askNum, visit, i);
    }
}

t_Answer DFS(t_Graf *graf) {
    int *ask, *visit, size, askNum;
    t_Answer Ans;
    Ans.arr = NULL;
    Ans.size = 0;


    if ( graf == NULL ) {
        return Ans;
    }

    size = graf->size;
    ask = (int *) malloc(sizeof(int) * size);
    visit = (int *) malloc(sizeof(int) * size);
    if ( visit&&ask ) {
        memset(visit, 0, sizeof(int) * size);
    }
    else {
        free(ask);
        free(visit);
        return Ans;
    }
    
    askNum = 0;

    FindDFS(graf, ask, &askNum, visit, 0);

    free(visit);
    Ans.arr = ask;
    Ans.size = askNum;
    return Ans;
}

t_Graf *ScanGrafFromStdin(void){
    int size, **mat, i, j, a, b;
    t_Graf *graf;


    printf("Number of graph vertices: ");
    scanf("%i", &size);

    mat = (int **)malloc(sizeof(int*) * size);
    if ( !mat ) {
        return NULL;
    }

    for ( i = 0; i < size; i++ ) {
        mat[i] = (int *)malloc(sizeof(int) * size);
        if ( mat[i] == NULL ) break;

        for ( j = 0; j < size; j++ )
            mat[i][j] = 0;
    }

    if ( i != size ) {
        for ( j = 0; j < i; j++ )
            free(mat[j]);
        free(mat);

        return NULL;
    }

    printf("Press Ctrl+D to Play\n");

    while ( scanf("%i %i", &a, &b) > 0) {
        if ( !(a < size && b < size) ) {
            printf("Fail data!\n");
            continue;
        }
        mat[a][b] = 1;
        mat[b][a] = 1;
    }


    graf = (t_Graf *)malloc(sizeof(t_Graf));
    if ( graf == NULL ) {
        for ( j = 0; j < size; j++ )
            free(mat[j]);
        free(mat);

        return NULL;
    }
    graf->size = size;
    graf->matrix = mat;

    return graf;    
}

void DelGraf(t_Graf *graf){
    int size = graf->size;
    int **mat = graf->matrix;

    for ( int i = 0; size > i; i++ )
        free(mat[i]);
    free(mat);

    free(graf);
}
