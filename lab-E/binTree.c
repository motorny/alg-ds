#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#define ERROR -1

typedef struct tree {
    struct tree* left;
    struct tree* right;
    int num;
    struct tree* parent;
} tree_t;

tree_t* add(int a, tree_t* root) {
    tree_t* MyTree;
    if (root == NULL) {
        MyTree = (tree_t*)malloc(sizeof(tree_t));
        if (!MyTree) return ERROR;
        MyTree->right = NULL;
        MyTree->left = NULL;
        MyTree->parent = NULL;
        MyTree->num = a;
        root = MyTree;
    }
    else {
        MyTree = root;
        while (MyTree)
            if (a == MyTree->num) {
                break;
            }
            else if (a < MyTree->num) {
                if (MyTree->left)

                    MyTree = MyTree->left;
                else {
                    MyTree->left = (tree_t*)malloc(sizeof(struct tree));
                    if (!MyTree->left) return ERROR;
                    MyTree->left->num = a;
                    MyTree->left->parent = MyTree;
                    MyTree->left->left = NULL;
                    MyTree->left->right = NULL;
                    break;
                }
            }
            else {
                if (MyTree->right)
                    MyTree = MyTree->right;
                else {
                    MyTree->right = (tree_t*)malloc(sizeof(struct tree));
                    if (!MyTree->right) return ERROR;
                    MyTree->right->num = a;
                    MyTree->right->parent = MyTree;
                    MyTree->right->left = NULL;
                    MyTree->right->right = NULL;
                    break;
                }
            }
    }
    return root;
}

int find(int a, tree_t* root) {
    if (!root) { return 0; }
    else {
        if (a == root->num) {
            return 1;
        }
        else {
            if (a < root->num) { return find(a, root->left); }
            else if (a > root->num) {
                return find(a, root->right);
            }
            else  return 0;


        }
    }
}


tree_t* del(int a, tree_t* root) {

    if (!root) {
        return NULL;
    }
    else {
        if (a == root->num) {
            if ((root->left == NULL) && (root->right == NULL)) {//simple
                if (root->parent) {
                    if (root->parent->left == root)
                        root->parent->left = NULL;
                    else
                        root->parent->right = NULL;
                }
                free(root);
                root = NULL;
            }
            else if ((root->right != NULL) && (root->left != NULL)) {
                int max = root->left->num;
                tree_t* tmp = root->left;
                while (tmp->right != NULL) {
                    if (max < tmp->right->num) {
                        max = tmp->right->num;
                    }
                    tmp = tmp->right;
                }
                del(max, root->left);
                root->num = max;
            }
            else if (root->left == NULL) {
                if (root->parent) {
                    if (root->parent->left == root) {
                        root->parent->left = root->right;
                        root->right->parent = root->parent;
                    }
                    else {
                        root->parent->right = root->right;
                        root->right->parent = root->parent;
                    }
                    free(root);
                    root = NULL;
                }
                else {
                    root->right->parent = NULL;
                    tree_t* tmp = root;
                    root = root->right;
                    free(tmp);

                }
            }
            else {
                if (root->parent) {
                    if (root->parent->left == root) {
                        root->parent->left = root->left;
                        root->left->parent = root->parent;
                    }
                    else {
                        root->parent->right = root->left;

                        root->left->parent = root->parent;
                    }
                    free(root);
                    root = NULL;
                }
                else {
                    root->left->parent = NULL;
                    tree_t* tmp = root;
                    root = root->left;
                    free(tmp);

                }
            }


        }
        else {
            if (a < root->num) {
                del(a, root->left);
            }
            else {
                del(a, root->right);
            }
        }
    }



    return root;
}


void deleteTree(tree_t* OneTree) {
    if (OneTree) {
        deleteTree(OneTree->left);
        deleteTree(OneTree->right);
        printf("%d ", OneTree->num);
        free(OneTree);
    }
}


int recurs(tree_t* root) {
    if (!root->left && root->right)
        root->num = recurs(root->right) + 1;
    else if (root->left && !root->right)
        root->num = recurs(root->left) + 1;
    else if (!root->left && !root->right)
        root->num = 0;

    else root->num = (recurs(root->left) < recurs(root->right) ? recurs(root->left) : recurs(root->right)) + 1;
    return root->num;


}

int main(int argc, char*argv[]) {
    /* tree_t* root = NULL;

     char c, operation, number[255];
     int index = 0, data;

     c = getchar();
     while (c != EOF) {
         operation = c;
         c = getchar();
         while (isspace(c)) {
             c = getchar();
         }
         while (isdigit(c)) {
             number[index++] = c;
             c = getchar();
         }
         number[index] = '\0';
         data = atoi(number);
         index = 0;
         switch (operation) {
         case 'a': {
             root = add(data, root);
             break;
         }
         case 'r': {
             root = del(data, root);
             break;
         }
         case 'f': {
             if (find(data, root)) {
                 printf("yes\n");
             }
             else {
                 printf("no\n");
             }
             break;
         }
         case 'n': {
             recurs(root);
             deleteTree(root);
             exit(0);
         }

         default: {
             deleteTree(root);
             return 0;
         }

         }

         if (c == '\n') {
             c = getchar();
         }

     }
       */
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(E3, recursWithOnlyValue) {

tree_t* root=NULL;
root=add(1, root);
recurs(root);
EXPECT_TRUE(root->num == 0);
deleteTree(root);
}

TEST(E3, recursExpectCorrectValue) {

tree_t* root = NULL;
root = add(1, root);
root = add(3, root);
root = add(2, root);
root = add(5, root);
root = add(4, root);

recurs(root);
EXPECT_TRUE(root->num == 2);
EXPECT_TRUE(root->right->num == 1);
EXPECT_TRUE(root->right->right->left->num == 0);
EXPECT_TRUE(root->right->right->num == 1);
EXPECT_TRUE(root->right->left->num == 0);
deleteTree(root);
}
