#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define plus 1024
#pragma warning(disable: 4996)

typedef struct vertex {
	int pt;
	struct vertex* left;
	struct vertex* right;
	struct vertex* elders;
}vertex;

char* scanString() {
	char* string = NULL;
	char* p = NULL;
	int size = plus;
	int k = 0;
	string = (char*)malloc(plus * sizeof(char));
	if (!string)
		return NULL;
	while ((string[k] = fgetc(stdin)) != EOF) {
		k++;
		if (k >= size) {
			p = (char)realloc(string, (size + plus) * sizeof(char));
			size += plus;
		}
		if (p)
			string = p;
		else
			return NULL;

	}
	string[k] = 0;
	return string;
}

vertex* getVertex(vertex* elders, int pt) {
	vertex* temp = (vertex*)malloc(sizeof(vertex));
	if (temp) {
		temp->left = NULL;
		temp->right = NULL;
		temp->elders = elders;
		temp->pt = pt;
	}
	return temp;
}
void binTreeWreck(vertex* binTree) {
	if (binTree) {
		binTreeWreck(binTree->left);
		binTreeWreck(binTree->right);
		free(binTree);
	}
}

void vertexSum(vertex** core, int pt) {

	if ((*core) == NULL) {
		(*core) = getVertex(NULL, pt);
		return;
	}
	vertex* temp = (*core);
	while (temp) {
		if (pt > temp->pt) {
			if (temp->right) {
				temp = temp->right;
				continue;
			}
			else {
				temp->right = getVertex(temp, pt);
				return;
			}
		}
		else if (pt < temp->pt) {
			if (temp->left) {
				temp = temp->left;
				continue;
			}
			else {
				temp->left = getVertex(temp, pt);
				return;
			}
		}
		else if (pt == temp->pt)
			return;
	}

}
vertex* detectVertex(vertex* core, int pt) {
	while (core) {
		if (pt > core->pt) {
			core = core->right;
			continue;
		}
		else if (pt < core->pt) {
			core = core->left;
		}
		else {
			return core;
		}
	}
	return NULL;
}

void eraseVertexByPt(vertex** core, int pt) {
	vertex* temp = NULL;
	vertex** res;
	if (core) {
		while (*core) {
			if (pt > (*core)->pt) {
				(core) = &((*core)->right);
			}
			else if (pt < (*core)->pt) {
				(core) = &((*core)->left);
			}
			else {
				temp = (*core);
				if (!(*core)->left && !(*core)->right)
					(*core) = NULL;
				else if (!(*core)->left)
					(*core) = (*core)->right;
				else if (!(*core)->right)
					(*core) = (*core)->left;
				else {
					res = &(*core)->left;
					while ((*res)->right)
						res = &(*res)->right;
					(*core)->pt = (*res)->pt;
					temp = *res;
					(*res) = (*res)->left;
				}
				free(temp);
			}

		}
	}

}

int main(void) {
	char* string = scanString();
	char* tstring;
	char patch = 0;
	int  digit = -1;
	int k = 0;


	vertex* binTree = NULL;
	tstring = strtok(string, "\n");
	while (tstring != NULL) {
		if (sscanf(tstring + k++, "%c", &patch));
		if (sscanf(tstring + k, "%i", &digit));
		k = 0;
		switch (patch)
		{
		case 'a':
			vertexSum(&binTree, digit);
			break;
		case 'f':
			if (detectVertex(binTree, digit))
				printf("yes\n");
			else
				printf("no\n");
			break;
		case 'r':
			eraseVertexByPt(&binTree, digit);
			break;
		}
		tstring = strtok(NULL, "\n");
	}

	free(string);
	binTreeWreck(binTree);
	return 0;
}