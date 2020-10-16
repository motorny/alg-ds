#pragma once

#include "Parser.h"
#include "Structure.h"


void ShowMenu(); 
int PrintAll(ListNode* head); //return count of printed
int PrintByDate(ListNode* head, int date);
int ReadData(ListNode* head); // read to head sorted
