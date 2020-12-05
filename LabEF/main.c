#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)
#ifdef LabE
int WordLength(char* word) {
  int i = 0;
  int counter = 0;
  while (word[i] != '\0') {
    ++counter;
    ++i;
  }
  return counter;
}

int CompareWords(char* w1, char* w2) {
  int i = 0;
  while (w1[i] == w2[i] && w1[i] != '\0' && w2[i] != '\0') {
    ++i;
  }
  if (w1[i] == '\0' && w2[i] != '\0') {
    return -1;
  }
  else if (w1[i] != '\0' && w2[i] == '\0') {
    return 1;
  }
  else if (w1[i] == '\0' && w2[i] == '\0') {
    return 0;
  }
  else {
    return w1[i] > w2[i] ? 1 : -1;
  }
}

void PrintWord(char* word) {
  int i = 0;
  while (word[i] != '\0') {
    printf("%c", word[i]);
    ++i;
  }
}

char* CopyWord(char* word) {
  int i = 0;
  char* newWord = malloc(sizeof(char) * (WordLength(word) + 1));
  while (word[i] != '\0') {
    newWord[i] = word[i];
    ++i;
  }
  newWord[i] = '\0';
  return newWord;
}
#endif

#ifdef LabF
int CompareIntervals(interval_t a, interval_t b) {
  if (a.left > b.left) {
    return 1;
  }
  else if (a.left < b.left) {
    return -1;
  }
  else {
    if (a.right > b.right) {
      return 1;
    }
    else if (a.right < b.right) {
      return -1;
    }
    else {
      return 0;
    }
  }
}

interval_t CopyInterval(interval_t data) {
  return data;
}

void PrintInterval(interval_t data) {
  printf("(%.2lf, %.2lf)", data.left, data.right);
}

#endif

int main() {
  tree_t* t = TreeCreate();
  char op = 1;
#ifdef LabE
  char data[100];
  SetCompareFunc(&CompareWords);
  SetDataWidthCounter(&WordLength);
  SetPrintDataFunc(&PrintWord);
  SetDataCopyFunc(&CopyWord);
  SetFreeDataFunc(&free);
#endif

#ifdef LabF
  interval_t data;
  SetCompareFunc(&CompareIntervals);
  SetDataCopyFunc(&CopyInterval);
  SetPrintDataFunc(&PrintInterval);
#endif

  while (1) {
    op = getchar();
    if (op == EOF) {
      break;
    }
#ifdef LabE
    scanf("%s", data);
#endif
#ifdef LabF
    scanf("%lf %lf", &data.left, &data.right);
#endif
    getchar();
    switch (op) {
    case 'a':
      TreeInsert(t, data);
      break;
    case 'f':
      if (TreeSearch(t, data)) {
        printf("yes\n");
      }
      else {
        printf("no\n");
      }
      break;
    case 'r':
      TreeDelete(t, data);
      break;
    default:
      break;
    }
    TreePrint(t);
  }
#ifdef LabF
  while (1) {
    printf("Enter interval cooridinates (format: right left):\n");
    scanf("%lf %lf", &data.left, &data.right);
    FindIntersect(t, data);
  }
#endif

  TreeFree(t);

  return 0;
}