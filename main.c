#include "list.h"

int main() {
	Node* pHead = NULL;
	FILE* pF;
	const int N = 24;
	if (pF = fopen("schedule.txt", "r")) {
		while (!feof(pF)) {
			pHead = readEntry(pHead, pF);
		}
		printMoreN(pHead,N);
		freeMem(pHead);
	}
	else printf("%s\n", "Can`t open file");
	_asm nop;
	return 0;
}