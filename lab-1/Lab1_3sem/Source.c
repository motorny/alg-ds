#define _CRT_SECURE_NO_WARNINGS

#include "listInit.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>


void PrintList(myList *man)
{
  while (man != NULL)
  {
    printf("%s %s %s\n", man->surname, man->name, man->patron);
    man = man->next;
  }
}

int main(void) {
  myList* start = NULL;
  myList* nMan = NULL;
  FILE* file = NULL;
  SNP snp;
  char buf[20];
  char* word;
  file = fopen("D:\\Programms\\ForLab1_3sem\\List.txt", "r");
  
  if (file == NULL) {
      printf("The file manList wasn't open");
      return 0;
  }

  //ВВодим первого в список
  fscanf(file, "%s", snp.surname);
  fscanf(file, "%s", snp.name);
  fscanf(file, "%s", snp.patron);
  
  start = InitList(snp.surname, snp.name, snp.patron);
  ////
  
  
  while (!feof(file)) {
    fscanf(file, "%s", snp.surname);
    fscanf(file, "%s", snp.name);
    fscanf(file, "%s", snp.patron);
    nMan = Add2List(&start, snp);
  }
  
  PrintList(start);
  DeleteList(start);
  fclose(file);
  return 0;
}
