#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct LIST {
	struct LIST* forward;
	int mark;
}LIST;

void getBlock_inArray(LIST** list, int markSum)
{
    LIST* now = *list;
    while (now->forward != NULL)
    {
        now = now->forward;
    }
    LIST* fresh = (LIST*)malloc(sizeof(LIST));
    fresh->forward = NULL;
    fresh->mark = markSum;
    now->forward = fresh;
}
void displaySingleNode(LIST** list, int* display, int mark)
{
    if (display[mark] > 0)
    {
        return;
    }
    display[mark]++;
    printf("%i ", mark);
    LIST* prime = list[mark];
    while (prime != NULL)
    {
        displaySingleNode(list, display, prime->mark);
        prime = prime->forward;
    }
}
void displayNodes(LIST** list, int reckon)
{
    int* display = (int*)calloc(sizeof(int), reckon);
    for (int k = 0; k < reckon; k++)
    {
        display[k] = 0;
    }
    displaySingleNode(list, display, 0);
    free(display);
}

int main()
{
    int reckon = 0;
    int num = 0;
    int markNow = 0;
    char got;
    scanf("%d", &reckon);
    got = getchar();
    got = getchar();
    LIST** list = (LIST**)calloc(reckon, sizeof(LIST*));
    for (int k = 0; k < reckon; k++)
    {
        list[k] = (LIST*)malloc(sizeof(LIST));
        (list[k])->mark = k;
        (list[k])->forward = NULL;
    }
    while (got != EOF)
    {
        scanf("%d", &num);
        got = getchar();
        if (got == EOF)
        {
            break;
        }
        while ((got != '\n') && (got != '\r'))
        {
            scanf("%d", &markNow);
            getBlock_inArray(&list[num], markNow);
            getBlock_inArray(&list[markNow], num);
            got = getchar();
        }
        got = getchar();

    }
    displayNodes(list, reckon);
    free(list);
    return 0;
}

