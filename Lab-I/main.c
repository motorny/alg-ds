#include"header.h"

int main(void) 
{
	Tree* root;
	root = Init();
	GetTreeFromConsole(&root);
	Destroy(&root);
	return 0;
}