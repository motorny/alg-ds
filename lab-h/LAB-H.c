#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treap
{
    int x, y;
    struct treap *left, *right;
}treap;

void split(treap *t, int k, treap **t1, treap **t2){
    if (t == NULL) {
        *t1 = *t2 = NULL;
        return;
    }
    else if (k > t->x) {
        treap *T1, *T2;
        split(t->right, k, &T1, &T2);
        t->right = T1;
        *t1 = t;
        *t2 = T2;
        return;
    }
    else {
        treap *T1, *T2;
        split(t->left, k, &T1, &T2);
        t->left = T2;
        *t1 = T1;
        *t2 = t;
        return;
    }
}

treap *merge(treap *t1, treap *t2){
    if (t2 == NULL)
    {
        return t1;
    }
    else if (t1 == NULL)
    {
        return t2;
    }
    else if (t1->y > t2->y)
    {
        t1->right = merge(t1->right, t2);
        return t1;
    }
    else
    {
        t2->left = merge(t1, t2->left);
        return t2;
    }
}

treap *insertKey(treap *t, treap *k){
    if(t == NULL) return k;
    if(k == NULL) return t;
    
    treap *t1 = NULL, *t2 = NULL;
    split(t, k->x, &t1, &t2);
    t = merge(merge(t1,k),t2);
    return t;
}

treap *removeKey(treap *t, int x){
    if(t == NULL) return NULL;
    if (t->x > x)
    {
        t->left = removeKey(t->left, x);
        return t;
    }
    else if (t->x < x)
    {
        t->right = removeKey(t->right, x);
        return t;
    }
    else
    {
        treap *tr = merge(t->left, t->right);
        free(t);
        return tr;
    }    
}

treap *creatNode(int k){
    static int priority = 1;
    treap *t = (treap*)malloc(sizeof(treap));
    if (t)
    {
        t->x = k;
        t->y = priority++;
        t->left = t->right = NULL;
    }

    return t;    
}

treap *search(treap *t, int k){
    treap *t1 = NULL, *t2 = NULL, *cur = NULL;
	split(t, k, &t1, &t2);
	split(t2, k + 1, &cur, &t2);
	t = merge(merge(t1, cur), t2);

    return cur;    
}


#ifndef GTEST

int main(void){
    treap *tree = NULL;
    char ch = getchar();
    int key;

    while ( ch != EOF ){
        scanf("%d", &key);
        switch ( ch ) {
        case 'a':
            tree = insertKey(tree, creatNode(key));
            break;
        case 'r':
            tree = removeKey(tree, key);
            break;
        case 'f':
            if ( search(tree, key) )
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            return 0;
        }

        ch = getchar();
        if ( ch == '\r' )
            ch = getchar();
        if ( ch == '\n' )
            ch = getchar();
    }

    return 0;
}

#endif // !GTEST