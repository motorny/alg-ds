#include <time.h>
#include <stdlib.h>
#include<stdio.h>
#define ERROR -2



typedef struct Noden{
    int key, priority;
    struct Noden* l;
    struct Noden* r;

} Nodent;

    Nodent* merge(Nodent* a, Nodent* b) {
       
            if (!a || !b)
                return a ? a : b;
            if (a->priority > b->priority) {
                a->r = merge(a->r, b);
                return a;
            }
            else {
                b->l = merge(a, b->l);
                return b;
            }
       
          }



 void split(Nodent*n, int key, Nodent **a, Nodent **b){

     if (!n) {
        if(!(a==NULL))
         *a = NULL;
        if (!(b == NULL))
            *b = NULL;
            return;
        }
        if (n->key<key)
        {

            split(n->r, key, &(n->r), b);
            if (!(a == NULL)) *a = n;
        }
        else {
            split(n->l, key, a, &(n->l));
            if (!(b == NULL))  *b = n;
        }
    }


    void add(Nodent** r, int key) {
        Nodent* root = *r;
        if (root != NULL) {
            Nodent* less = NULL, * greater = NULL;
            split(root, key, less, greater);
            Nodent* tmp = (Nodent*)malloc(sizeof(Nodent));
            tmp->l;
            tmp->r;
            tmp->key = key;
            less = merge(less, tmp);
            root = merge(less, greater);
        }
        else { 
            root = (Nodent*)malloc(sizeof(Nodent));
            root->key = key;
            root->l = NULL;
            root->r = NULL;
            root->priority = rand();
        }
        *r = root;
    }

    int contains(Nodent* root, int key) {
        if (root == NULL) { return 0; }
            Nodent* less = NULL, * greater = NULL, * equal = NULL;
            split(root, key, &less, &greater);
            split(greater, key + 1, &equal, &greater);
            int result = 0;
            if (equal) result = 1;
            root = merge(merge(less, equal), greater);
            return result;
        
    }



    void erase(Nodent* root, int key) {
        Nodent* less=NULL, * greater= NULL, * equal=NULL;
        split(root, key, &less, &greater);
        split(greater, key + 1, &equal, &greater);
        root = merge(less, greater);
    }




    int main()
    {
        Nodent *root=NULL;
        srand(time(NULL));
        int n;
        int prevRes = 0;

        char c, operation, number[255];
        int index = 0, data;

        c = getchar();
        while (c != EOF)
        {
            operation = c;
            c = getchar();
            while (isspace(c))
            {
                c = getchar();
            }
            while (isdigit(c))
            {
                number[index++] = c;
                c = getchar();
            }
            number[index] = '\0';
            data = atoi(number);
            index = 0;
            switch (operation)
            {
            case 'a':
            {
                add(&root, data);
                break;
            }
            case 'r':
            {
                erase(root, data);
                break;
            }
            case 'f':
            {
                if (contains(root, data))
                {
                    printf("yes\n");
                }
                else
                {
                    printf("no\n");
                }
                break;
            }
            default: {
               
            }

            }
            if (c == '\n')
            {
                c = getchar();
            }

        }
        return 0;
    }
