#include "Graph.h"

int main(void) {
	int nodeNum;
	int cur, next;

	scanf("%d", &nodeNum);
	
	node_list_t* list = InitList(nodeNum);
	if (list == NULL)
		return -1;

	while (!feof(stdin)) {
		scanf("%d %d", &cur, &next);
		node_t* node1 = NewNode(cur);
		node_t* node2 = NewNode(next);
		if (node1 == NULL || node2 == NULL)
			return -2;
		node1 = AddNode(list, node1);
		node2 = AddNode(list, node2);

		edge_t* edge1 = NewEdge(node2);
		edge_t* edge2 = NewEdge(node1);
		AddEdge(node1, edge1);
		AddEdge(node2, edge2);
	}

	DepthFirstSearch(list);

	FreeNodeList(list);
	return 0;
}