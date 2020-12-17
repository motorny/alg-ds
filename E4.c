#include <stdio.h>
#include <stdlib.h>


typedef enum {
  NONE = 0,
  LEFT = 1,
  RIGHT = 2
}way_t;


typedef struct tree_t {
  char* word;
  int len;
  struct tree_t* left;
  struct tree_t* right;
  struct tree_t* parent;
  int WigthOfSubtree;
} tree_t;



void Append(tree_t** tree, char* buff) {
  tree_t* tmp = (*tree);
  tree_t* new;
  tree_t* ptr = (*tree);
  int num = 0, i, subtreelength;

  new = (tree_t*)malloc(sizeof(tree_t));
  if (!new)
    return;

  while (buff[num] != '\0')
    num++;

  new->left = NULL;
  new->right = NULL;
  new->parent = NULL;
  new->len = num;
  new->WigthOfSubtree = 0;
  new->len = num;

  new->word = (char*)malloc((num + 1) * sizeof(char));
  if (!new->word)
    return;

  for (i = 0; i <= num; i++)
    new->word[i] = buff[i];

  if (!(*tree)) {
    (*tree) = new;
    return;
  }

  while (ptr) {
    if (num < ptr->len) {
      if (ptr->left)
        ptr = ptr->left;
      else
        break;
    }

    else if (num > ptr->len) {
      if (ptr->right)
        ptr = ptr->right;
      else
        break;
    }

    else {
      free(new);
      return;
    }
  }


  if (num < ptr->len)
    ptr->left = new;
  else
    ptr->right = new;

  new->parent = ptr;


  subtreelength = 0;
  tmp = new;
  while (tmp->parent) {
    tmp = tmp->parent;
    tmp->WigthOfSubtree += num;
  }
}


tree_t* Find(tree_t* tree, char* buff) {
  tree_t* tmp = tree;

  int num = 0, i;
  while (buff[num] != '\0')
    num++;

  while (tmp) {

    if (num < tmp->len)
      tmp = tmp->left;

    else if (num > tmp->len)
      tmp = tmp->right;

    else {
      for (i = 0; i < num; ++i) {
        if (tmp->word[i] != buff[i])
          return NULL;
      }

      return tmp;
    }
  }

  return NULL;
}


void Delete(tree_t** tree, tree_t* vert) {
  if (!vert)
    return;

  int temp, i;
  tree_t* max = vert; 
  tree_t* parent; 
  tree_t* child; 
  tree_t* tmp2; 
  way_t pway;
  char* help;

  if (vert->left == NULL && vert->right == NULL) {
    if ((vert == (*tree))) {
      free(vert->word);
      free(vert);
      (*tree) = NULL;
      return;
    }

    parent = vert->parent;
    if (parent->left == vert)
      pway = LEFT;
    else
      pway = RIGHT;

    if (pway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;

    tmp2 = vert;

    while (tmp2->parent) {
      tmp2 = tmp2->parent;
      tmp2->WigthOfSubtree -= vert->len;
    }

    free(vert->word);
    free(vert);

    return;
  }


  if ((vert->left != NULL && vert->right == NULL) || (vert->left == NULL && vert->right != NULL)) {

    if (vert == (*tree)) {
      if (vert->left)
        (*tree) = vert->left;
      else
        (*tree) = vert->right;
      (*tree)->parent = NULL;
      free(vert);
      return;
    }

    parent = vert->parent;
    if (parent->left == vert)
      pway = LEFT;
    else
      pway = RIGHT;

    if (vert->left)
      child = vert->left;
    else 
      child = vert->right;

    child->parent = vert->parent;

    if (pway == LEFT)
      parent->left = child;
    else
      parent->right = child;


    tmp2 = vert;
    while (tmp2->parent) {
      tmp2 = tmp2->parent;
      tmp2->WigthOfSubtree -= vert->len;
    }

    free(vert->word);
    free(vert);
    return;
  }


  max = max->right;

  while (max->left)
    max = max->left;

  temp = max->len;
  max->len = vert->len;
  vert->len = temp;

  help = (char*)realloc(vert->word, (max(vert->len, max->len) + 1) * sizeof(char));
  if (help) {
    vert->word = help;
    help = NULL;
  }
  else {
    free(vert->word);
    return;
  }

  for (i = 0; i <= max(vert->len, max->len); ++i)
    vert->word[i] = max->word[i];

  tmp2 = max;
  while (tmp2->parent != vert->parent) {
    tmp2 = tmp2->parent;
    tmp2->WigthOfSubtree += (max->len - vert->len);
  }


  if (max->right) {
    child = max->right;
    parent = max->parent;
    if (parent->left == max)
      pway = LEFT;
    else
      pway = RIGHT;

    if (pway == LEFT)
      parent->left = child;
    else
      parent->right = child;

    child->parent = parent;
  }


  else {
    parent = max->parent;
    if (parent->left == max)
      pway = LEFT;
    else
      pway = RIGHT;

    if (pway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;
  }

  tmp2 = max;
  while (tmp2->parent) {
    tmp2 = tmp2->parent;
    tmp2->WigthOfSubtree -= max->len;
  }

  free(max->word);
  free(max);
  return;
}


void Print(tree_t* tree, int level) {

  if (tree) {
    int i;
    Print(tree->left, level + (tree->len));
    for (i = 0; i < level; i++)
      printf("   ");

    for (i = 0; i < tree->len; ++i)
      printf("%c", tree->word[i]);

    printf("\n");
    for (i = 0; i < level; i++)
      printf("   ");
    printf("%i\n", tree->len);

    for (i = 0; i < level; i++)
      printf("   ");
    printf("%i\n", tree->WigthOfSubtree);

    Print(tree->right, level + (tree->len));
  }
}


void DestroyTree(tree_t* tree) {

  if (tree) {
    DestroyTree(tree->left);
    DestroyTree(tree->right);
    free(tree->word);
    free(tree);
  }
}


int main(void) {
  tree_t* tree = NULL;
  const int ONE = 1;

  Append(&tree, "Lab");
  Append(&tree, "Destroy");
  Append(&tree, "Polytech");
  Append(&tree, "c");
  Append(&tree, "tree");
  Delete(&tree, Find(tree, "tree"));

  Print(tree, ONE);

  DestroyTree(tree);
  return 0;
}