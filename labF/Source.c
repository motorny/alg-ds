#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include"SectionTree.h"

int main(void) {
	int leftBorder = 0, rightBorder = 0;
	NODE* root = NULL;
	NODE** interMass = NULL;
	ConsoleTree(&root);
	printTreePreOrder(root, "root", 0);
	
	printf("Enter section that should be intered\n");
	scanf("%d %d", &leftBorder, &rightBorder);
	interMass = FindInterSegm(root, leftBorder, rightBorder);
	if (interMass != NO_MEMORY) {
		PrintSectMass(interMass);
		free(interMass);
	}
	else
		printf("Not enough memory");
	DestroyTree(&root);
	
	return 0;
}
