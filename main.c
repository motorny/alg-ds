#include <stdio.h>
#include "memallocator.h"

int main(){
  char* b[100];
  char a[1500];
  meminit(a, 1500);
  for (int i = 0; i < 100; i++){
    b[i] = (char*)memalloc(1);
  }

  for (int i = 0; i < 100; i++){
    memfree(b[i]);
  }
  return 0;
}