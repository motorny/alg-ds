#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ((x)>=0?(x):-(x))

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
  tree_t* temp = (*tree), * newnode, * ptr = (*tree);
  int num=0, i, subtreelength;
  newnode = (tree_t*)malloc(sizeof(tree_t));
  if (!newnode)
    return;

  while (buff[num] != '\0')
    num++;

  newnode->left = NULL;
  newnode->right = NULL;
  newnode->parent = NULL;
  newnode->num = num;
  newnode->subtreeWigth = 0;
  newnode->num = num;
  newnode->word = (char*)malloc((num + 1) * sizeof(char));
  if (!newnode->word)
    return;
  for (i = 0; i <= num; i++)
    newnode->word[i] = buff[i];

  if (!(*tree)) {
    (*tree) = newnode;
    return;
  }

  while (ptr) {
    if (num < ptr->num) {
      if (ptr->left)
        ptr = ptr->left;
      else
        break;
    }

    else if (num > ptr->num) {
      if (ptr->right)
        ptr = ptr->right;
      else
        break;
    }

    else {//such node exists
      free(newnode);
      return;
    }
  }

  //put new node
  if (num < ptr->num)
    ptr->left = newnode;
  else
    ptr->right = newnode;

  newnode->parent = ptr;

  //update subtreelengths
  subtreelength = 0;
  temp = newnode;
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
  tree_t* maximum=vertex, *parent, *child, *temp2; //go to left child of vertex and then to right 
  way_t parentway;
  char* help;

  //no childs, free the element
  if (vertex->left == NULL && vertex->right == NULL) {
    if ((vertex == (*tree))) {
      free(vertex->word);
      free(vertex);
      (*tree) = NULL;
      return;
    }

    parent = vertex->parent;
    parentway = parent->left == vertex ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;

    //update subtreewidth
    temp2 = vertex;
    while (temp2->parent) {
      temp2 = temp2->parent;
      temp2->subtreeWigth -= vertex->num;
    }

    free(vertex->word);
    free(vertex);



    return;
  }


  //has one child, put child instead of itself
  if ((vertex->left != NULL && vertex->right == NULL) || (vertex->left == NULL && vertex->right != NULL)) {

    if (vertex == (*tree)) { //no parent
      if (vertex->left)
        (*tree) = vertex->left;
      else
        (*tree) = vertex->right;
      (*tree)->parent = NULL;
      free(vertex);
      return;
    }

    parent = vertex->parent;
    parentway = parent->left == vertex ? LEFT : RIGHT;

    if (vertex->left) //only left child
      child = vertex->left;
    else //only right child
      child = vertex->right;

    child->parent = vertex->parent;

    if (parentway == LEFT)
      parent->left = child;
    else
      parent->right = child;

    //update subtreewidth
    temp2 = vertex;
    while (temp2->parent) {
      temp2 = temp2->parent;
      temp2->subtreeWigth -= vertex->num;
    }

    free(vertex->word);
    free(vertex);
    return;
  }

  //node has two childs
  maximum = maximum->right;

  while (maximum->left)
    maximum = maximum->left;

  temp = maximum->num;
  maximum->num = vertex->num;
  vertex->num = temp;

  help = (char*)realloc(vertex->word, (max(vertex->num, maximum->num)+1)*sizeof(char)); //need more memory
  if (help) {
    vertex->word = help;
    help = NULL;
  }
  else {
    free(vertex->word);
    return;
  }

  for (i = 0; i <= max(vertex->num, maximum->num); ++i)
    vertex->word[i] = maximum->word[i];

  temp2 = maximum;
  while (temp2->parent != vertex->parent) {
    temp2 = temp2->parent;
    temp2->subtreeWigth += (maximum->num - vertex->num);
  }

  //now need to delete max

  //max can have one child on the right
  if (maximum->right) {
    child= maximum->right;
    parent = maximum->parent;
    parentway = parent->left == maximum ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = child;
    else
      parent->right = child;
    
    child->parent = parent;
  }

  //max has no childs
  else {
    parent = maximum->parent;
    parentway = parent->left == maximum ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;
  }
  //update subtreewidth
  temp2 = maximum;
  while (temp2->parent) {
    temp2 = temp2->parent;
    temp2->subtreeWigth -= maximum->num;
  }

  free(maximum->word);
  free(maximum);
  return;
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

  NodeAppend1(&tree, "coder");
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "school");
  NodeAppend1(&tree, "EOF");
  NodeAppend1(&tree, "e");
  NodeAppend1(&tree, "tree");
  NodeRemove1(&tree, NodeFind1(tree, "coder"));
  PrintTree1(tree, ONE);

  DestroyTree1(tree);
  return 0;
}


