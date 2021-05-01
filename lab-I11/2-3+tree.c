#include "lab-I.h"

//for inserting
bool Unite(tree_t** tree, tree_t* node, tree_t* newNode) {
  // newNode bigger than node
  tree_t* nodeParent = node->parent;

  tree_t* newtree = NULL;

  //in case if 3 children
  tree_t* newParent = NULL, *l1, *l2, *l3, *l4;

  if (!nodeParent) {
    newtree = (tree_t*)malloc(sizeof(tree_t));
    if (!newtree)
      return false;

    newtree->isLeaf = false;
    newtree->value = 0;
    newtree->rn = 0;
    newtree->amountChildren = 2;
    newtree->rc = newtree->parent = NULL;
    newtree->maxValue = newNode->maxValue;
    newtree->ln = node->maxValue;
    newtree->lc = node;
    newtree->mc = newNode;
    newNode->parent = node->parent = newtree;

    (*tree) = newtree;
    return true;
  }

  //if parent exists and 2 children
  else if (nodeParent->amountChildren == 2) {
    nodeParent->amountChildren = 3;
    newNode->parent = nodeParent;

    if (newNode->maxValue < nodeParent->lc->maxValue) {
      nodeParent->rc = nodeParent->mc;
      nodeParent->mc = nodeParent->lc;
      nodeParent->lc = newNode;
    }
    else if (newNode->maxValue > nodeParent->lc->maxValue &&\
      newNode->maxValue < nodeParent->mc->maxValue) {
      nodeParent->rc = nodeParent->mc;
      nodeParent->mc = newNode;
    }
    else
      nodeParent->rc = newNode;

    nodeParent->ln = nodeParent->lc->maxValue;
    nodeParent->rn = nodeParent->mc->maxValue;
    nodeParent->maxValue = nodeParent->rc->maxValue;
    nodeParent = nodeParent->parent;
    while (nodeParent) {
      if (newNode->maxValue > nodeParent->maxValue)
        nodeParent->maxValue = newNode->maxValue;
      else
        break;

      nodeParent = nodeParent->parent;
    }

    return true;
  }
  else {
    newParent = (tree_t*)malloc(sizeof(tree_t));
    if (!newParent)
      return false;

    if (newNode->maxValue < nodeParent->lc->maxValue) {
      l1 = newNode;
      l2 = nodeParent->lc;
      l3 = nodeParent->mc;
      l4 = nodeParent->rc;
    }
    else if (newNode->maxValue > nodeParent->lc->maxValue && newNode->maxValue < nodeParent->mc->maxValue) {
      l1 = nodeParent->lc;
      l2 = newNode;
      l3 = nodeParent->mc;
      l4 = nodeParent->rc;
    }
    else if (newNode->maxValue > nodeParent->mc->maxValue && newNode->maxValue < nodeParent->rc->maxValue) {
      l1 = nodeParent->lc;
      l2 = nodeParent->mc;
      l3 = newNode;
      l4 = nodeParent->rc;
    }
    else {
      l1 = nodeParent->lc;
      l2 = nodeParent->mc;
      l3 = nodeParent->rc;
      l4 = newNode;
    }

    nodeParent->rn = 0;
    nodeParent->amountChildren = 2;
    nodeParent->ln = l1->maxValue;
    nodeParent->lc = l1;
    nodeParent->mc = l2;
    nodeParent->rc = NULL;
    nodeParent->maxValue = l2->maxValue;
    l1->parent = l2->parent = nodeParent;

    newParent->isLeaf = false;
    newParent->value = 0;
    newParent->rn = 0;
    newParent->amountChildren = 2;
    newParent->ln = l3->maxValue;
    newParent->lc = l3;
    newParent->mc = l4;
    newParent->rc = NULL;
    newParent->maxValue = l4->maxValue;
    l3->parent = l4->parent = newParent;

    return Unite(tree, nodeParent, newParent);
  }
}

//////functions for deleting////////////////

