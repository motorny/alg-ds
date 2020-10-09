#include "lab_A.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(void) {
	plenty_t* A, *B, *C;
	
	A = CreateZeroPlenty();
	FillPlenty(A, 10, 1);
	PrintPlenty(A);
	DelFromPlenty(A, 4, FIRST);
	PrintPlenty(A);

	DestroyPlenty(A);

	// enable memory leaks report
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	return 0;
}

