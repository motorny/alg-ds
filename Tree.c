
#include <stdio.h>
#include <stdlib.h>

 struct tree {
  int num;
  int ord; 
  struct tree* left;
  struct tree* parent;
  struct tree* right;
} ;

 

void AddTo(struct tree* tree, int* ord)
{
  if (tree) 
  {
    if(tree->left)
      AddTo(tree->left, ord);

    tree->ord = *ord;
    (*ord)++;

    if(tree->right)
      AddTo(tree->right, ord);
  }
}


void Add(struct tree** tree, int num)
{
    struct tree* temp = (*tree), * newnode, * ptr = (*tree);
    int ord = 1;
    newnode = (struct tree*)malloc(sizeof(struct tree));
    if (!newnode)
        return;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    newnode->num = num;

    if (!(*tree))
    {
        (*tree) = newnode;
        AddTo((*tree), &ord);
        return;
    }

    while (ptr)
    {
        if (num < ptr->num)
        {
            if (ptr->left)
                ptr = ptr->left;
            else
                break;
        }

        else if (num > ptr->num)
        {
            if (ptr->right)
                ptr = ptr->right;
            else
                break;
        }

        else
        {
            free(newnode);
            return;
        }
    }

    if (num < ptr->num)
        ptr->left = newnode;
    else
        ptr->right = newnode;

    newnode->parent = ptr;

    AddTo((*tree), &ord);
}

struct tree* KNodeFind(struct tree* tree, int k)
{
    struct tree* tmp = NULL;
    if (tree)
    {
        tmp = KNodeFind(tree->right, k);
        if (tmp)
            return tmp;
        if (tree->ord == k)
            return tree;
        tmp = KNodeFind(tree->left, k);
        if (tmp)
            return tmp;
    }
    
    return NULL;
  
}

void DestroyTree(struct tree* tree)
{
  if (tree)
  {
    DestroyTree(tree->left);
    DestroyTree(tree->right);
    free(tree);
  }
}


struct tree* getMax(struct tree* tree)
{
    while (tree->right != NULL)
    {
        tree = tree->right;
    }
    return tree;
}

        
        
void NodeRemove(struct tree** tree, int num)
{
    if (tree == NULL) {
        return;
    }
    if ((*tree) == NULL)
    {
        return;
    }
    if (num < (*tree)->num)
    {
        NodeRemove(&((*tree)->left), num);
    }
    else if (num > (*tree)->num)
    {
        NodeRemove(&((*tree)->right), num);
    }
    else if ((*tree)->left == NULL && (*tree)->right == NULL)
    {
        (*tree) = NULL;
    }
    else if ((*tree)->left != NULL && (*tree)->right == NULL)
    {
        (*tree) = (*tree)->left;
    }
    else
    {
        if ((*tree)->left == NULL && (*tree)->right != NULL)
        {
            (*tree) = (*tree)->right;
        }
        else
        {
            struct tree* max = getMax((*tree)->left);
            (*tree)->num = max->num;
            NodeRemove(&((*tree)->left), max->num);
        }
    }
}







void PrintKTree(struct tree* tree, int level, int k)
{
  if (tree) 
  {
    PrintKTree(tree->left, level + 1, k);
    if (tree->ord < k) 
    {
      for (int i = 0; i < level; i++)
        printf(" ");
      printf("%i\n", tree->num);
    }
    PrintKTree(tree->right, level + 1, k);
  }
}


void PrintTree(struct tree* tree, int level)
{
    if (tree)
    {
        int i;
        PrintTree(tree->left, level + 1);
        for (i = 0; i < level; i++)
            printf("    ");
        printf("%i\n", tree->num);
        PrintTree(tree->right, level + 1);
    }
}


struct tree* FindNode(struct tree* tree, int num) 
{
    while (tree) {
        if (num > tree->num)
        {
            tree = tree->right;
            continue;
        }
        else if (num < tree->num) 
        {
            tree = tree->left;
        }
        else 
        {
            return tree;
        }
    }
    return NULL;
}

int DefineFunc(FILE* file, int* number) {
    char define = getchar();
    if (define == -1)
        return 0;
    fscanf_s(file, " %d", number);
    getchar();
    if (define == 'a')
        return 1;
    else if (define == 'r')
        return 2;
    else if (define == 'f')
        return 3;
    else
        return 0;
}
   

int main(void)
{
  const int k = 4, ONE = 1;
  struct tree* tree = NULL, *find=NULL;
  

  /*Add(&tree, 7);
  Add(&tree, 5);
  Add(&tree, 12);
  Add(&tree, 2);
  Add(&tree, 6);
  Add(&tree, 9);
  Add(&tree, 15);
  NodeRemove(&tree, 5);*/

  int func = 0, number = 0;

  
  func = DefineFunc(stdin, &number);
  if (func == 0)
      return -1;
  do {
      switch (func) {
      case 1:
          Add(&tree, number);
          break;
      case 2:
          NodeRemove(&tree, number);
          break;
      case 3:
          if (FindNode(tree, number) != NULL)
              fprintf(stdout, "yes\n");
          else
              fprintf(stdout, "no\n");
          break;
      default:
          break;
      }
      func = DefineFunc(stdin, &number);
  } while (func != 0);

  find = KNodeFind(tree, k);

  if ( ((find->num) % 2) == 0)
  {
      PrintKTree(tree, ONE, k);
  }
  else
  {
      PrintTree(tree, ONE);
  }
  
  

  DestroyTree(tree);
  return 0;
}