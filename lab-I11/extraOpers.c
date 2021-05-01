#include "lab-I.h"

//push into stack
bool Push(stack_t** stack, tree_t* newTree) {

  if (!newTree)
    return false;
  stack_t* newNode = (stack_t*)malloc(sizeof(stack_t));
  if (!newNode)
    return false;
  newNode->tree = newTree;
  newNode->next = (*stack);
  (*stack) = newNode;
  return true;
}

//remove from stack
bool Pop(stack_t** stack, tree_t** tree) {
  stack_t* deleteNode = (*stack);
  if (!deleteNode) {
    (*tree) = NULL;
    return false;
  }
  (*tree) = (*stack)->tree;
  (*stack) = (*stack)->next;
  free(deleteNode);
  return true;
}

int TreeHeight(tree_t* tree) {
  int h = 0;
  tree_t* temp = tree;
  while (temp) {
    h++;
    temp = temp->lc;
  }
  return h;
}

int GetMinElement(tree_t* tree) {
  tree_t* temp = tree;

  while (temp && temp->isLeaf == false)
    temp = temp->lc;

  return (temp ? temp->value : 0);
}

bool UnitedFromLeft(tree_t** tree, tree_t* leftTree, tree_t* newTreesSibling) {
  tree_t* siblingParent = newTreesSibling->parent;
  tree_t* newNodeToNewLeft = NULL;

  if (siblingParent == NULL) {
    tree_t* newParent = (tree_t*)malloc(sizeof(tree_t));
    if (newParent == NULL)
      return false;

    newParent->isLeaf = false;
    newParent->value = 0;
    newParent->rn = 0;
    newParent->ln = leftTree->maxValue;
    newParent->maxValue = newTreesSibling->maxValue;
    newParent->amountChildren = 2;

    newParent->lc = leftTree;
    newParent->mc = newTreesSibling;
    newParent->rc = newParent->parent = NULL;

    leftTree->parent = newParent;
    newTreesSibling->parent = newParent;

    (*tree) = newParent;
    return true;
  }
  if (siblingParent->amountChildren == 2) {
    siblingParent->amountChildren = 3;
    siblingParent->rc = siblingParent->mc;
    siblingParent->mc = siblingParent->lc;
    siblingParent->lc = leftTree;
    leftTree->parent = siblingParent;

    siblingParent->rn = siblingParent->mc->maxValue;
    siblingParent->ln = siblingParent->lc->maxValue;

    return true;
  }
  if (siblingParent->amountChildren == 3) {
    newNodeToNewLeft = (tree_t*)malloc(sizeof(tree_t));
    if (newNodeToNewLeft == NULL)
      return false;

    newNodeToNewLeft->isLeaf = false;
    newNodeToNewLeft->value = 0;
    newNodeToNewLeft->rn = 0;
    newNodeToNewLeft->amountChildren = 2;

    newNodeToNewLeft->lc = leftTree;
    newNodeToNewLeft->mc = siblingParent->lc;
    newNodeToNewLeft->rc = newNodeToNewLeft->parent = NULL;

    newNodeToNewLeft->ln = leftTree->maxValue;
    newNodeToNewLeft->maxValue = newNodeToNewLeft->mc->maxValue;

    leftTree->parent = newNodeToNewLeft;
    newTreesSibling->parent = newNodeToNewLeft;

    siblingParent->amountChildren = 2;
    siblingParent->lc = siblingParent->mc;
    siblingParent->mc = siblingParent->rc;
    siblingParent->rc = NULL;
    siblingParent->rn = 0;
    siblingParent->ln = siblingParent->lc->maxValue;

    return UnitedFromLeft(tree, newNodeToNewLeft, siblingParent);
  }
  return true;
}

