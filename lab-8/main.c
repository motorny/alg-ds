#include "HashTable.h"

int main(void) {
	hashTable_t* table = CreateHashTable();

	while (1) {
		int i = 0, num = 0;
		char function = getchar();
		char ch;
		char str[STR_SIZE];
		if (function == EOF || function == '\n')
			break;

        //scanf("%d", &num);

		ch = getchar();
		while (isspace(ch)){
			ch = getchar();
		}
		while (ISDIGIT(ch)) {
			str[i++] = ch;
			ch = getchar();
		}
		str[i] = '\0';

		//choosing operator
		if (function == 'a')
			AddStr(table, str);
		else if (function == 'r')
			DeleteStr(table, str);
		else if (function == 'f') {
			if (FindStr(table, str))
				printf("yes\n");
			else
				printf("no\n");
		}

        //function = getchar(); //get "\n" at the end of str
	}

	DestroyTable(table);
	return 0;
}