#include"bplus.h"

int main(void) {
  Bplus* root;
  root = Init();
	GetTreeFromConsole(&root);
  Destroy(&root);
  return 0;
}