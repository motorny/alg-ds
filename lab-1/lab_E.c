#include "lab_E.h"

static int FindKeyWord(char* str, char** key, int from, int to) {
	char* temp;
	int i = 0;
	char* data = *key;

	data = (char*)malloc(STEP_FOR_MALLOC);
	if (data == NULL)
		return -1;

	while (str[from] != SPACE && from <= to) {

		if ((i >= STEP_FOR_MALLOC - 1) && (i % STEP_FOR_MALLOC - 1 == 0)) {
			temp = (char*)realloc(data, 2 * STEP_FOR_MALLOC);
			if (temp != NULL)
				data = temp;
			else {
				free(data);
				return -1;
			}
		}

		data[i] = str[from];
		from++;
		i++;
	}
	
	data[i] = 0;

	*key = data;
	return from;
}
static int FindChildTree(char* str, char** childTree, int from, int to) {
	char* temp, *data = *childTree;
	int i = 0;
	int leftBracketCount = 1;
	data = (char*)malloc(STEP_FOR_MALLOC);
	if (data == NULL)
		return -1;
	
	while (str[from] != BRACKET_LEFT && from <= to)
		from++;
	from++;

	while (from <= to) {
		if (str[from] == BRACKET_LEFT) {
			leftBracketCount++;
		}
		if (str[from] == BRACKET_RIGHT) {
			if (leftBracketCount == 1)
				break;
			else
				leftBracketCount--;
		}
				
		if ((i >= STEP_FOR_MALLOC) && (i % STEP_FOR_MALLOC == 0)) {
			temp = (char*)realloc(data, 2 * STEP_FOR_MALLOC);
			if (temp != NULL)
				data = temp;
			else {
				free(data);
				return -1;
			}
		}

		data[i] = str[from];
		from++;
		i++;
	}

	data[i] = 0;
	*childTree = data;
	return from;
}

static node_t* FillTree(char* str, int from, int to) {
	if (from >= to)
		return NULL;

	char* key, *leftPart, *rightPart;
	int pos = from;
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
		return NULL;

	pos = FindKeyWord(str, &key, pos, to);
	newNode->keyWord = key;

	pos = FindChildTree(str, &leftPart, pos, to);
	newNode->left = FillTree(leftPart, 0, strlen(leftPart));

	pos = FindChildTree(str, &rightPart, pos, to);
	newNode->right = FillTree(rightPart, 0, strlen(rightPart));

	return newNode;
}
node_t* ReadTree(FILE* fp) {
	if (fp == NULL)
		return NULL;

	node_t* treeHead = NULL;
	int check;
	char* strNode = (char*)malloc(sizeof(char) * MAX_INPUT_STR);
	if (strNode == NULL)
		return NULL;

	check = fscanf(fp, "%99[^\n]", strNode);
	if (check == -1)
		return NULL;
	
	setlocale(LC_ALL, "Russian");
	treeHead = FillTree(strNode, 0, strlen(strNode));

	free(strNode);
	return treeHead;
}

static void PrintTreeCur(node_t* tree, int depth) {
	if (tree != NULL) {
		PrintTreeCur(tree->left, depth + 1);
		for (int i = 0; i < depth; ++i)
			printf("       ");
		printf("%s<\n", tree->keyWord);
		PrintTreeCur(tree->right, depth + 1);
	}
}

void PrintTree(node_t* tree) {
	PrintTreeCur(tree, 0);
}

void DestroyTree(node_t* t) {
	if (t == NULL)
		return;
	DestroyTree(t->left);
	DestroyTree(t->right);
	if (t->keyWord != NULL)
		free(t->keyWord);
	free(t);
}