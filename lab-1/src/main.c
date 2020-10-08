#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "join.h"
static void Generate(const char* f,int n) {
	FILE* f1 = fopen(f, "wb");
	srand(time(NULL));
	WriteToFile(f1, n);
	fclose(f1);
}

static void Print(const char* fn) {
	struct Data first;
	FILE* f = fopen(fn, "rb");
	while (fread(&first, sizeof(struct Data), 1, f)) {
		printf("%i\n%s\n%s\n\n", first.int_field, first.str_field1, first.str_field2);
	}
	fclose(f);
}

static void JoinFiles(const char* fb1, const char* fb2, const char* fr) {
	struct Data data;
	struct Node* first;
	struct List list1 = { NULL,0 };
	struct List list2 = { NULL,0 };
	struct List list3 = { NULL,0 };
	FILE* f = fopen(fb1, "rb");
	while (fread(&data, sizeof(struct Data), 1, f)) {
		Add(&list1, &data);
	}
	freopen(fb2, "rb", f);
	while (fread(&data, sizeof(struct Data), 1, f)) {
		Add(&list2, &data);
	}
	list3 = Join(&list1, &list2);
	first = list3.first;
	freopen(fr, "wb", f);
	while (first) {
		fwrite(&(first->data), sizeof(struct Data), 1, f);
		first = first->next;
	}
	fclose(f);
}

int main(int argc, const char* argv[]) {
	switch (argc)
	{
	case 2:
		Print(argv[1]);
		break;
	case 3:
		Generate(argv[1], atoi(argv[2]));
		break;
	case 4:
		JoinFiles(argv[1], argv[2], argv[3]);
		break;
	default: 
		fprintf(stderr, "Programm must be called wuth parametres");
		return 1;
	}
	return 0;
}