#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct node
{
    int key[3];
    int size;
    struct node *(child[4]);
    struct node *parent;
} node;

node *InitNode(int k, node *c1, node *c2, node *c3, node *p){
    node *node;

    if(k < 0) return NULL;

    node = malloc(sizeof(node));
    if(node != NULL){
        node->key[0] = k;
        node->key[1] = -1;
        node->key[2] = -1;
        node->size = 1;
        node->child[0] = c1;
        node->child[1] = c2;
        node->child[2] = c3;
        node->child[3] = NULL;
        node->parent = p;
    }
    
    return node;
}

static void swap(int *x, int *y) {
    int r = *x;
    *x = *y;
    *y = r;
}

static void sort2(int *x, int *y) {   
    if (*x > *y) swap(x, y);
}

static void sort3(int *x, int *y, int *z) {
    if (*x > *y) swap(x, y);
    if (*x > *z) swap(x, z);
    if (*y > *z) swap(y, z);
}

static void sort(node *node) {
    if (node->size == 1) return;
    if (node->size == 2) sort2(&(node->key[0]), &(node->key[1]));
    if (node->size == 3) sort3(&(node->key[0]), &(node->key[1]), &(node->key[2]));
}

bool find(node *node, int k) {
    for (int i = 0; i < node->size; ++i)
        if (node->key[i] == k) return true;
    return false;
}

void insertNode(node *node, int k) {
    node->key[node->size] = k;
    node->size++;
    sort(node);
}

void removeNode(node *node, int k) {
    if (node->size >= 1 && node->key[0] == k) {
        node->key[0] = node->key[1];
        node->key[1] = node->key[2];
        node->size--;
    } else if (node->size == 2 && node->key[1] == k) {
        node->key[1] = node->key[2];
        node->size--;
    }
}

node *split(node *item) {
    if (item->size < 3) return item;

    node *x = InitNode(item->key[0], item->child[0], item->child[1], NULL, item->parent);
    node *y = InitNode(item->key[2], item->child[2], item->child[3], NULL, item->parent);
    if (x->child[0])  x->child[0]->parent = x;
    if (x->child[1]) x->child[1]->parent = x;
    if (y->child[0])  y->child[0]->parent = y;
    if (y->child[1]) y->child[1]->parent = y;

    if (item->parent) {
        insertNode(item->parent,item->key[1]);

        if (item->parent->child[0] == item) item->parent->child[0] = NULL;
        else if (item->parent->child[1] == item) item->parent->child[1] = NULL;
        else if (item->parent->child[2] == item) item->parent->child[2] = NULL;

        if (item->parent->child[0] == NULL) {
            item->parent->child[3] = item->parent->child[2];
            item->parent->child[2] = item->parent->child[1];
            item->parent->child[1] = y;
            item->parent->child[0] = x;
        } else if (item->parent->child[1] == NULL) {
            item->parent->child[3] = item->parent->child[2];
            item->parent->child[2] = y;
            item->parent->child[1] = x;
        } else {
            item->parent->child[3] = y;
            item->parent->child[2] = x;
        }

        node *tmp = item->parent;
        free(item);
        return tmp;
    } else {
        x->parent = item;
        y->parent = item;

        item->key[0] = item->key[1];
        item->child[0] = x;
        item->child[1] = y;
        item->child[2] = NULL;
        item->child[3] = NULL;
        item->parent = NULL;
        item->size = 1;
        return item;
    }
}

static node *search_min(node *p) { // Поиск узла с минимальным элементов в 2-3-дереве с корнем p.
    if (!p) return p;
    if (!(p->child[0])) return p;
    else return search_min(p->child[0]);
}

