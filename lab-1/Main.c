#include "queue.h"

int error = 0;

int main(void) {
    queue_t* queue = NULL;
    int N = 5, N1 = 0, i = 0;
    int num = 8, num1 = 12, extracted = 0;
    int priority = 3;
    int mass[5] = {4, 5, 7, 20, 45};
    int* mass1 = NULL;
    //bool_t flag = TRUE;

    //
    printf("create an empty queue:\n\n");
    queue = QueueCreate(mass1, N1);

    DeleteMax(queue);
    if (error != FINISHED) {
        printf("ERROR: no element to delete!\n");
        error = 0;
    }

    extracted = ExtractMax(queue);
    if (error != FINISHED) {
        printf("ERROR: no element to extract!\n");
        error = 0;
    }

    EnqueueByPriority(queue, num, priority);
    if (error != FINISHED) {
        printf("ERROR: impossible to enqueue!\n\n");
        error = 0;
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
    EnqueueByPriority(queue, num, priority);
    PrintQueue(queue);

    printf("add at the end [%d]:\n", num1);
    InsertTail(queue, num1);
    PrintQueue(queue);

    printf("remove the first element:\n");
    DeleteMax(queue);
    PrintQueue(queue);

    extracted = ExtractMax(queue);
    printf("extract the first element:\n");
    printf("extracted number = %d\n", extracted);
    PrintQueue(queue);

    QueueDestroy(queue);

    _CrtDumpMemoryLeaks();
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	return 0;
}