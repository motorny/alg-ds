//#include "vld.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define K 3
enum Color
{
BLACK,RED
};
enum DIRECTION {
    LEFT,RIGHT
};
/* структура, описывающая узел красно-черного дерева */
struct rb_node
{
   enum Color color;
    int data;
    struct rb_node* link[2];
};

 int colorOfNode(struct rb_node* node)
 {
     return node != NULL && node->color == RED;
 }
 /* функция для однократного поворота узла */
 struct rb_node* rb_single(struct rb_node* root, enum DIRECTION dir)
 {
     struct rb_node* save = root->link[!dir];

     root->link[!dir] = save->link[dir];
     save->link[dir] = root;

     root->color = RED;
     save->color = BLACK;

     return save;
 }

 /* функция для двукратного поворота узла */
 struct rb_node* rb_double(struct rb_node* root, enum DIRECTION dir)
 {
     root->link[!dir] = rb_single(root->link[!dir], (enum DIRECTION)!dir);
     return rb_single(root, dir);
 }
 struct rb_node* makeLeaf(int data)
 {
     struct rb_node* rn =(struct rb_node*) malloc(sizeof(struct rb_node));

     if (rn != NULL) { 
         rn->data = data;
         rn->color = RED; /* –инициализация красным цветом */
         rn->link[0] = NULL;
         rn->link[1] = NULL;
     }
     return rn;
 }
 int add(struct rb_node** root, int data)
 {
     struct rb_node* tree = *root;
     /* если добавляемый элемент оказывается корнем– то ничего делать не нужно*/
     if (tree == NULL) {
         tree = makeLeaf(data);
         if (tree == NULL)
             return ERROR;
     }
     else {
         struct rb_node head = { BLACK }; /* временный корень дерева*/
         struct rb_node* g = NULL;     //  дедушка
         struct rb_node*t = &head;      
         struct rb_node* p = NULL;     // родитель
         struct rb_node*q = t->link[1] = tree;     // итератор 
         /*изначально корень дерева это правый потомок временного корня*/
         int dir = LEFT, last;

         /* основной цикл прохода по дереву */
         for (;;)
         {
             if (q == NULL) {
                 /* вставка  */
                 p->link[dir] = q = makeLeaf(data);
               
                 if (q == NULL)
                     return 0;
             }
             else if (colorOfNode(q->link[0]) && colorOfNode(q->link[1]))  
             {
                 /* смена цвета */
                 q->color = RED;
                 q->link[0]->color = BLACK;
                 q->link[1]->color = BLACK;
             }
             /* совпадение 2-х красных цветов */
             if (colorOfNode(q) && colorOfNode(p))
             {
                 int dir2 = t->link[1] == g;
                 if (!p)
                     return ERROR;
                 if (q == p->link[last])
                     t->link[dir2] = rb_single(g, (enum DIRECTION)!last);
                 else
                     t->link[dir2] = rb_double(g, (enum DIRECTION)!last);
             }

             /* такой узел в дереве уже есть  - выход из функции*/
             if (q->data == data)
             {
                 break;
             }

             last = dir;
             dir = q->data < data;

             if (g != NULL)
                 t = g;
             g = p, p = q;
             q = q->link[dir];
         }

         /* обновить указатель на корень дерева*/
         tree = head.link[1];
     }
     /* сделать корень дерева черным */
     tree->color = BLACK;
     *root = tree;
     return TRUE;
 }
 int myAdd(struct rb_node** root, int data) {
     struct rb_node* tree = *root;

     *root = tree;
     return 1;
 }
 int removeNode(struct rb_node** root, int data)
 {
     struct rb_node* tree = *root;
     if (tree != NULL)
     {
         struct rb_node head = { BLACK }; /* временный указатель на корень дерева */
         struct rb_node* q, * p, * g; /* вспомогательные переменные */
         struct rb_node* f = NULL;  /* узел, подлежащий удалению */
         int dir = 1;

         /* инициализация вспомогательных переменных */
         q = &head;
         g = p = NULL;
         q->link[1] = tree;

         /* поиск и удаление */
         while (q->link[dir] != NULL) {
             int last = dir;

             /* сохранение иерархии узлов во временные переменные */
             g = p, p = q;
             q = q->link[dir];
             dir = q->data < data;

             /* сохранение найденного узла */
             if (q->data == data)
                 f = q;

             if (!colorOfNode(q) && !colorOfNode(q->link[dir])) {
                 if (colorOfNode(q->link[!dir]))
                     p = p->link[last] = rb_single(q,( enum DIRECTION) dir);
                 else if (!colorOfNode(q->link[!dir])) {
                     struct rb_node* s = p->link[!last];


                     if (s != NULL) {
                         if (!colorOfNode(s->link[!last]) && !colorOfNode(s->link[last])) {
                             /* смена цвета узлов */
                             p->color = BLACK;
                             s->color = RED;
                             q->color = RED;
                         }
                         else {
                             int dir2 = g->link[1] == p;

                             if (colorOfNode(s->link[last]))
                                 g->link[dir2] = rb_double(p, (enum DIRECTION)last);
                             else if (colorOfNode(s->link[!last]))
                                 g->link[dir2] = rb_single(p, (enum DIRECTION)last);

                             /* корректировка цвета узлов */
                             q->color = g->link[dir2]->color = RED;
                             g->link[dir2]->link[0]->color = BLACK;
                             g->link[dir2]->link[1]->color = BLACK;
                         }
                     }
                 }
             }
         }

         /* удаление найденного узла */
         if (f != NULL) {
             f->data = q->data;
             p->link[p->link[1] == q] =
                 q->link[q->link[0] == NULL];
             free(q);
         }

         /* обновление указателя на корень дерева */
         tree = head.link[1];
         if (tree != NULL)
             tree->color = BLACK;
     }
     *root = tree;
     return TRUE;
 }
 int br_find(struct rb_node* root,int data) {
     while (root) {
         if (root->data == data)
             return 1;
         else if (data > root->data) {
             root = root->link[1];
         }
         else
             root = root->link[0];
   }
     return 0;
 }
 void freeTree(struct rb_node* root) {
     if (root) {
         freeTree(root->link[0]);
         freeTree(root->link[1]);
     //    printf("%d ", root->data);
         free(root);
     }
 }
 void printTree(struct rb_node* root) {
     if (root) {
         printTree(root->link[0]);
         printTree(root->link[1]);
            printf("%d ", root->data);   
     }
 }


 int main(int argc, char* argv[]) {

     struct rb_node tree;
     struct rb_node* myTree=&tree;
     myTree = NULL;
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
              add(&myTree, data);
             break;
         }
         case 'r':
         {
             removeNode(&myTree, data);
             break;
         }
         case 'f':
         {
             if (br_find(myTree, data))
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
             printTree(myTree);
             break;
         }

         }
         if (c == '\n')
         {
             c = getchar();
         }

     }
     freeTree(myTree);

     return  0;
 }
