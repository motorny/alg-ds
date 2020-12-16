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

void dfs(int x){
    int k=ans[0];
    used[x] = 1;
    ans[0]++;
    ans[k]=x;
    for (int i=0;i<n;i++){
        if (peak[x][i]==1 && used[i] == 0) {
            dfs(i);
        }
    }
    return;
}

int main() {
    scanf("%d",&n);
    int a;
    int b;
    while (scanf("%d%d", &a, &b) == 2) {
        peak[a][b]=1;
        peak[b][a]=1;
    }
    ans[0]=1;
    dfs(0);
    for (int i=1;i< ans[0];i++)
        printf("%d ",ans[i]);
    return 0;
}