//fixing after deleting
void FixPath(tree_t* node) {
  tree_t* temp = node;
  tree_t* parent = NULL;

  if (temp)
    parent = temp->parent;

  while (temp && parent) {
    if (parent->amountChildren == 2)
    {
      if (temp == parent->lc)
        parent->ln = temp->maxValue;
      else if (temp == parent->mc)
        parent->maxValue = temp->maxValue;
    }
    else {
      if (temp == parent->lc)
        parent->ln = temp->maxValue;
      else if (temp == parent->mc)
        parent->rn = temp->maxValue;
      else if (temp == parent->rc)
        parent->maxValue = temp->maxValue;
    }

    temp = parent;
    parent = parent->parent;
  }
}

void FixTwoParentsTreesMin(tree_t* fixNode, tree_t* deleteNode) {
  tree_t* deleteNodeParent = deleteNode->parent;

  //all have 2 children
  if (fixNode->amountChildren == 2 && fixNode->lc->amountChildren == 2 && \
    fixNode->mc->amountChildren == 2) {
    if (deleteNodeParent == fixNode->lc) {
      fixNode->mc->rc = fixNode->mc->mc;
      fixNode->mc->mc = fixNode->mc->lc;

      if (deleteNode == deleteNodeParent->lc)
        fixNode->mc->lc = deleteNodeParent->mc;
      else
        fixNode->mc->lc = deleteNodeParent->lc;

      fixNode->mc->lc->parent = fixNode->mc;

      fixNode->mc->amountChildren = 3;
      fixNode->mc->ln = fixNode->mc->lc->maxValue;
      fixNode->mc->rn = fixNode->mc->mc->maxValue;
    }
    else {
      if (deleteNode == deleteNodeParent->lc)
        fixNode->lc->rc = deleteNodeParent->mc;
      else
        fixNode->lc->rc = deleteNodeParent->lc;

      fixNode->lc->rc->parent = fixNode->lc;

      fixNode->lc->amountChildren = 3;
      fixNode->lc->rn = fixNode->lc->mc->maxValue;
      fixNode->lc->maxValue = fixNode->lc->rc->maxValue;

      fixNode->ln = fixNode->lc->maxValue;
    }
  }

  FixPath(fixNode);
}

void FixTwoParentsTrees(tree_t* fixNode, tree_t* deleteNode) {
  tree_t* deleteNodeParent = deleteNode->parent;

  if (fixNode->lc == deleteNodeParent) {
    if (deleteNodeParent->lc == deleteNode) {
      deleteNodeParent->lc = deleteNodeParent->mc;
      deleteNodeParent->ln = deleteNodeParent->lc->maxValue;
    }
    deleteNodeParent->mc = fixNode->mc->lc;
    deleteNodeParent->mc->parent = deleteNodeParent;
    deleteNodeParent->maxValue = deleteNodeParent->mc->maxValue;

    fixNode->mc->lc = fixNode->mc->mc;
    fixNode->mc->mc = fixNode->mc->rc;
    fixNode->mc->rc = NULL;
    fixNode->mc->ln = fixNode->mc->lc->maxValue;
    fixNode->mc->rn = 0;

    fixNode->mc->amountChildren = 2;
    fixNode->ln = fixNode->lc->maxValue;
  } //if (fixNode->lc == deleteNodeParent)

  else {
    if (deleteNodeParent->mc == deleteNode)
      deleteNodeParent->mc = deleteNodeParent->lc;

    deleteNodeParent->lc = fixNode->lc->rc;
    deleteNodeParent->lc->parent = deleteNodeParent;
    fixNode->ln = deleteNodeParent->lc->maxValue;
    deleteNodeParent->maxValue = deleteNodeParent->mc->maxValue;

    fixNode->lc->amountChildren = 2;
    fixNode->lc->rn = 0;
    fixNode->lc->rc = NULL;
    fixNode->lc->maxValue = fixNode->lc->mc->maxValue;

    fixNode->mc->ln = fixNode->mc->lc->maxValue;

    fixNode->ln = fixNode->lc->maxValue;
    fixNode->maxValue = fixNode->mc->maxValue;
  }

  FixPath(fixNode);
}