bool UnitedFromRight(tree_t** tree, tree_t* rightTree, tree_t* newTreesSibling) {
  tree_t* siblingParent = newTreesSibling->parent;
  tree_t* newNodeToNewRight;
  tree_t* temp, *newParent;
  int prevMax;

  if (siblingParent == NULL) {
    newParent = (tree_t*)malloc(sizeof(tree_t));
    if (newParent == NULL)
      return false;

    newParent->isLeaf = false;
    newParent->value = 0;
    newParent->rn = 0;
    newParent->ln = newTreesSibling->maxValue;
    newParent->maxValue = rightTree->maxValue;
    newParent->amountChildren = 2;

    newParent->lc = newTreesSibling;
    newParent->mc = rightTree;
    newParent->rc = newParent->parent = NULL;

    rightTree->parent = newParent;
    newTreesSibling->parent = newParent;

    (*tree) = newParent;
    return true;
  }
  if (siblingParent->amountChildren == 2) {
    siblingParent->amountChildren = 3;
    siblingParent->rc = rightTree;
    rightTree->parent = siblingParent;

    siblingParent->rn = siblingParent->mc->maxValue;
    siblingParent->maxValue = siblingParent->rc->maxValue;

    siblingParent = siblingParent->parent;
    while (siblingParent) {
      if (rightTree->maxValue > siblingParent->maxValue)
        siblingParent->maxValue = rightTree->maxValue;
      else
        break;

      siblingParent = siblingParent->parent;
    }

    return true;
  }
  if (siblingParent->amountChildren == 3) {
    newNodeToNewRight = (tree_t*)malloc(sizeof(tree_t));
    if (!newNodeToNewRight)
      return false;

    newNodeToNewRight->isLeaf = false;
    newNodeToNewRight->value = 0;
    newNodeToNewRight->rn = 0;
    newNodeToNewRight->amountChildren = 2;

    newNodeToNewRight->lc = siblingParent->rc;
    newNodeToNewRight->mc = rightTree;
    newNodeToNewRight->rc = newNodeToNewRight->parent = NULL;

    newNodeToNewRight->ln = newNodeToNewRight->lc->maxValue;
    newNodeToNewRight->maxValue = newNodeToNewRight->mc->maxValue;

    rightTree->parent = newNodeToNewRight;
    newTreesSibling->parent = newNodeToNewRight;

    siblingParent->amountChildren = 2;
    siblingParent->rc = NULL;
    siblingParent->rn = 0;
    siblingParent->maxValue = siblingParent->mc->maxValue;

    prevMax = newNodeToNewRight->lc->maxValue;
    temp = siblingParent->parent;
    while (temp) {
      if (temp->maxValue == prevMax)
        if (temp->amountChildren == 2)
          temp->maxValue = temp->mc->maxValue;
        else
          temp->maxValue = temp->rc->maxValue;
      else
        break;

      temp = temp->parent;
    }

    return UnitedFromRight(tree, newNodeToNewRight, siblingParent);
  }
  return true;
}

//return merged tree from pointer
bool Merge(tree_t** tree, tree_t* tree1, tree_t* tree2) {
  int len1 = TreeHeight(tree1);
  int min1 = GetMinElement(tree1);
  int len2 = TreeHeight(tree2);
  int min2 = GetMinElement(tree2);
  int tempLen;
  int tmpMin;
  int i;

  tree_t* temp;
  tree_t* oldPtr = (*tree);
  tree_t* tempParent;
  tree_t* newTreeTop; //if len1==len2

  //in case if some tree does not exist
  if (!tree1 && !tree2)  {
    (*tree) = NULL;
    return false;
  }
  else if (!tree1) {
    (*tree) = tree2;
    return true;
  }
  else if (!tree2) {
    (*tree) = tree1;
    return true;
  }

  //cannot merge
  if (!(min2 > tree1->maxValue || min1 > tree2->maxValue)) {
    (*tree) = NULL;
    return false;
  }

  if (len1 < len2) {
    temp = tree2;
    tree2 = tree1;
    tree1 = temp;

    tempLen = len1;
    len1 = len2;
    len2 = tempLen;
    tmpMin = min1;
    min1 = min2;
    min2 = tmpMin;
  }

  if (len1 == len2) {
    newTreeTop = (tree_t*)malloc(sizeof(tree_t));
    if (newTreeTop == NULL)
      return false;

    newTreeTop->isLeaf = false;
    newTreeTop->value = 0;
    newTreeTop->rn = 0;
    newTreeTop->amountChildren = 2;
    newTreeTop->rc = NULL;
    newTreeTop->parent = NULL;

    tree1->parent = newTreeTop;
    tree2->parent = newTreeTop;

    if (min2 > tree1->maxValue) {
      newTreeTop->lc = tree1;
      newTreeTop->mc = tree2;
    }
    else {
      newTreeTop->lc = tree1;
      newTreeTop->mc = tree2;
    }
    newTreeTop->ln = newTreeTop->lc->maxValue;
    newTreeTop->maxValue = newTreeTop->mc->maxValue;
    (*tree) = newTreeTop;
    return true;
  } //if (len1 == len2)

  else {
    temp = tree1;
    tempParent = NULL;
    if (min1 > tree2->maxValue) {
      for (i = 0; i < len1 - len2; i++) {
        tempParent = temp;
        temp = temp->lc;
      }

      UnitedFromLeft(tree, tree2, temp);
      if ((*tree) == oldPtr)
        (*tree) = tree1;
    }

    else {
      for (i = 0; i < len1 - len2; i++) {
        tempParent = temp;
        if (tree1->amountChildren == 2)
          temp = temp->mc;
        else
          temp = temp->rc;
      }
      UnitedFromRight(tree, tree2, temp);
      if ((*tree) == oldPtr)
        (*tree) = tree1;
    }
  }
  return true;
}

