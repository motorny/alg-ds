#include "hesh.h"

int main() {
	int size = 10000;
	hash_table_t* table = CreateTable(size);
	ConsoleTable(&table);
	return 0;
}