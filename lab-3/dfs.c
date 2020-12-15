#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define ERROR -1



void dfs(int** arr, int root,int c){
    if(!arr[root][c]){
       arr[root][c]=1;
       printf("%d ", root);
        for (int i = 0; i < c; ++i) {
            if(arr[i][root]&&!arr[i][c])
            dfs(arr,i,c);
        }
    }

}






int** fill(int c) {
   int** arr = (int**)malloc(sizeof(int*) * c);
   if(!arr)
       return ERROR;
    for (int i = 0; i < c; ++i) {
        arr[i] = (int*)malloc(sizeof(int) * (c+1));
        if(!arr[i])
            return ERROR;
        for (int j = 0; j < c; ++j) {
            if (i != j) {
                arr[i][j] = 0;
            }
            else
                arr[i][j] = 1;
        }
        arr[i][c]=0;
    }

    for (int i = 0; i < c; ++i) {
        int a = 0, j = 0;
        int b = 0;
        int flag = 1;
        char buf[100];
        char s;
        int k = 0;
        while ((s = (char)getchar()) != '\n') {
            buf[k++] = s;
            if ((s == ' ') && flag) {
                buf[k - 1] = 0;
                a = atoi(buf);
                flag = 0;
                k = 0;
            }
            else if (s == ' ')
            {
                buf[k - 1] = 0;
                b = atoi(buf);
                arr[a][b] = 1;
                arr[b][a] = 1;
                k = 0;
            }
        }
        if (k&&!flag) {
            buf[k] = 0;
            b = atoi(buf);
            arr[a][b] = 1;
            arr[b][a] = 1;
        }
    }

    return arr;
}




int main() {
    int count = 0;
    int k = 0;
    char s;
    char buf[30];
    while ((s = (char)getchar()) != '\n') {
        buf[k++] = s;
    }
    buf[k] = 0;
    count = atoi(buf);

  int** arr = fill(count);

  dfs(arr,0,count);





    for (int i = 0; i <count ; ++i) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}