//return 2 splited trees from pointers
bool Split(tree_t* tree, tree_t** tree1, tree_t** tree2, int key) {
  tree_t* temp = tree;
  tree_t* tempParent = NULL, *lt = NULL, *rt = NULL, *deleteNode, *leafNode;
  stack_t* leftStack = NULL;
  stack_t* rightStack = NULL;

  (*tree1) = NULL;
  (*tree2) = NULL;

  if (tree == NULL)
    return false;

  while (temp && temp->isLeaf == false) {
    tempParent = temp;

    if (temp->amountChildren == 2)  {
      if (key <= temp->ln)
        temp = temp->lc;
      else
        temp = temp->mc;
    }
    else {
      if (key <= temp->ln)
        temp = temp->lc;
      else if (temp->ln < key && key <= temp->rn)
        temp = temp->mc;
      else if (temp->rn < key)
        temp = temp->rc;
    }
  }

  if (!temp || temp->value != key)
    return false;

  if (tempParent == NULL) {
    (*tree1) = temp;
    (*tree2) = NULL;
  }
  else {
    Push(&leftStack, temp);

    while (tempParent) {

      //in different cases push in different ways
      if (tempParent->amountChildren == 2 && temp == tempParent->lc) {
        tempParent->mc->parent = NULL;
        Push(&rightStack, tempParent->mc);
      }
      else if (tempParent->amountChildren == 2 && temp == tempParent->mc){
        tempParent->lc->parent = NULL;
        Push(&leftStack, tempParent->lc);
      }
      else if (tempParent->amountChildren == 3 && temp == tempParent->lc) {
        tempParent->mc->parent = tempParent->rc->parent = NULL;
        Push(&rightStack, tempParent->mc);
        Push(&rightStack, tempParent->rc);
      }
      else if (tempParent->amountChildren == 3 && temp == tempParent->mc) {
        tempParent->lc->parent = tempParent->rc->parent = NULL;
        Push(&leftStack, tempParent->lc);
        Push(&rightStack, tempParent->rc);
      }
      else if (tempParent->amountChildren == 3 && temp == tempParent->rc)  {
        tempParent->mc->parent = tempParent->lc->parent = NULL;
        Push(&leftStack, tempParent->lc);
        Push(&leftStack, tempParent->mc);
      }

      deleteNode = temp;
      tempParent = tempParent->parent;
      if (temp->isLeaf == true) {
        leafNode = temp;
        temp = temp->parent;
        leafNode->parent = NULL;
      }
      else
        temp = temp->parent;
      if (deleteNode->isLeaf == false)
        free(deleteNode);
    }

    while (leftStack != NULL) {
      Pop(&leftStack, &temp);
      Merge(&lt, lt, temp);
    }
    (*tree1) = lt;

    while (rightStack != NULL) {
      Pop(&rightStack, &temp);
      Merge(&rt, rt, temp);
    }
    (*tree2) = rt;
  }

  return true;
}