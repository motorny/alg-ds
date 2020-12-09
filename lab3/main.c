#include "dfs.h"

int main(void) {
    node_t* list;
    int num;
    scanf("%i", &num);
    list = (node_t*)malloc(num * sizeof(node_t));
    if (!list) {
        printf("ERROR: No memory");
        return -1;
    }

    CreateList(list, num);
    ReadGraph(list, num);
    DFS(list, 0, num);
    DestroyList(list, num);

    _CrtDumpMemoryLeaks();
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    return 0;
}