#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"

int ReadGraph() {
	int ch = 0, i = 0;
	int iRib = 0, iAdj = 0;
	char str[100];

	ch = getchar();
	if (ch == EOF) {
		return 0;
	}
	while (ch != '\n') {
		if (ch == EOF) {
			return 0;
		}
		str[i++] = ch;
		ch = getchar();
	}
	str[i] = 0;
	data.vertexCount = atoi(str);
	data.vertex = (state*)malloc(sizeof(state) * data.vertexCount + 1);
	if (data.vertex == NULL) {
		return 0;
	}
	for (i = 0; i < data.vertexCount; i++) {
		data.vertex[i] = notVisited;
	}
	data.ribs = (int**)malloc(sizeof(int*) * data.vertexCount * data.vertexCount);
	for (i = 0; i < data.vertexCount * data.vertexCount; i++) {
		data.ribs[i] = (int*)malloc(sizeof(int) * 2);
		if (data.ribs == NULL) {
			return 0;
		}
	}
	i = 0;
	ch = getchar();
	while (ch != EOF) {
		if (ch == ' ' || ch == '\n') {
			str[i] = 0;
			data.ribs[iRib][iAdj++] = atoi(str);
			i = 0;
		}
		else {
			str[i++] = ch;
		}
		if (ch == '\n') {
			iAdj = 0;
			iRib++;
		}
		ch = getchar();
	}
	data.ribsCount = iRib;
	return 1;
}

branch DeepFirstSearch(int vertex, branch ans) {
	int vertices = data.vertexCount;
	data.vertex[vertex] = visited;
	countShadedVert++;
	ans.answer[ans.ansIndex++] = vertex;

	while (countShadedVert != data.vertexCount) {
		for (int i = 0; i < data.ribsCount; i++) {
			if (data.ribs[i][0] == vertex &&
				data.vertex[data.ribs[i][1]] == notVisited &&
				data.ribs[i][1] < vertices)
			{
				vertices = data.ribs[i][1];
			}
			if (data.ribs[i][1] == vertex &&
				data.vertex[data.ribs[i][0]] == notVisited &&
				data.ribs[i][0] < vertices)
			{
				vertices = data.ribs[i][0];
			}
		}
		if (vertices != data.vertexCount) {
			ans = DeepFirstSearch(vertices, ans);
			vertices = data.vertexCount;
		}
		else {
			return ans;
		}
	}
	return ans;
}

void clearGraph() {
	free(data.vertex);
	for (int i = 0; i < data.vertexCount * data.vertexCount; i++) {
		free(data.ribs[i]);
	}
	free(data.ribs);
}


