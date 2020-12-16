#include"list.h"
DblLinkedList* CreateList(void) {
    DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
    if (tmp == NULL) { 
        printf("Error of memory");
        return NULL; }
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}


void DeleteList(DblLinkedList* list) {
    Node* tmp = (list)->head;
    Node* next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(list);

}

int AddData(DblLinkedList* list, int data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL||list==NULL) {
        return !NULL;
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
    return NULL;
}

//int popFront(DblLinkedList* list) {
//    Node* prev;
//    int tmp;
//    if (list->head == NULL) {
//        exit(2);
//    }
//
//    prev = list->head;
//    list->head = list->head->next;
//    if (list->head) {
//        list->head->prev = NULL;
//    }
//    if (prev == list->tail) {
//        list->tail = NULL;
//    }
//    tmp = prev->value;
//    free(prev);
//
//    list->size--;
//    return tmp;
//}


static void pushBack(DblLinkedList* list, int value) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

//int popBack(DblLinkedList* list) {
//    Node* next;
//    int tmp;
//    if (list->tail == NULL) {
//        exit(4);
//    }
//
//    next = list->tail;
//    list->tail = list->tail->prev;
//    if (list->tail) {
//        list->tail->next = NULL;
//    }
//    if (next == list->head) {
//        list->head = NULL;
//    }
//    tmp = next->value;
//    free(next);
//
//    list->size--;
//    return tmp;
//}



static Node* getNth(DblLinkedList* list, size_t index) {
    Node* tmp = NULL;
    size_t i;

    if (index < list->size / 2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    }
    else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
}
static int deleteNth(DblLinkedList* list, size_t index) {
    Node* elm = NULL;
    int tmp;
    elm = getNth(list, index);
    if (elm == NULL) {
        return NULL;
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;

    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }

    free(elm);

    list->size--;

    return tmp;
}


void PrintList(DblLinkedList* list) {
    Node* tmp = list->head;
    while (tmp) {
        printf("%d ", (tmp->value));
        tmp = tmp->next;
    }
    printf("\n");
}
static size_t getMin(DblLinkedList* list, size_t index) {
    Node* tmp = list->head;
    size_t i = 0, MinIndex = 0;
    int min = INT_MAX;


    while (tmp && i < index) {
        if (tmp->value < min)
        {
            MinIndex = i;
            min = tmp->value;
        }
        tmp = tmp->next;
        i++;
    }

    return MinIndex;
}
void SortList(DblLinkedList* list) {
    size_t size, m = 0;
    int tmp = NULL;
    if (list != NULL) {
        size = list->size;
        while (size > 0)
        {
            m = getMin(list, size--);
            tmp = deleteNth(list, m);
            pushBack(list, tmp);
        }
    }
}

