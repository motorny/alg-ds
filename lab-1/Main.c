#include "queue.h"

int main(void) {
    queue_t* queue = NULL;
    int N = 5, N1 = 0, i = 0;
    int num = 8, num1 = 12, extracted = 0;
    int priority = 3;
    int mass[5] = {4, 5, 7, 20, 45};
    int* mass1 = NULL;
    bool_t* flag = (bool_t*)malloc(sizeof(bool_t));
    *flag = 0;

    //
    printf("create an empty queue:\n\n");
    queue = QueueCreate(mass1, N1);

    DeleteMax(queue, flag);
    if (*flag != TRUE) {
        printf("ERROR: no element to delete!\n");
        *flag = TRUE;
    }

    extracted = ExtractMax(queue, flag);
    if (*flag != TRUE) {
        printf("ERROR: no element to extract!\n");
        *flag = TRUE;
    }

    EnqueueByPriority(queue, num, priority, flag);
    if (*flag != TRUE) {
        printf("ERROR: impossible to enqueue!\n\n");
        *flag = TRUE;
    }

    //
    printf("array of numbers: ");
    for (i = 0; i < N; i++)
        printf("%d ", mass[i]);
    printf("\n\n");

    queue = QueueCreate(mass, N);

    printf("create queue:\n");
    PrintQueue(queue); 

    printf("enqueue (%d)[%d]:\n", priority, num);
    EnqueueByPriority(queue, num, priority, flag);
    PrintQueue(queue);

    printf("add at the end [%d]:\n", num1);
    InsertTail(queue, num1, flag);
    PrintQueue(queue);

    printf("remove the first element:\n");
    DeleteMax(queue, flag);
    PrintQueue(queue);

    extracted = ExtractMax(queue, flag);
    printf("extract the first element:\n");
    printf("extracted number = %d\n", extracted);
    PrintQueue(queue);

    QueueDestroy(queue);
    free(flag);

    _CrtDumpMemoryLeaks();
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	return 0;
}