static node *redistribute(node *leaf) {
    node *parent = leaf->parent;
    node *first = parent->child[0];
    node *second = parent->child[1];
    node *third = parent->child[2];

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->child[0] = parent->child[1];
            parent->child[1] = parent->child[2];
            parent->child[2] = NULL;
            insertNode(parent->child[0],parent->key[0]);
            parent->child[0]->child[2] = parent->child[0]->child[1];
            parent->child[0]->child[1] = parent->child[0]->child[0];

            if (leaf->child[0] != NULL) parent->child[0]->child[0] = leaf->child[0];
            else if (leaf->child[1] != NULL) parent->child[0]->child[0] = leaf->child[1];

            if (parent->child[0]->child[0] != NULL) parent->child[0]->child[0]->parent = parent->child[0];

            removeNode(parent, parent->key[0]);
            free(first);
        } else if (second == leaf) {
            insertNode(first, parent->key[0]);
            removeNode(parent, parent->key[0]);
            if (leaf->child[0] != NULL) first->child[2] = leaf->child[0];
            else if (leaf->child[1] != NULL) first->child[2] = leaf->child[1];

            if (first->child[2] != NULL) first->child[2]->parent = first;

            parent->child[1] = parent->child[2];
            parent->child[2] = NULL;

            free(second);
        } else if (third == leaf) {
            insertNode(second, parent->key[1]);
            parent->child[2] = NULL;
            removeNode(parent, parent->key[1]);
            if (leaf->child[0] != NULL) second->child[2] = leaf->child[0];
            else if (leaf->child[1] != NULL) second->child[2] = leaf->child[1];

            if (second->child[2] != NULL)  second->child[2]->parent = second;
            
            free(third);
        }
    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->child[0] != NULL) {
                leaf->child[1] = leaf->child[0];
                leaf->child[0] = NULL;
            }

            insertNode(leaf, parent->key[1]);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                removeNode(second, second->key[1]);
                leaf->child[0] = second->child[2];
                second->child[2] = NULL;
                if (leaf->child[0] != NULL) leaf->child[0]->parent = leaf;
            } else if (first->size == 2) {
                parent->key[1] = second->key[0];
                leaf->child[0] = second->child[1];
                second->child[1] = second->child[0];
                if (leaf->child[0] != NULL) leaf->child[0]->parent = leaf;

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                removeNode(first, first->key[1]);
                second->child[0] = first->child[2];
                if (second->child[0] != NULL) second->child[0]->parent = second;
                first->child[2] = NULL;
            }
        } else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->child[0] == NULL) {
                    leaf->child[0] = leaf->child[1];
                    leaf->child[1] = NULL;
                }
                insertNode(second, parent->key[1]);
                parent->key[1] = third->key[0];
                removeNode(third, third->key[0]);
                second->child[1] = third->child[0];
                if (second->child[1] != NULL) second->child[1]->parent = second;
                third->child[0] = third->child[1];
                third->child[1] = third->child[2];
                third->child[2] = NULL;
            } else if (first->size == 2) {
                if (leaf->child[1] == NULL) {
                    leaf->child[1] = leaf->child[0];
                    leaf->child[0] = NULL;
                }
                insertNode(second, parent->key[0]);
                parent->key[0] = first->key[1];
                removeNode(first, first->key[1]);
                second->child[0] = first->child[2];
                if (second->child[0] != NULL) second->child[0]->parent = second;
                first->child[2] = NULL;
            }
        } else if (first == leaf) {
            if (leaf->child[0] == NULL) {
                leaf->child[0] = leaf->child[1];
                leaf->child[1] = NULL;
            }
            insertNode(first, parent->key[0]);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                removeNode(second, second->key[0]);
                first->child[1] = second->child[0];
                if (first->child[1] != NULL) first->child[1]->parent = first;
                second->child[0] = second->child[1];
                second->child[1] = second->child[2];
                second->child[2] = NULL;
            } else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                removeNode(third, third->key[0]);
                first->child[1] = second->child[0];
                if (first->child[1] != NULL) first->child[1]->parent = first;
                second->child[0] = second->child[1];
                second->child[1] = third->child[0];
                if (second->child[1] != NULL) second->child[1]->parent = second;
                third->child[0] = third->child[1];
                third->child[1] = third->child[2];
                third->child[2] = NULL;
            }
        }
    } else if (parent->size == 1) {
        insertNode(leaf, parent->key[0]);

        if (first == leaf && second->size == 2) {
            parent->key[0] = second->key[0];
            removeNode(second, second->key[0]);

            if (leaf->child[0] == NULL) leaf->child[0] = leaf->child[1];

            leaf->child[1] = second->child[0];
            second->child[0] = second->child[1];
            second->child[1] = second->child[2];
            second->child[2] = NULL;
            if (leaf->child[1] != NULL) leaf->child[1]->parent = leaf;
        } else if (second == leaf && first->size == 2) {
            parent->key[0] = first->key[1];
            removeNode(first, first->key[1]);

            if (leaf->child[1] == NULL) leaf->child[1] = leaf->child[0];

            leaf->child[0] = first->child[2];
            first->child[2] = NULL;
            if (leaf->child[0] != NULL) leaf->child[0]->parent = leaf;
        }
    }
    return parent;
}

