#pragma once
void StrSearchAnalys(SNP* searchSNP, char* search);
int SearchCompare(myList* man, SNP searchSNP);
myList** SearchInList(myList* start, SNP searchSNP);
void PrintSearch(myList** searchList);
void ClearSearch(myList** searchList);