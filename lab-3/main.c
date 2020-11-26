#include <stdio.h>
#include <stdlib.h>
#include "DFS.h"

int main(void) {
    t_Graf *graf;
    t_Answer ans;

    graf = ScanGrafFromStdin();
    if ( graf == NULL ) {
        return -1;
    }
    ans = DFS(graf);
    DelGraf(graf);

    if ( ans.arr != NULL ) {
        for ( int i = 0; i < ans.size; i++ )
            printf("%d ", ans.arr[i]);
        free(ans.arr);
    }
    else {
        return -1;
    }

    return 0;
}