#include "Parser.h"
void FillPtrStr(strPtr ptr, char* content, int count)
{
	for (int i = 0; i < count;i++)
	{
		ptr[i] = content;
	}
}

#pragma warning(push) //запомнить состояние 
#pragma warning(disable:6386) // выключить предупреждение
strPtr ParseString(char* string, char* separator, int ElemCount)
{
	strPtr PtrArray;
	char *ptr1, *ptr2; // between ptr2 && ptr1 must be a word
	int wordlen; //word length without '\n'
	int CurElemCount = 0;
	int strlenSep = strlen(separator);
	PtrArray = (strPtr)malloc(sizeof(str) * (ElemCount+1));
	if (PtrArray == NULL) 
		return NULL;
	else
	{
		PtrArray[ElemCount] = NULL;
		char* newPtr;
		ptr1 = string;
		ptr2 = FindSubstr(separator, ptr1); // find separator
		while (CurElemCount < ElemCount)
		{
			if (ptr2 != NULL)
			{
				wordlen = (int)(ptr2 - ptr1); // if separator is found -> get wordlen to malloc and copy
				newPtr = (char*)malloc(sizeof(char) * (wordlen + 1));
				if (newPtr == NULL) return NULL;
				else
				{
					newPtr[wordlen] = '\0';
					StrCpyN(newPtr, ptr1, wordlen);
					PtrArray[CurElemCount] = newPtr;
					ptr1 = ptr2 + strlenSep;
					ptr2 = FindSubstr(separator, ptr1);
				}
			}
			else
			{
				wordlen = strlen(ptr1); // if separator isn't found -> all left is a last word
				newPtr = (char*)malloc(sizeof(char) * (wordlen + 1));
				if (newPtr == NULL) return NULL;
				else
				{
					newPtr[wordlen] = '\0';
					StrCpyN(newPtr, ptr1, wordlen);
					PtrArray[CurElemCount] = newPtr;
				}
				break; //stop
			}
			CurElemCount++;
		}
	}
	return PtrArray;
}
#pragma warning(pop) //вернуть состояние

int StrCpyN(char* destination, char* origin, int N) // copy first N chars
{
	int count = 0; // count of coppied syms
	for (;count < N; count++)
	{
		destination[count] = origin[count];
	}
	return count;
}

char* FindSubstr(char* substr, char* origin) 
{
	int i = 0;
	char* substr2 = substr; // ptr to begin of substr

	int strlenO = strlen(origin);
	int strlenS = strlen(substr);
	if (strlenS > strlenO) return NULL; // it seems like an error	

	for (;i <= strlenO-strlenS;i++)
	{
		if (IsSubstrHere(substr2, origin))
			return origin;
		else
			origin++;
	}

	return NULL;
}

int IsSubstrHere(char* substr, char* origin) // Просматривает, есть ли в начале строки подстрока
{
	
	int strlenO = strlen(origin);
	int strlenS = strlen(substr);
	if (strlenS > strlenO) return 0; // error
	
	for (int i = 0; i < strlenS; i++)
	{
		if (substr[i] != origin[i]) return 0; //no substr here
	}
	return 1; //substr is here yeah!!
}
int strlen(char* str) 
{
	char g;
	int i = 0;
	while ((g = str[i]) != '\0' && (g = str[i]) != EOF)
		i++;
	return i;
}