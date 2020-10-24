#include "working_list.h"

int main()

{
   
    tnode* top = NULL;
    FILE* fp;
    fp = fopen("spisok.txt", "r");
    if (fp == NULL) {
        perror("empty file ");
        return ERROR_OPENING_FILE;
    }

    tnode* person = NULL;
    char* buffer = (char*)calloc(3 * MAX_LE, sizeof(char));

    while (!feof(fp)) {
        fgets(buffer, 3 * MAX_LE, fp);
        person = ConvertInputToNode(buffer);
        AddToList(&top, person);
    }

    PrintInitialList(&top);

    printf("Enter the request in format <<surname>> <<name>> <<second name>> : ");

    fgets(buffer, 3 * MAX_LE, stdin);
    tnode* input = ConvertInputToNode(buffer);
    int count = PrintFilteredList(&top, input);
    if (count == 0) {
        printf("no matches found in list");
    }
    free(input);
    free(buffer);
    FreeList(&top);

    fclose(fp);
    return 0;

}




