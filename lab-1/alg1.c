#include "header.h"

int main() {
	LIST* list;
	FILE* f;
	int our_temp;
	int days_with_temp;
	fopen_s(&f, "average_temperature.txt", "r");

	if (f == NULL) {
		puts("The file can't be opened");
		return -1;
	}

	list = InitList();
	ReadFile(f, list);
	Print(list);
	fclose(f);

	puts("Enter your temperature:");
	scanf_s("%d", &our_temp);
	days_with_temp = Search(list, our_temp);
	printf("There is %d days with your temperature\n", days_with_temp);

	FreeList(list);
	system("pause");
	return 0;
}