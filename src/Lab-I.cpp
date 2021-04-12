#include <cstdio>
#include <cstdlib>
#include "node.h"

#define def_main int main()

int ReadAction(FILE *fp, int *key) {
    char c, n;
    int check;
    check = fscanf(fp, "%c", &c);
    if (check == -1)
        return 0;

    fscanf(fp, " %d", key);
    fscanf(fp, "%c", &n);

    switch (c) {
        case 'a':
            return 1;
        case 'r':
            return 2;
        case 'f':
            return 3;
        case 'd':
            return 4;
        default:
            return 0;
    }
}

def_main {
    int mode = 0, num = 0;
    mode = ReadAction(stdin, &num);
    if (mode == 0)
        return -1;

    do {
        switch (mode) {
            case 1:
                insert(num);
                break;
            case 2:
                DelNode(num);
                break;
            case 3: {
                search(num);
                break;
            }
            case 4: {
                display(root, 0);
            }
            default:
                break;
        }
        mode = ReadAction(stdin, &num);

    } while (mode != 0);
    return 0;
}

void insert(int key) {
    node *newnode;
    int upKey;
    KeyStatus value;
    value = ins(root, key, &upKey, &newnode);
    if (value == InsertIt) {
        node *uproot = root;
        root = (node *) malloc(sizeof(node));
        root->n = 1;
        root->keys[0] = upKey;
        root->p[0] = uproot;
        root->p[1] = newnode;
    }
}

KeyStatus ins(node *ptr, int key, int *upKey, node **newnode) {
    node *newPtr, *lastPtr;
    int pos, i, n, splitPos;
    int newKey, lastKey;
    KeyStatus value;
    if (ptr == NULL) {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    if (n < 2) {
        pos = searchPos(newKey, ptr->keys, n);
        for (i = n; i > pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
        ++ptr->n;
        if (ptr->n != 2) {
            ptr->p[2] = NULL;
        }
        return Success;
    }

    if (pos == 2) {
        lastKey = newKey;
        lastPtr = newPtr;
    } else {
        lastKey = ptr->keys[1];
        lastPtr = ptr->p[2];
        for (i = 1; i > pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
    }
    splitPos = 1;
    (*upKey) = ptr->keys[splitPos];
    (*newnode) = (node *) malloc(sizeof(node));
    ptr->n = splitPos;
    (*newnode)->n = 2 - splitPos;
    for (i = 0; i < (*newnode)->n; i++) {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if (i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;

}

void display(node *ptr, int blanks) {
    if (ptr) {
        int i;
        for (i = 1; i <= blanks; i++)
            printf(" ");
        for (i = 0; i < ptr->n; i++)
            printf("%d ", ptr->keys[i]);
        printf("\n");
        for (i = 0; i <= ptr->n; i++)
            display(ptr->p[i], blanks + 10);
    }
}

void search(int key) {

    int pos, n;
    node *ptr = root;
    while (ptr) {
        n = ptr->n;
        pos = searchPos(key, ptr->keys, n);
        if (pos < n && key == ptr->keys[pos]) {
            printf("yes\n");
            return;
        }
        ptr = ptr->p[pos];
    }
    printf("no\n");
}

int searchPos(int key, int *key_arr, int n) {

    int pos = 0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}


void DelNode(int key) {

    node *uproot;
    KeyStatus value;
    value = del(root, key);
    switch (value) {
        case SearchFailure:
            break;
        case LessKeys:
            uproot = root;
            root = root->p[0];
            free(uproot);
            break;
        default:
            return;
    }
}

KeyStatus del(node *ptr, int key) {

    int pos, i, pivot, n, min;
    int *key_arr;
    KeyStatus value;
    node **p, *lptr, *rptr;
    if (ptr == NULL)
        return SearchFailure;
    n = ptr->n;
    key_arr = ptr->keys;
    p = ptr->p;
    min = 1;
    pos = searchPos(key, key_arr, n);
    if (p[0] == NULL) {
        if (pos == n || key < key_arr[pos])
            return SearchFailure;
        for (i = pos + 1; i < n; i++) {
            key_arr[i - 1] = key_arr[i];
            p[i] = p[i + 1];
        }
        return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
    }
    if (pos < n && key == key_arr[pos]) {
        node *qp = p[pos], *qp1;
        int nkey;
        while (1) {
            nkey = qp->n;
            qp1 = qp->p[nkey];
            if (qp1 == NULL)
                break;
            qp = qp1;
        }
        key_arr[pos] = qp->keys[nkey - 1];
        qp->keys[nkey - 1] = key;
    }

    value = del(p[pos], key);
    if (value != LessKeys)
        return value;

    if (pos > 0 && p[pos - 1]->n > min) {
        pivot = pos - 1;
        lptr = p[pivot];
        rptr = p[pos];
        rptr->p[rptr->n + 1] = rptr->p[rptr->n];
        for (i = rptr->n; i > 0; i--) {
            rptr->keys[i] = rptr->keys[i - 1];
            rptr->p[i] = rptr->p[i - 1];
        }
        rptr->n++;
        rptr->keys[0] = key_arr[pivot];
        rptr->p[0] = lptr->p[lptr->n];
        key_arr[pivot] = lptr->keys[--lptr->n];
        return Success;
    }

    if (pos < n && p[pos + 1]->n > min) {
        pivot = pos;
        lptr = p[pivot];
        rptr = p[pivot + 1];
        lptr->keys[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        key_arr[pivot] = rptr->keys[0];
        lptr->n++;
        rptr->n--;
        for (i = 0; i < rptr->n; i++) {
            rptr->keys[i] = rptr->keys[i + 1];
            rptr->p[i] = rptr->p[i + 1];
            rptr->p[rptr->n] = rptr->p[rptr->n + 1];
            return Success;
        }

        if (pos == n)
            pivot = pos - 1;
        else
            pivot = pos;
        lptr = p[pivot];
        rptr = p[pivot + 1];
        lptr->keys[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        for (i = 0; i < rptr->n; i++) {
            lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
            lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
        }
        lptr->n = lptr->n + rptr->n + 1;
        free(rptr);
        for (i = pos + 1; i < n; i++) {
            key_arr[i - 1] = key_arr[i];
            p[i] = p[i + 1];
        }
        return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
    }
}

void inorder(node *ptr) {
    if (ptr) {
        if (ptr->n >= 1) {
            inorder(ptr->p[0]);
            printf("%d ", ptr->keys[0]);
            inorder(ptr->p[1]);
            if (ptr->n == 2) {
                printf("%d ", ptr->keys[1]);
                inorder(ptr->p[2]);
            }
        }
    }
}