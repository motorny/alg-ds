#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mergelists.h"

#pragma warning (disable:4996)

// Says, whether character is a letter (1) or not (0)
static int _isLetter(char ch) {
  if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    return 1;
  return 0;
}

// Returns lowercase ASCII code for uppercase letters
static char _upperIntoLower(char ch) {
  if (ch >= 'A' && ch <= 'Z')
    return ch + 32;
  return ch;
}

// Reads the sring character by character until meeting '\n' or EOF
static char* _readLine(FILE* fp, int* err) {
  int mul = 100, extra = 1;
  char* p = (char*)malloc(sizeof(char) * (mul + 1)), * q = p, * cur = p;

  if (*err != 0)
    return NULL;

  if (p != NULL) {
    if (fgets(p, mul + 1, fp) == NULL) {
      p[0] = 0;
      return p;
    }

    while (p[strlen(p) - 1] != '\n' && !feof(fp)) {
      q = (char*)realloc(p, sizeof(char) * (mul * (++extra) + 1));
      if (q != NULL) {
        p = q;
        cur = p + mul * (extra - 1);
        fgets(cur, mul + 1, fp);
      }
      else {
        (*err)++;
        break;
      }
    }
    if (p[strlen(p) - 1] == '\n')
      p[strlen(p) - 1] = 0;
  }

  else
    (*err)++;

  return p;
}

// Returns a pointer on a list, which consists only of a dummy
list_t* CreateList(int* err) {
  list_t* list;

  if (*err != 0)
    return NULL;

  list = (list_t*)malloc(sizeof(list_t));
  if (list != NULL) {
    list->words = NULL;
    list->next = NULL;
  }
  else
    (*err)++;

  return list;
}

// Frees the sublist node by node
static void _destroyLetter(list_t* p) {
  subList_t* subCur = p->words->next, * subNext;

  free(p->words);
  while (subCur != NULL) {
    subNext = subCur->next;
    free(subCur->word);
    free(subCur);
    subCur = subNext;
  }
  free(p);
}

// Frees the list node by node
void DestroyList(list_t* p) {
  list_t* cur = p->next, * next;

  free(p);
  while (cur != NULL) {
    next = cur->next;
    _destroyLetter(cur);
    cur = next;
  }
}

// Returns a pointer to a subnode before current word
subList_t* FindPlaceForWord(char* newWord, list_t* p, int* err) {
  subList_t* prev = p->words, * cur = prev->next;
  char letterCur, letterNew;
  int i, flagPlaceFound = 0;

  // Cycle for searching the right place for a new word in a sublist
  // Order is figured out by compairing ASCII codes of two letters
  while (cur != NULL) {
    for (i = 1; newWord[i] != 0; i++) {
      if (_isLetter(cur->word[i]) == 0 || _isLetter(newWord[i]) == 0) {
        (*err)++;
        return NULL;
      }
      letterCur = _upperIntoLower(cur->word[i]);
      letterNew = _upperIntoLower(newWord[i]);
      if (letterCur == 0 || letterCur < letterNew)
        break;
      if (letterCur > letterNew) {
        flagPlaceFound++;
        break;
      }
    }
    if (flagPlaceFound != 0)
      break;
    prev = cur;
    cur = cur->next;
  }

  return prev;
}

// Adds a word into sublist (into node "p") maintaining an alphabetical order
subList_t* AddWord(char* newWord, list_t* p, int* err) {
  subList_t* subp, * prev;

  if (*err != 0)
    return NULL;

  subp = (subList_t*)malloc(sizeof(subList_t));

  if (subp != NULL) {
    subp->word = newWord;
    prev = FindPlaceForWord(newWord, p, err);
    subp->next = prev->next;
    prev->next = subp;
  }
  else
    (*err)++;

  return subp;
}

// Adds new letter into alphabet after "p" 
// Returns its pointer
// Àlso creates its sublist (with dummy) - for words starting with this letter
list_t* AddLetter(char newLetter, list_t* p, int* err) {
  list_t* q;
  subList_t* subq;

  if (*err != 0)
    return NULL;

  q = (list_t*)malloc(sizeof(list_t));
  subq = (subList_t*)malloc(sizeof(subList_t));
  if (q != NULL && subq != NULL) {
    q->letter = newLetter;
    q->words = subq;
    subq->next = NULL;
    q->next = p->next;
    p->next = q;
  }
  else
    (*err)++;

  return q;
}

