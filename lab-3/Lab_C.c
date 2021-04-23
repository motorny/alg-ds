#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

void ReadMatrContest(unsigned **M, unsigned *M_size)
{
  char Buf[300];
  int point = 0;
  scanf("%i\n", M_size); // load size
  //init mem
  *M = malloc(*M_size * *M_size * sizeof(unsigned));
  memset(*M, 0, *M_size * *M_size * sizeof(unsigned));
  for (point = 0; point < *M_size; point++)
  {
    int second = 0;
    char *ptr = Buf;
    char *endptr = Buf;
    gets(Buf);
    while (TRUE)
    {
      while (isspace(*ptr))
        ptr++;
      second = strtod(ptr, &endptr);
      if (ptr == endptr)
        break;
      ptr = endptr;
      (*M)[point * *M_size + second] = 1;
      (*M)[second * *M_size + point] = 1;
    }
  }
}

char* NextLine(char* Str, char Symb)
{
  int len = strlen(Str);
  int i;
  for (i = 0; i < len; i++)
    if (Str[i] == Symb)
      return Str + i;
  return NULL;
}

void ReadMatrStr(char *String, unsigned** M, unsigned* M_size)
{
  int point = 0;
  char *line_begin;
  char* line_end;
  int VerteciesLoaded = 0;
  if (sscanf(String, "%i", M_size) != 1)
    return;
  if (*M_size <= 0)
  { 
    *M_size = 0;
    return;
  }
  //init mem
  *M = malloc(*M_size * *M_size * sizeof(unsigned));
  memset(*M, 0, *M_size * *M_size * sizeof(unsigned));

  // Setup Second line. If non exist -> Error
  line_begin = NextLine(String, '\n') + 1;
  if (line_begin == String + 1)
  {
    free(*M);
    *M = NULL;
    *M_size = 0;
    return;
  }
  line_end = NextLine(line_begin, '\n');
  if (line_end == NULL)
  {
    free(*M);
    *M = NULL;
    *M_size = 0;
    return;
  }
  // for each line
  while (line_end != NULL)
  {
    int p1;
    char *ptr = NextLine(line_begin, ' '); // Setup pointer on second number
    p1 = atoi(line_begin);                 // Get first number
    do {
      int p2;
      if (ptr == NULL || ptr >= line_end) // if we ended with this line -> go out
        break;
      p2 = atoi(ptr);                     // Get number from pointer
      if (p1 >= *M_size || p2 >= *M_size) // if bad number given
      {
        free(*M);
        *M = NULL;
        *M_size = 0;
        return;
      }
      (*M)[p1 * *M_size + p2] = 1;        // Setup matrix with first number and current
      (*M)[p2 * *M_size + p1] = 1;
    } while (ptr = NextLine(ptr + 1, ' '));  // Get next number in line
    line_begin = line_end + 1;            // setup next line
    line_end = NextLine(line_begin, '\n'); // setup next line
    VerteciesLoaded++;
  }
  if (line_begin != String + strlen(String)) //if someone forgot to put \n at the last line
  {
    int p1;
    char* ptr = NextLine(line_begin, ' ');
    line_end = strlen(String) + String;
    p1 = atoi(line_begin);
    do {
      int p2;
      if (ptr == NULL || ptr >= line_end) // if we ended with this line -> go out
        break;
      p2 = atoi(ptr);
      if (p1 >= *M_size || p2 >= *M_size) // if bad number given
      {
        free(*M);
        *M = NULL;
        *M_size = 0;
        return;
      }
      (*M)[p1 * *M_size + p2] = 1;
      (*M)[p2 * *M_size + p1] = 1;
    } while (ptr = NextLine(ptr + 1, ' '));
    line_begin = line_end + 1;
    VerteciesLoaded++;
  }
  if (VerteciesLoaded != *M_size)
  {
    free(*M);
    *M = NULL;
    *M_size = 0;
    return;
  }
}

void DFS(unsigned *M, unsigned M_size, unsigned point, unsigned *markings)
{
  int counter = 0;
  int i;
  if (markings == NULL || M == NULL || M_size < 1 || point < 0)
    return;
  markings[point] = 1;
  for (i = 0; i < M_size; i++)
    if (M[point * M_size + i])
      counter++;
  printf("%i ", point);
  if (counter == 1)
    return;
  for (i = 0; i < M_size; i++)
    if (M[point * M_size + i] && i != point && !markings[i])
    {
      DFS(M, M_size, i, markings);
    }
}

void PrintDFS(char* String)
{
  unsigned* M = NULL;
  unsigned M_size = 0;
  unsigned* Markings;
  if (String == NULL || String[0] == NULL)
    return;
  ReadMatrStr(String, &M, &M_size);
  if (M == NULL || M_size <= 0)
    return;
  Markings = malloc(M_size * sizeof(unsigned));
  memset(Markings, 0, M_size * sizeof(unsigned));

  DFS(M, M_size, 0, Markings);
  printf("\n");

  free(Markings);
  free(M);
}
/*
int main(void)
{
  return 0;
}
*/