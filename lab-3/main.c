#include <stdio.h>
#include "malloc.h"

typedef unsigned int V;

typedef struct E{
    V u;
    struct E* nextPtr;
} e;

typedef struct Graph{
    e* Adj;
} G;


int main() {
    unsigned int countOfNumber;
    scanf("%d", &countOfNumber);
    G g = {(e *) malloc(countOfNumber + 1)};
    g.Adj[0] =
    printf("%d",g);
    return 0;
}
