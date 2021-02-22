#include "aatree.h"

static int skew(aatree_t** tree) {
  if (tree == NULL || *tree == NULL)
    return PTR_ERR;

  if ((*tree)->left != NULL) {
    if ((*tree)->left->level == (*tree)->level) {
      aatree_t* tmp = *tree;

      *tree = tmp->left;
      tmp->left = (*tree)->right;
      if(tmp->left != NULL)
        tmp->left->parent = tmp;
      (*tree)->right = tmp;
      (*tree)->parent = tmp->parent;
      tmp->parent = *tree;

      if ((*tree)->parent != NULL) {
        if (tmp == (*tree)->parent->left)
          (*tree)->parent->left = *tree;
        else
          (*tree)->parent->right = *tree;
      }

      return TRUE;
    }
  }

  return FALSE;
}

static int split(aatree_t** tree) {
  if (tree == NULL || *tree == NULL)
    return PTR_ERR;

  if ((*tree)->right != NULL && (*tree)->right->right != NULL) {
    if ((*tree)->right->right->level == (*tree)->level) {
      aatree_t* tmp = *tree;

      *tree = tmp->right;
      tmp->right = (*tree)->left;
      if (tmp->right != NULL)
        tmp->right->parent = tmp;
      (*tree)->left = tmp;
      (*tree)->parent = tmp->parent;
      tmp->parent = *tree;
      (*tree)->level++;

      if ((*tree)->parent != NULL) {
        if (tmp == (*tree)->parent->left)
          (*tree)->parent->left = *tree;
        else
          (*tree)->parent->right = *tree;
      }

      return TRUE;
    }
  }

  return FALSE;
}

int Insert(aatree_t** root, int data) {
  aatree_t* node = (aatree_t*)malloc(sizeof(aatree_t)), *tmpPar = NULL, **tmp = NULL;

  if (node == NULL)
    return MEM_ERR;

  if (root == NULL) {
    free(node);
    return PTR_ERR;
  }

  node->key = data;
  node->left = NULL;
  node->right = NULL;
  node->level = 1;
  if (*root == NULL) {
    node->parent = NULL;
  }
  else {
    tmp = root;
    while (*tmp != NULL) {
      tmpPar = *tmp;
      if ((*tmp)->key < data) {
        tmp = &((*tmp)->right);
      }
      else if ((*tmp)->key > data) {
        tmp = &((*tmp)->left);
      }
      else {
        free(node);
        return FALSE;
      }
    }

    *tmp = node;
    node->parent = tmpPar;
  }

  while (node->parent != NULL) {
    node = node->parent;
    skew(&node);
    split(&node);
  }

  *root = node;

  return TRUE;
}

aatree_t* Find(aatree_t* root, int data) {
  while (root != NULL) {
    if (root->key > data)
      root = root->left;
    else if (root->key < data)
      root = root->right;
    else
      return root;
  }

  return NULL;
}

static aatree_t* findMax(aatree_t* root) {
  if (root == NULL)
    return NULL;

  while (root->right != NULL)
    root = root->right;

  return root;
}

int Delete(aatree_t** root, int data, aatree_t* tree) {
  aatree_t* tmp = NULL, *nodeToDel = NULL;

  if (root == NULL)
    return PTR_ERR;

  if (tree == NULL)
    return FALSE;

  nodeToDel = Find(tree, data);
  if (nodeToDel != NULL) {
    if (nodeToDel->left == NULL && nodeToDel->right == NULL) {
      if (nodeToDel->parent != NULL) {
        if (nodeToDel == nodeToDel->parent->left)
          nodeToDel->parent->left = NULL;
        else
          nodeToDel->parent->right = NULL;
      }
      else {
        *root = NULL;
      }
    }
    else if (nodeToDel->left != NULL && nodeToDel->right == NULL) {
      if (nodeToDel->parent != NULL) {
        nodeToDel->left->parent = nodeToDel->parent;
        if (nodeToDel == nodeToDel->parent->left)
          nodeToDel->parent->left = nodeToDel->left;
        else
          nodeToDel->parent->right = nodeToDel->left;
      }
      else {
        *root = nodeToDel->left;
        (*root)->parent = NULL;
      }
    }
    else if (nodeToDel->right != NULL && nodeToDel->left == NULL) {
      if (nodeToDel->parent != NULL) {
        nodeToDel->right->parent = nodeToDel->parent;
        if (nodeToDel == nodeToDel->parent->left)
          nodeToDel->parent->left = nodeToDel->right;
        else
          nodeToDel->parent->right = nodeToDel->right;
      }
      else {
        *root = nodeToDel->right;
        (*root)->parent = NULL;
      }
    }
    else {
      tmp = findMax(nodeToDel->left);
      nodeToDel->key = tmp->key;
      Delete(root, tmp->key, (nodeToDel->left));

      return TRUE;
    }

    tmp = nodeToDel;
    while (tmp->parent != NULL) {
      int l, l2;

      tmp = tmp->parent;

      if (tmp->left == NULL && tmp->right == NULL)
        l = 0;
      else if (tmp->left != NULL && tmp->right == NULL)
        l = tmp->left->level;
      else if (tmp->left == NULL && tmp->right != NULL)
        l = tmp->right->level;
      else {
        l = tmp->left->level;
        l2 = tmp->right->level;
        if (l2 < l)
          l = l2;
      }

      if (l < tmp->level - 1) {
        tmp->level--;
        if (tmp->right != NULL && tmp->right->level > tmp->level)
          tmp->right->level = tmp->level;
        skew(&tmp);
        skew(&tmp->right);
        if (tmp->right != NULL)
          skew(&tmp->right->right);
        split(&tmp);
        split(&tmp->right);
      }
    }

    if(tmp != nodeToDel)
      *root = tmp;

    free(nodeToDel);
    return TRUE;
  }

  return FALSE;
}

void Clear(aatree_t** root) {
  while ((*root) != NULL)
    Delete(root, (*root)->key, *root);
}