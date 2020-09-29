#include "List.h"

int main()
{
	LIST* a = initList();
	Bool searchItem;
	a = insertInList(a, 0);
	a = insertInList(a, 3);
	a = insertInList(a, 4);
	a = insertInList(a, 6);
	a = insertInList(a, 2);
	a = insertInList(a, 8);
	printList(a);
	searchItem = searchItemInList(a, 4);
	if (searchItem == TRUE)
	{
		printf_s("item was found\n");
	}
	else
	{
		printf_s("item was not found\n");
	}
	searchItem = searchItemInList(a, 7);
	if (searchItem == TRUE)
	{
		printf_s("item was found\n");
	}
	else
	{
		printf_s("item was not found\n");
	}

	LIST* b = initList();
	b = insertInList(b, 3);
	b = insertInList(b, 4);
	b = insertInList(b, 0);
	b = insertInList(b, 7);
	b = insertInList(b, 8);
	printList(b);

	LIST* inter = intersection(a, b);
	printList(inter);

	LIST* un = unionOfSets(a, b);
	printList(un);

	LIST* c = initList();
	LIST* d = initList();
	un = intersection(c, d);
	printList(un);

	delList(a);
	delList(b);
	delList(inter);
	delList(un);
	return 0;
}