void Correct3ParentsTrees(tree_t* fixNode, tree_t* deleteNode) {
  tree_t* deleteNodeParent = deleteNode->parent;

  //all have 2 children
  if (fixNode->lc->amountChildren == 2 && fixNode->mc->amountChildren ==2 &&\
    fixNode->rc->amountChildren == 2) {
    if (fixNode->lc == deleteNodeParent) {
      fixNode->mc->rc = fixNode->mc->mc;
      fixNode->mc->mc = fixNode->mc->lc;

      if (deleteNodeParent->lc == deleteNode)
        fixNode->mc->lc = deleteNodeParent->mc;
      else
        fixNode->mc->lc = deleteNodeParent->lc;

      fixNode->mc->lc->parent = fixNode->mc;

      fixNode->lc = fixNode->mc;
      fixNode->mc = fixNode->rc;
      fixNode->rc = NULL;

      fixNode->amountChildren = 2;
      fixNode->ln = fixNode->lc->maxValue;
      fixNode->rn = 0;
      fixNode->lc->amountChildren = 3;
      fixNode->lc->ln = fixNode->lc->lc->maxValue;
      fixNode->lc->rn = fixNode->lc->mc->maxValue;
    }

    else if (fixNode->mc == deleteNodeParent)
    {
      if (deleteNodeParent->lc == deleteNode)
        fixNode->lc->rc = deleteNodeParent->mc;
      else
        fixNode->lc->rc = deleteNodeParent->lc;

      fixNode->lc->rc->parent = fixNode->lc;

      fixNode->mc = fixNode->rc;
      fixNode->rc = NULL;

      fixNode->amountChildren = 2;
      fixNode->lc->maxValue = fixNode->lc->rc->maxValue;
      fixNode->ln = fixNode->lc->maxValue;
      fixNode->rn = 0;
      fixNode->lc->amountChildren = 3;
      fixNode->lc->rn = fixNode->lc->mc->maxValue;
    }
    else if (fixNode->rc == deleteNodeParent)
    {
      if (deleteNodeParent->lc == deleteNode)
        fixNode->mc->rc = deleteNodeParent->mc;
      else
        fixNode->mc->rc = deleteNodeParent->lc;

      fixNode->mc->rc->parent = fixNode->mc;
      fixNode->rc = NULL;

      fixNode->amountChildren = 2;
      fixNode->ln = fixNode->lc->maxValue;
      fixNode->rn = 0;
      fixNode->mc->maxValue = fixNode->mc->rc->maxValue;
      fixNode->maxValue = fixNode->mc->maxValue;
      fixNode->mc->amountChildren = 3;
      fixNode->mc->rn = fixNode->mc->mc->maxValue;
    }

    free(deleteNodeParent);
  } //if all have 2 chidren

  else {
    if (fixNode->lc == deleteNodeParent) {
      if (deleteNodeParent->lc == deleteNode)
        deleteNodeParent->lc = deleteNodeParent->mc;

      deleteNodeParent->mc = fixNode->mc->lc;
      deleteNodeParent->mc->parent = deleteNodeParent;
      deleteNodeParent->ln = deleteNodeParent->lc->maxValue;
      deleteNodeParent->maxValue = deleteNodeParent->mc->maxValue;

      fixNode->mc->lc = fixNode->mc->mc;

      //looking at childrens' children
      if (fixNode->mc->amountChildren == 2) {
        fixNode->mc->mc = fixNode->rc->lc;
        fixNode->mc->mc->parent = fixNode->mc;

        fixNode->mc->ln = fixNode->mc->lc->maxValue;
        fixNode->mc->maxValue = fixNode->mc->mc->maxValue;

        fixNode->rc->lc = fixNode->rc->mc;
        fixNode->rc->mc = fixNode->rc->rc;

        fixNode->rc->amountChildren = 2;
        fixNode->rc->rn = 0;
        fixNode->rc->rc = NULL;
        fixNode->rc->ln = fixNode->rc->lc->maxValue;
        fixNode->rc->maxValue = fixNode->rc->mc->maxValue;
      }
      else {
        fixNode->mc->amountChildren = 2;
        fixNode->mc->mc = fixNode->mc->rc;
        fixNode->mc->rn = 0;
        fixNode->mc->rc = NULL;
        fixNode->mc->ln = fixNode->mc->lc->maxValue;
      }

      fixNode->ln = fixNode->lc->maxValue;
      fixNode->rn = fixNode->mc->maxValue;
      fixNode->maxValue = fixNode->rc->maxValue;
    } //if (fixNode->lc == deleteNodeParent)

    else if (fixNode->mc == deleteNodeParent) {
      if (fixNode->lc->amountChildren == 3) {
        if (deleteNodeParent->mc == deleteNode)
          deleteNodeParent->mc = deleteNodeParent->lc;

        deleteNodeParent->lc = fixNode->lc->rc;
        deleteNodeParent->lc->parent = deleteNodeParent;
        deleteNodeParent->ln = deleteNodeParent->lc->maxValue;
        deleteNodeParent->maxValue = deleteNodeParent->mc->maxValue;

        fixNode->lc->amountChildren = 2;
        fixNode->lc->rn = 0;
        fixNode->lc->rc = NULL;
        fixNode->lc->maxValue = fixNode->lc->mc->maxValue;
      }
      else {
        if (deleteNodeParent->lc == deleteNode)
          deleteNodeParent->lc = deleteNodeParent->mc;

        deleteNodeParent->mc = fixNode->rc->lc;
        deleteNodeParent->mc->parent = deleteNodeParent;
        deleteNodeParent->lc->parent = deleteNodeParent;
        deleteNodeParent->ln = deleteNodeParent->lc->maxValue;
        deleteNodeParent->maxValue = deleteNodeParent->mc->maxValue;

        fixNode->rc->lc = fixNode->rc->mc;
        fixNode->rc->mc = fixNode->rc->rc;
        fixNode->rc->amountChildren = 2;
        fixNode->rc->rn = 0;
        fixNode->rc->rc = NULL;
        fixNode->rc->ln = fixNode->rc->lc->maxValue;
        fixNode->rc->maxValue = fixNode->rc->mc->maxValue;
      }

      fixNode->ln = fixNode->lc->maxValue;
      fixNode->rn = fixNode->mc->maxValue;
      fixNode->maxValue = fixNode->rc->maxValue;
    }//else if (fixNode->mc == deleteNodeParent)

    else {
      if (deleteNodeParent->mc == deleteNode)
        deleteNodeParent->mc = deleteNodeParent->lc;

      if (fixNode->mc->amountChildren == 2)
      {
        deleteNodeParent->lc = fixNode->mc->mc;
        deleteNodeParent->lc->parent = deleteNodeParent;

        fixNode->mc->mc = fixNode->mc->lc;

        fixNode->mc->lc = fixNode->lc->rc;
        fixNode->mc->lc->parent = fixNode->mc;

        fixNode->lc->amountChildren = 2;
        fixNode->lc->rn = 0;
        fixNode->lc->rc = NULL;
        fixNode->lc->maxValue = fixNode->lc->mc->maxValue;

        fixNode->mc->ln = fixNode->mc->lc->maxValue;
        fixNode->mc->maxValue = fixNode->mc->mc->maxValue;
      }
      else {
        deleteNodeParent->lc = fixNode->mc->rc;
        deleteNodeParent->lc->parent = deleteNodeParent;

        fixNode->mc->amountChildren = 2;
        fixNode->mc->rn = 0;
        fixNode->mc->rc = NULL;
        fixNode->mc->maxValue = fixNode->mc->mc->maxValue;
      }
      deleteNodeParent->ln = deleteNodeParent->lc->maxValue;
      deleteNodeParent->maxValue = deleteNodeParent->mc->maxValue;

      fixNode->ln = fixNode->lc->maxValue;
      fixNode->rn = fixNode->mc->maxValue;
      fixNode->maxValue = fixNode->rc->maxValue;
    }
  }

  FixPath(fixNode);
}

