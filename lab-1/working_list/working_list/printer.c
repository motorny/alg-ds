#include "working_list.h"

int PrintFilteredList(tnode** top, tnode* input) { // applies entered filters "info" to list and prints it
    int match_counter = 0;
    tnode* tmp = (*top);
    while (tmp != NULL) {                    // does nothing if initial list is empty, as intended
        if (Compare(tmp, input) == MATCH) {
            printf("%s\n", tmp->surname);
            match_counter++;
        }
        tmp = tmp->next;
    }
    return match_counter;
}

void PrintInitialList(tnode** top) { // prints the list read from the file
    tnode* tmp = (*top);            // prints only surnames
    if ((*top) == NULL) {
        printf("empty list");
        return;
    }
    while (tmp != NULL) {
        printf("%s\n", tmp->surname);
        tmp = tmp->next;
    }
    printf("list successfully printed\n");
}


void FreeList(tnode** top) {        // kills the list after the programm is done
    tnode* tmp = (*top);
    if (tmp == NULL) return;
    while ((*top) != NULL) {
        tmp = (*top);
        (*top) = (*top)->next;
        free(tmp);
    }
    free(*top);
}