// If node for current word exists: returns its pointer, flagMatchFound == 1
// If node for current word doesn't exist: returns pointer for a node, which the current letter must follow after, flagMatchFound == 0
// Returns NULL in case of unknown mistake
list_t* FindLetterMatch(list_t* list, char letter, int* flagMatchFound, int*err) {
  list_t* prev = list, * cur = list->next;

  if (_isLetter(letter) == 0) {
    (*err)++;
    return NULL;
  }

  // Cycle searches, if the letter of current word already exist in a list
  while (cur != NULL) {
    if (_upperIntoLower(cur->letter) == letter) {
      (*flagMatchFound)++;
      return cur;
    }
    if (_upperIntoLower(cur->letter) > letter)
      return prev;
    prev = cur;
    cur = cur->next;
  };
  if (cur == NULL)
    return prev;

  return NULL;
}

// Fills list and its sublists, placing letters and words in alphabetical order
static list_t* _fillFromFile(char* filename, int* err) {
  FILE* fp;
  list_t* list, * cur;
  char* word;
  int flagMatchFound;

  fp = fopen(filename, "r");
  list = CreateList(err);

  // Cycle reads file line by line: FindLetterMatch() decides on a letter the word belong and AddWord() adds it to its sublist
  if (fp != NULL && *err == 0) {
    while (!feof(fp) && *err == 0) {
      flagMatchFound = 0;
      word = _readLine(fp, err);
      if (word[0] == 0 || (int)word[0] == EOF) {
        free(word);
        continue;
      }
      cur = FindLetterMatch(list, _upperIntoLower(word[0]), &flagMatchFound, err);
      if (flagMatchFound == 0)
        cur = AddLetter(_upperIntoLower(word[0]), cur, err);
      AddWord(word, cur, err);
    }
    fclose(fp);
  }
  else
    (*err)++;

  return list;
}

// Creates one list from two, maintaining an alphabetical order
list_t* MergeLists(list_t* list1, list_t* list2, int* err) {
  list_t* listNew, * cur;
  list_t* cur1 = list1->next, * cur2 = list2->next;
  list_t* cur2Next;
  subList_t* subCur, * subNext, *sub1Prev;
  char ch01, ch02;

  listNew = CreateList(err);
  cur = listNew;

  if (*err != 0)
    return NULL;

  // Cycle runs through both of lists, comparing their letters:
    // if letter of one list is bigger than letter of another, the first one becomes a node of a merged list
    // if letter of list1 equals letter of list2, all words of list2 goes to list1.
      //Then etter of list1 becomes a node of a merged list. Letter of list2 gets destroyed
  while (cur1 != NULL && cur2 != NULL && *err == 0) {
    ch01 = _upperIntoLower(cur1->letter);
    ch02 = _upperIntoLower(cur2->letter);
    if (ch01 == ch02) {
      subCur = cur2->words->next;
      free(cur2->words);
      while (subCur != NULL) {
        subNext = subCur->next;
        sub1Prev = FindPlaceForWord(subCur->word, cur1, err);
        subCur->next = sub1Prev->next;
        sub1Prev->next = subCur;
        subCur = subNext;
      }
      cur2Next = cur2->next;
      free(cur2);
      cur->next = cur1;
      cur1 = cur1->next;
      cur2 = cur2Next;
    }
    else if (ch01 < ch02) {
      cur->next = cur1;
      cur1 = cur1->next;
    }
    else if (ch01 > ch02) {
      cur->next = cur2;
      cur2 = cur2->next;
    }
    cur = cur->next;
  }
  if (cur1 != NULL)
    cur->next = cur1;
  else if (cur2 != NULL)
    cur->next = cur2;

  free(list1);
  free(list2);

  return listNew;
}

// Creates or fills a file with words of merged lists in alphabetical order
static void _writeToFile(char* filename, list_t* list, int err) {
  FILE* fp;
  list_t* p = list->next;
  subList_t* subq;

  fp = fopen(filename, "w");

  if (fp != NULL) {
    if (err == 0) {
      while (p != NULL) {
        subq = p->words->next;
        while (subq != NULL) {
          fprintf(fp, "%s\n", subq->word);
          subq = subq->next;
        }
        p = p->next;
      }
    }
    else {
      fprintf(fp, "Some problem prevented program from giving a result.\nPossible reasons:\n");
      fprintf(fp, "> lack of memory\n> wrong names of input files\n> incomparable characters (non-letters)\n");
      fprintf(fp, "Solve it and try again.\n");
    }
    fclose(fp);
  }
}
