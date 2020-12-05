#include <stdio.h>
#include <stdlib.h>

typedef struct tree_t {
  int num; //length of word
  struct tree_t* left;
  struct tree_t* parent;
  struct tree_t* right;
  int subtreeWigth; //sum of word lengths of sons,grandsons, etc. until leaves
  char* word;
} tree_t;

typedef enum {
  NONE = 0,
  LEFT = 1,
  RIGHT = 2
}way_t;


//length of words different, so parametr of creating binary tree will be length

void NodeAppend1(tree_t** tree, char* buff) {
  tree_t* temp = (*tree), * parent = NULL;
  way_t way = NONE;
  int num = 0, i;
  
  int subtreelength = 0;

  //length
  while (buff[num] != '\0')
    num++;

  //create tree
  if ((*tree) == NULL) {
    (*tree) = (tree_t*)malloc(sizeof(tree_t));
    if (!(*tree))
      return;

    (*tree)->num = num;
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->parent = NULL;
    (*tree)->subtreeWigth = 0;

    (*tree)->word = (char*)malloc((num + 1) *sizeof(char));
    if (!(*tree)->word)
      return;

    for (i = 0; i < num; ++i)
      (*tree)->word[i] = buff[i];

    (*tree)->word[num] = '\0';
    return;
  }


  parent = *tree;
  //go to child once to put temp2 pointer on parent to put pointers later
  if (num < temp->num) {
    if (temp->left)
      temp = temp->left;
    else//remember where must go
      way = LEFT;
  }
  //go to child once to put temp2 pointer on parent to put pointers later
  else if (num > temp->num) {
    if (temp->right)
      temp = temp->right;
    else
      way = RIGHT;
  }

  while (way == NONE && temp && temp->num != num) {
    parent = temp;

    if (num < temp->num) {

      if (temp->left) {
        parent = temp;
        temp = temp->left;
      }
      else {//remember where must go
        way = LEFT;
        break;
      }
    }

    else if (num > temp->num) {

      if (temp->right) {
        parent = temp;
        temp = temp->right;
      }
      else {
        way = RIGHT;
        break;
      }
    }

  }

  //vertex exists, do nothing
  if (temp && temp->num == num)
    return;

  //temp is empty, create node
  if (way == LEFT) {
    temp->left = (tree_t*)malloc(sizeof(tree_t));
    if (!temp->left)
      return;

    temp = temp->left;
  }
  else if (way == RIGHT) {
    temp->right = (tree_t*)malloc(sizeof(tree_t));
    if (!temp->right)
      return;
    temp = temp->right;
  }

  temp->num = num;
  temp->left = NULL;
  temp->parent = parent;
  temp->right = NULL;
  temp->subtreeWigth = 0; //list

  temp->word = (char*)malloc((num+1) * sizeof(char));
  if (!temp->word)
    return;

  //<= cause enough memory for '\0'
  for (i = 0; i <= num; ++i)
    temp->word[i] = buff[i];

  temp->word[num] = '\0';
  //update subtreelengths. go from temp(is list) to root
  subtreelength = 0;
  while (temp->parent) {
    temp = temp->parent;
    temp->subtreeWigth += num;
  }
}

void DestroyTree1(tree_t* tree) {
  if (tree) {
    DestroyTree1(tree->left);
    DestroyTree1(tree->right);
    free(tree->word);
    free(tree);
  }
}

tree_t* NodeFind1(tree_t* tree, char* buff) {
  tree_t* temp = tree;

  int num=0, i;
  while (buff[num] != '\0')
    num++;

  while (temp) {

    if (num < temp->num)
      temp = temp->left;

    else if (num > temp->num)
      temp = temp->right;

    // found. check if words are equal
    else {
      for (i = 0; i < num; ++i) {
        if (temp->word[i] != buff[i])
          return NULL;
      }

      return temp; //equal
    }
      
  }

  return NULL;
}

void NodeRemove1(tree_t** tree, tree_t* vertex) {
  if (!vertex)
    return;
  int temp, i;
  tree_t* max = vertex, * parent, *temp2; //go to left child of vertex and then to right 
  way_t parentway;
  char c;

  int subtreewidthprev = vertex->subtreeWigth;

  //change numbers of removing vertex and max
  if (max->left) {
    max = max->left;

    while (max->right)
      max = max->right;

    //add difference to subtreewudth because length of list changed
    vertex->subtreeWigth += (vertex->num - max->num);

    //exchange information
    temp = max->num;
    max->num = vertex->num;
    vertex->num = temp;

    for (i = 0; i < max->num; ++i) {
      c = max->word[i];
      max->word[i] = vertex->word[i];
      vertex->word[i] = c;
    }

  }

  //no left child on removing vertex, only right 
  else if (vertex->right != NULL){
    parent = vertex->parent;
    parentway = (parent->left == vertex) ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = vertex->right;
    else //parentway==RIGHT
      parent->right = vertex->right;

    vertex->right->parent = parent;

    temp2 = vertex->right;
    while (temp2->parent) {
      temp2 = temp2->parent;
      temp2->subtreeWigth -= vertex->num;
    }
    return;
  }


  //now we should remove 'max'. He can have 1 child on the left.
  if (max->left == NULL && max->right == NULL) {

    if (max == (*tree)) {
      free(max->word);
      free(max);
      (*tree) = NULL;
      return;
    }

    parent = max->parent;

    parentway = (parent->left == max) ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = NULL;
    else //parentway==RIGHT
      parent->right = NULL;

    //update subtreewidth until root
    temp2 = max;
    while (temp2->parent) {
      temp2 = temp2->parent;
      temp2->subtreeWigth -= max->num;
    }

    free(max->word);
    free(max);
  }

  else { //has one child on the left

    parent = max->parent;
    parentway = (parent->left == max) ? LEFT : RIGHT;

    if (parentway == LEFT) {
      parent->left = max->left;
      max->left->parent = parent;
    }
    else { //parentway == RIGHT
      parent->right = max->left;
      max->left->parent = parent;
    }

    //update subtreewidth until root
    temp2 = max;
    while (temp2->parent) {
      temp2 = temp2->parent;
      temp2->subtreeWigth -= max->num;
    }


    free(max->word);
    free(max);
  }
}



/* printing tree rotated on 90 degrees. Root of tree in the left, leaves on the right
* 
* structure of printing:
*  
*  word
*  length of word
*  length of subtree 
*/
void PrintTree1(tree_t* tree, int level) {
  if (tree) {
    int i;
    PrintTree1(tree->left, level + (tree->num)); //tree->num - length of word
    for (i = 0; i < level; i++)
      printf("   ");

    for (i = 0; i < tree->num; ++i)
      printf("%c", tree->word[i]);

    printf("\n");
    for (i = 0; i < level; i++)
      printf("   ");
    printf("%i\n", tree->num);

    for (i = 0; i < level; i++)
      printf("   ");
    printf("%i\n", tree->subtreeWigth);

    PrintTree1(tree->right, level + (tree->num));
  }
}

int main(void) {
  tree_t* tree = NULL;
  const int ONE = 1;

  NodeAppend1(&tree, "yes");
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "school");
  NodeAppend1(&tree, "wonderful");
  NodeAppend1(&tree, "coder");
  NodeAppend1(&tree, "polytechnic");

  NodeRemove1(&tree, NodeFind1(tree, "school"));

  PrintTree1(tree, ONE);

  DestroyTree1(tree);
  return 0;
}