void DeleteNodesFromTree(tree_t** tree, tree_t* nodeParent, tree_t* node) {
  if (!nodeParent->parent && nodeParent->amountChildren == 2) {
    if (nodeParent->lc == node)
      (*tree) = nodeParent->mc;
    else
      (*tree) = nodeParent->lc;
    (*tree)->parent = NULL;

    free(nodeParent);
    free(node);
  }
  else if (!nodeParent->parent) {
    nodeParent->amountChildren = 2;
    if (nodeParent->lc == node) {
      nodeParent->lc = nodeParent->mc;
      nodeParent->mc = nodeParent->rc;
    }
    else if (nodeParent->mc == node)
      nodeParent->mc = nodeParent->rc;

    nodeParent->rc = NULL;
    nodeParent->rn = 0;
    nodeParent->maxValue = nodeParent->mc->maxValue;
    nodeParent->ln = nodeParent->lc->maxValue;
    free(node);
  }//else if (!nodeParent->parent)

  else {
    if (nodeParent->parent->amountChildren == 2 && nodeParent->parent->lc->amountChildren == 2\
      && nodeParent->parent->mc->amountChildren == 2) {
      FixTwoParentsTreesMin(nodeParent->parent, node);
      DeleteNodesFromTree(tree, nodeParent->parent, nodeParent);
    }
    else if (nodeParent->parent->amountChildren == 2) {
      FixTwoParentsTrees(nodeParent->parent, node);
      free(node);
    }
    else  {
      Correct3ParentsTrees(nodeParent->parent, node);
      free(node);
    }
  }
}


