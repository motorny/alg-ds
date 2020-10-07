#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> 
#include"Skip_List.h"

int main() {
    long t;
    srand((int)time(0));
    SkipList* sl = CreateSkipList();

    t = GetTickCount();
    for (int i = 1; i <= 89; i++)
    {
        Insert(sl, i, i * 3);
        PrintSkipList(sl);
    }
    t = GetTickCount() - t;
    printf("Function time Incert  %ld milliseconds \n", t);

    for (int i = 1; i <= 23; i++)
    {
        Search(sl, i);
       printf("%d\n", Search(sl, i));
    }
    t = GetTickCount() - t;
    printf("Function time Search %ld milliseconds \n", t);

    t = GetTickCount();
    for (int i = 1; i <= 88; i++)
    {
         Delete(sl, i);
         PrintSkipList(sl);
    }
    t = GetTickCount() - t;
    printf("Function time Delete %ld milliseconds \n", t);

   

 
    return 0;
}
