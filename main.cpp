
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define DUBLICATE 1
#define MAX 4
#define MIN 2
int f = 0;

struct btreeNode {
  int val[MAX + 1], count;
  struct btreeNode* link[MAX + 1];
};

typedef struct btreeNode btreeNode;

btreeNode* root;

btreeNode* createNode(int val, btreeNode* child) {
  btreeNode* newNode = (btreeNode*)malloc(sizeof(btreeNode));
  newNode->val[1] = val;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

void addValToNode(int val, int pos, btreeNode* node, btreeNode* child) {
  int j = node->count;
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
}


void splitNode(int val, int* pval, int pos, btreeNode* node, btreeNode* child, btreeNode** newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (btreeNode*)malloc(sizeof(btreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    addValToNode(val, pos, node, child);
  }
  else {
    addValToNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

int setValueInNode(int val, int* pval, btreeNode* node, btreeNode** child) {

  int pos;
  if (!node) {
    *pval = val;
    *child = NULL;
    return 1;
  }

  if (val < node->val[1]) {
    pos = 0;
  }
  else {
    for (pos = node->count;
      (val < node->val[pos] && pos > 1); pos--);
    if (val == node->val[pos]) {
      return DUBLICATE;
    }
  }
  if (setValueInNode(val, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      addValToNode(*pval, pos, node, *child);
    }
    else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}


void insertion(int val) {
  int result, i;
  btreeNode* child;

  result = setValueInNode(val, &i, root, &child);
  if (result)
    root = createNode(i, child);
}


void copyNodes(btreeNode* myNode, int pos) {
  btreeNode* node;
  node = myNode->link[pos];

  for (; node->link[0] != NULL;)
    node = node->link[0];
  myNode->val[pos] = node->val[1];

}


void removeVal(btreeNode* myNode, int pos) {
  int i = pos + 1;
  while (i <= myNode->count) {
    myNode->val[i - 1] = myNode->val[i];
    myNode->link[i - 1] = myNode->link[i];
    i++;
  }
  myNode->count--;
}


void doRightShift(btreeNode* myNode, int pos) {
  btreeNode* Right = myNode->link[pos];
  int j = Right->count;

  while (j > 0) {
    Right->val[j + 1] = Right->val[j];
    Right->link[j + 1] = Right->link[j];
  }
  Right->val[1] = myNode->val[pos];
  Right->link[1] = Right->link[0];
  Right->count++;

  Right = myNode->link[pos - 1];
  myNode->val[pos] = Right->val[Right->count];
  myNode->link[pos] = Right->link[Right->count];
  Right->count--;
  return;
}


void doLeftShift(btreeNode* myNode, int pos) {
  int j = 1;
  btreeNode* Left = myNode->link[pos - 1];

  Left->count++;
  Left->val[Left->count] = myNode->val[pos];
  Left->link[Left->count] = myNode->link[pos]->link[0];

  Left = myNode->link[pos];
  myNode->val[pos] = Left->val[1];
  Left->link[0] = Left->link[1];
  Left->count--;

  while (j <= Left->count) {
    Left->val[j] = Left->val[j + 1];
    Left->link[j] = Left->link[j + 1];
    j++;
  }
  return;
}


void mergeNodes(btreeNode* myNode, int pos) {
  int j = 1;
  btreeNode* Left = myNode->link[pos], * Right = myNode->link[pos - 1];

  Right->count++;
  Right->val[Right->count] = myNode->val[pos];
  Right->link[Right->count] = myNode->link[0];

  while (j <= Left->count) {
    Right->count++;
    Right->val[Right->count] = Left->val[j];
    Right->link[Right->count] = Left->link[j];
    j++;
  }

  j = pos;
  while (j < myNode->count) {
    myNode->val[j] = myNode->val[j + 1];
    myNode->link[j] = myNode->link[j + 1];
    j++;
  }
  myNode->count--;
  free(Left);
}

void adjustNode(btreeNode* myNode, int pos) {
  if (!pos) {
    if (myNode->link[1]->count > MIN) {
      doLeftShift(myNode, 1);
    }
    else {
      mergeNodes(myNode, 1);
    }
  }
  else {
    if (myNode->count != pos) {
      if (myNode->link[pos - 1]->count > MIN) {
        doRightShift(myNode, pos);
      }
      else {
        if (myNode->link[pos + 1]->count > MIN) {
          doLeftShift(myNode, pos + 1);
        }
        else {
          mergeNodes(myNode, pos);
        }
      }
    }
    else {
      if (myNode->link[pos - 1]->count > MIN)
        doRightShift(myNode, pos);
      else
        mergeNodes(myNode, pos);
    }
  }
}

int delValFromNode(int val, btreeNode* myNode) {
  int pos, flag = 0;
  if (myNode) {
    if (val < myNode->val[1]) {
      pos = 0;
      flag = 0;
    }
    else {
      for (pos = myNode->count;
        (val < myNode->val[pos] && pos > 1); pos--);
      if (val == myNode->val[pos]) {
        flag = 1;
      }
      else {
        flag = 0;
      }
    }
    if (flag) {
      if (myNode->link[pos - 1]) {
        copyNodes(myNode, pos);
        flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
      }
      else {
        removeVal(myNode, pos);
      }
    }
    else {
      flag = delValFromNode(val, myNode->link[pos]);
    }
    if (myNode->link[pos]) {
      if (myNode->link[pos]->count < MIN)
        adjustNode(myNode, pos);
    }
  }
  return flag;
}

void deletion(int val, btreeNode* myNode) {
  btreeNode* tmp;
  if (!delValFromNode(val, myNode)) {
    return;
  }
  else {
    if (myNode->count == 0) {
      tmp = myNode;
      myNode = myNode->link[0];
      free(tmp);
    }
  }
  root = myNode;
  return;
}

void searching(int val, int* pos, btreeNode* myNode) {
  if (!myNode) {
    return;
  }

  if (val < myNode->val[1]) {
    *pos = 0;
  }
  else {
    for (*pos = myNode->count;
      (val < myNode->val[*pos] && *pos > 1); (*pos)--);
    if (val == myNode->val[*pos]) {
      f = 1;
      return;
    }
  }
  searching(val, pos, myNode->link[*pos]);
  return;
}

int main() {

  char c, operation, number[1024];
  int index = 0, data, v = 0;

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
      insertion(data);
      break;
    }
    case 'r':
    {
      deletion(data, root);
      break;
    }
    case 'f':
    {
      searching(data, &v, root);
      if (f)
        printf("yes\n");
      else
        printf("no\n");
      f = 0;
    }
    }
    if (c == '\n')
    {
      c = getchar();
    }
  }
}