static node *fix(node *leaf) {
    if (leaf->size == 0 && leaf->parent == NULL) { // Случай 0, когда удаляем единственный ключ в дереве
        free(leaf);
        return NULL;
    }
    if (leaf->size != 0) { // Случай 1, когда вершина, в которой удалили ключ, имела два ключа
        if (leaf->parent) return fix(leaf->parent);
        else return leaf;
    }

    node *parent = leaf->parent;
    if (parent->child[0]->size == 2 || parent->child[1]->size == 2 || parent->size == 2)
        leaf = redistribute(leaf);
    else if (parent->size == 2 && parent->child[2]->size == 2) 
        leaf = redistribute(leaf);
    else
    {
        node *parent = leaf->parent;

        if (parent->child[0] == leaf) {
            insertNode(parent->child[1], parent->key[0]);
            parent->child[1]->child[2] = parent->child[1]->child[1];
            parent->child[1]->child[1] = parent->child[1]->child[0];

            if (leaf->child[0] != NULL) parent->child[1]->child[0] = leaf->child[0];
            else if (leaf->child[1] != NULL) parent->child[1]->child[0] = leaf->child[1];

            if (parent->child[1]->child[0] != NULL) parent->child[1]->child[0]->parent = parent->child[1];

            removeNode(parent, parent->key[0]);
            free(parent->child[0]);
            parent->child[0] = NULL;
        } else if (parent->child[1] == leaf) {
            insertNode(parent->child[0], parent->key[0]);

            if (leaf->child[0] != NULL) parent->child[0]->child[2] = leaf->child[0];
            else if (leaf->child[1] != NULL) parent->child[0]->child[2] = leaf->child[1];

            if (parent->child[0]->child[2] != NULL) parent->child[0]->child[2]->parent = parent->child[0];

            removeNode(parent, parent->key[0]);
            free(parent->child[1]);
            parent->child[1] = NULL;
        }

        if (parent->parent == NULL) {
            node *tmp = NULL;
            if (parent->child[0] != NULL) tmp = parent->child[0];
            else tmp = parent->child[1];
            tmp->parent = NULL;
            free(parent);
            return tmp;
        }
        leaf = parent;
    }
    return fix(leaf);
}

node *search(node *p, int k) {
    if (!p) return NULL;

    if (find(p,k)) return p;
    else if (k < p->key[0]) return search(p->child[0], k);
    else if ((p->size == 2) && (k < p->key[1]) || (p->size == 1)) return search(p->child[1], k);
    else if (p->size == 2) return search(p->child[2], k);
}

node *addElem(node *p, int k) { 
    if (!p) return  InitNode(k,NULL,NULL,NULL,NULL); 

    if ((p->child[0] == NULL) && (p->child[1] == NULL) && (p->child[2] == NULL)) insertNode(p,k);
    else if (k <= p->key[0]) addElem(p->child[0], k);
    else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1])) addElem(p->child[1], k);
    else addElem(p->child[2], k);

    return split(p);
}

node *removElem(node *p, int k) {
    node *item = search(p, k);

    if (!item) return p;

    node *min = NULL;
    if (item->key[0] == k) min = search_min(item->child[1]); // Ищем эквивалентный ключ
    else min = search_min(item->child[2]);

    if (min) { // Меняем ключи местами
        int *z = (k == item->key[0] ? &(item->key[0]) : &(item->key[1]));
        swap(z, &(min->key[0]));
        item = min; // Перемещаем указатель на лист, т.к. min - всегда лист
    }

    removeNode(item, k); // И удаляем требуемый ключ из листа
    return fix(item); // Вызываем функцию для восстановления свойств дерева.
}

int main(void){
    node *tree = NULL;
    char ch = getchar();
    int key;

    while ( ch != EOF ){
        scanf("%d", &key);
        switch ( ch ) {
        case 'a':
            tree = addElem(tree, key);
            break;
        case 'r':
            tree = removElem(tree, key);
            break;
        case 'f':
            if (search(tree, key) != NULL)
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