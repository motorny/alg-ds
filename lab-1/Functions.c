#include "Functions.h"

LST* CreateElement(int keyDigit, const char* word)
{
  LST* element;

  element = (LST*)malloc(sizeof(LST));

  if (element == NULL)
    return NULL;

  strcpy_s(element->word, MAX_WORD_SIZE, word);
  element->keyDigit = keyDigit;
  return element;
}

int AddElementToList(LST** list, int keyDigit, const char* word)
{
  if (word == NULL)
    return NULLPTR_STRING_ON_INPUT;

  //если список абсолютно пуст (создаем первый элемент и заполняем его)
  if ((*list) == NULL)
  {
    (*list) = CreateElement(keyDigit, word);

    if ((*list) == NULL)
      return NOT_ENOUGH_MEMORY;

    (*list)->ptrToNext = (*list);//конечный элемент указывает на себя
    return 0;
  }

  LST* currentElement = (*list),
    * previousElement = (*list),
    * newElement;

  //поиск места для нового элемента
  while (currentElement->ptrToNext != currentElement && currentElement->keyDigit < keyDigit)
  {
    previousElement = currentElement;
    currentElement = currentElement->ptrToNext;
  }

  if (currentElement->keyDigit == keyDigit)
    return MATCH_OF_KEY_NUMBERS;

  newElement = CreateElement(keyDigit, word);

  if (newElement == NULL)
    return NOT_ENOUGH_MEMORY;

  //ключ нового элемента меньше чем у текущего, вставляем новый элемент перед текущим
  if (currentElement->keyDigit > newElement->keyDigit)
  {
    newElement->ptrToNext = currentElement;

    if (currentElement == (*list))//текущий элемент - начальный
      (*list) = newElement;
    else
      previousElement->ptrToNext = newElement;
  }
  //вставляем новый элемент в конец, если его ключ самый большой
  else
  {
    newElement->ptrToNext = newElement;
    currentElement->ptrToNext = newElement;
  }

  return 0;
}

int FindElementInList(const LST* list, int keyDigit)
{
  const LST* temp = list;

  while (temp->ptrToNext != temp && temp->keyDigit < keyDigit)
  {
    temp = temp->ptrToNext;
  }

  return temp->keyDigit == keyDigit;
}

void DeleteList(LST* list)
{
  LST* temp,
    * next = list;
  do
  {
    temp = next;
    next = temp->ptrToNext;
    free(temp);
  } while (temp != next);
}

void PrintList(LST* list)
{
  LST* temp,
    * next = list;

  do
  {
    temp = next;
    next = temp->ptrToNext;
    printf("%s   %d\n", temp->word, temp->keyDigit);

  } while (temp->ptrToNext != temp);
}

int ReadFromFileToList(LST** list, const char* inputFileName)
{
  FILE* inputFile = NULL;
  int keyDigit = 0, err;
  char word[MAX_WORD_SIZE + 1];

  //Открываем файл
  fopen_s(&inputFile, inputFileName, "r");
  if (!inputFile)
  {
    return FILE_CANNOT_BE_OPENED;
  }

  //чтение из файла в список
  while (1)
  {
    if (fscanf_s(inputFile, "%s", word, MAX_WORD_SIZE) == EOF || fscanf_s(inputFile, "%d", &keyDigit) == EOF)
      break;

    err = AddElementToList(list, keyDigit, word);

    if (err)
      return err;
  }
  return 0;
}