///////end of functions for deleting///////

bool Insert(tree_t** tree, int key) {
  tree_t* newLeaf = (tree_t*)malloc(sizeof(tree_t));
  tree_t* temp = (*tree), * parent = NULL;
  if (!newLeaf)
    return false;

  //if 3 children
  tree_t* newParent = NULL;
  tree_t* l1, * l2, * l3, * l4;

  newLeaf->isLeaf = true;
  newLeaf->value = key;
  newLeaf->maxValue = key;

  newLeaf->amountChildren = 0;
  newLeaf->ln = 0;
  newLeaf->rn = 0;
  newLeaf->lc = NULL;
  newLeaf->rc = NULL;
  newLeaf->mc = NULL;

  if (*tree) {
    while (temp && temp->isLeaf == false) {
      parent = temp;

      if (temp->amountChildren == 2) {
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
    if (temp  && temp->value == key) {
      free(newLeaf);
      return false;
    }

    if (parent) {
      if (parent->amountChildren == 2) {
        parent->amountChildren = 3;
        newLeaf->parent = parent;

        if (key < parent->lc->value) {
          parent->ln = key;
          parent->rn = parent->lc->value;
          parent->rc = parent->mc;
          parent->mc = parent->lc;
          parent->lc = newLeaf;
        }
        else if (key  < parent->mc->value && key  > parent->lc->value) {
          parent->rn = key;
          parent->rc = parent->mc;
          parent->mc = newLeaf;
        }
        else {
          parent->rn = parent->mc->value;
          parent->rc = newLeaf;
        }
        parent->maxValue = parent->rc->value;

        parent = parent->parent;
        while (parent) {
          if (key > parent->maxValue)
            parent->maxValue = key;
          else
            break;

          parent = parent->parent;
        }

        return true;
      } //if (parent->amountChildren == 2)

      else {
        newParent = (tree_t*)malloc(sizeof(tree_t));
        if (!newParent) {
          free(newLeaf);
          return false;
        }
        if (key < parent->lc->value) {
          l1 = newLeaf;
          l2 = parent->lc;
          l3 = parent->mc;
          l4 = parent->rc;
        }
        else if (key > parent->lc->value && key < parent->mc->value) {
          l1 = parent->lc;
          l2 = newLeaf;
          l3 = parent->mc;
          l4 = parent->rc;
        }
        else if (key > parent->mc->value && key < parent->rc->value) {
          l1 = parent->lc;
          l2 = parent->mc;
          l3 = newLeaf;
          l4 = parent->rc;
        }
        else {
          l1 = parent->lc;
          l2 = parent->mc;
          l3 = parent->rc;
          l4 = newLeaf;
        }

        //rearranging leaves
        parent->amountChildren = 2;
        parent->rn = 0;
        parent->ln = l1->value;
        parent->lc = l1;
        parent->mc = l2;
        parent->rc = NULL;
        parent->maxValue = l2->value;
        l1->parent = l2->parent = parent;

        newParent->isLeaf = false;
        newParent->value = 0;
        newParent->rn = 0;
        newParent->amountChildren = 2;
        newParent->ln = l3->value;
        newParent->lc = l3;
        newParent->mc = l4;
        newParent->rc = NULL;
        newParent->maxValue = l4->value;
        l3->parent = l4->parent = newParent;

        return Unite(tree, parent, newParent);
      }
    } //if(parent)

    else {
      newParent = (tree_t*)malloc(sizeof(tree_t));
      if (!newParent) {
        free(newLeaf);
        return false;
      }
      newLeaf->parent = newParent;
      temp->parent = newParent;

      newParent->parent = NULL;
      newParent->amountChildren = 2;
      newParent->isLeaf = false;
      newParent->value = 0;
      newParent->rn = 0;
      newParent->rc = NULL;

      if (temp->value < key) {
        newParent->lc = temp;
        newParent->ln = temp->value;
        newParent->mc = newLeaf;
      }
      else {
        newParent->lc = newLeaf;
        newParent->ln = newLeaf->value;
        newParent->mc = temp;
      }
      newParent->maxValue = newParent->mc->value;

      (*tree) = newParent;
      return true;
    }
  }
  else {
    newLeaf->parent = NULL;
    (*tree) = newLeaf;
  }

  return true;
}

bool Find(tree_t* tree, int key) {
  tree_t* temp = tree;

  while (temp && temp->isLeaf == false) {
    if (temp->amountChildren == 2) {
      if (key <= temp->ln)
        temp = temp->lc;
      else
        temp = temp->mc;
    }
    else {
      if (temp->ln >= key)
        temp = temp->lc;
      else if (temp->ln < key && key <= temp->rn)
        temp = temp->mc;
      else if (temp->rn < key)
        temp = temp->rc;
    }
  }
  if (!temp || temp->value != key)
    return false;
  else
    return true;
}

bool Delete(tree_t** tree, int key) {
  tree_t* temp = (*tree);
  tree_t* parent = NULL;

  if (!(*tree))
    return false;

  while (temp && temp->isLeaf == false) {
    parent = temp;

    if (temp->amountChildren == 2) {
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
  if (temp == NULL || (temp != NULL && temp->value != key))
    return false;

  if (parent == NULL)
    (*tree) = NULL;

  else if (!parent->parent) {
    if (parent->amountChildren == 2) {
      if (temp == parent->lc)
        (*tree) = parent->mc;
      else
        (*tree) = parent->lc;

      (*tree)->parent = NULL;
      free(parent);
    }
    else {
      parent->amountChildren = 2;
      if (parent->lc == temp) {
        parent->lc = parent->mc;
        parent->mc = parent->rc;
      }
      else if (parent->mc == temp)
        parent->mc = parent->rc;

      parent->maxValue = parent->mc->value;
      parent->ln = parent->lc->value;
      parent->rc = NULL;
      parent->rn = 0;

      FixPath(parent);
    }
  } //else if (!parent->parent)

  else {
    if (parent->amountChildren == 3) {
      parent->amountChildren = 2;
      if (parent->lc == temp) {
        parent->lc = parent->mc;
        parent->mc = parent->rc;
      }
      else if (parent->mc == temp)
        parent->mc = parent->rc;

      parent->maxValue = parent->mc->value;
      parent->ln = parent->lc->value;
      parent->rc = NULL;
      parent->rn = 0;

      FixPath(parent);
    } //if (parent->amountChildren == 3)

    else {
      if (parent->parent->amountChildren == 2 && parent->parent->lc->amountChildren == 2\
        && parent->parent->mc->amountChildren == 2) {
        FixTwoParentsTreesMin(parent->parent, temp);
        DeleteNodesFromTree(tree, parent->parent, parent);
      }
      else if (parent->parent->amountChildren == 2)
        FixTwoParentsTrees(parent->parent, temp);
      else
        Correct3ParentsTrees(parent->parent, temp);
    }
  }

  free(temp);
  return true;
}

int main() {
  char comand;
  int num;
  tree_t* root = NULL;

  while (true) {
    comand = fgetc(stdin);

    if (comand == EOF || comand == '\n')
      break;

    scanf("%i", &num);

    //comands
    if (comand == 'a') //append
      Insert(&root, num);

    //adress as bool type. Is adress not NULL -> TRUE. Otherwise, FALSE
    else if (comand == 'f') { //find
      if (Find(root, num))
        printf("yes\n");
      else
        printf("no\n");
    }

    else if (comand == 'r')//remove
      Delete(&root, num);

    num = 0;
    comand = fgetc(stdin); //get '\n' from stdin
  }
  return 0;
}