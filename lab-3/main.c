#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
int n;
int peak [2500][2500];
int ans[10000];
int used[10000];
//int k=0;
void dfs(int x){
    int k=ans[0];

//    for (int i=1;i<k;i++)
//        if (ans[i]==x){
//            flag=0;
//            return;
//        }
    used[x] = 1;
    ans[0]++;
    ans[k]=x;
//    printf("%d ",x);

    for (int i=0;i<n;i++){
//        printf("%d",i);
        if (peak[x][i]==1 && used[i] == 0) {
//            peak[x][i] = 0;
//            peak[i][x] = 0;
            dfs(i);
        }
    }
    return;
}

int main() {
//    printf("%d",n);
//    freopen("input.txt","r",stdin);
//    printf("%d",n);
    scanf("%d",&n);
//    printf("%d",n);
    int a;
    int b;
    while (scanf("%d%d", &a, &b) == 2) {
//        a = getc (stdin/zz
//        scanf("%d %d", &a, &b))
        peak[a][b]=1;
        peak[b][a]=1;
//        printf("\n %d %d",a ,b);
    }
//    for (int i=0;i<n;i++){
//        for (int j=0;j<n;j++){
//            printf("%d ",peak[i][j]);
//        }
//        printf("\n");
//    }
//    10
//    0 2
//    0 4
//    0 5
//    1 3
//    1 4
//    2 4
//    2 5
//    2 6
//    2 9
//    3 5
//    3 7
//    5 6
//    5 8
//    7 9
//    printf("\n %d",0);
    ans[0]=1;
    dfs(0);
    for (int i=1;i< ans[0];i++)
        printf("%d ",ans[i]);
//    printf("\n %d",k);
        //    for (int i=0;i<n;i++){
//        for (int j=0;j<n;j++){
//            printf("%d ",peak[i][j]);
//        }
//        printf("\n");
//    }
    return 0;
}
