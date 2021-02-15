#include "Graph.h"

node_list_t* InitList(int nodeNum) {
	if (nodeNum < 1)
		return NULL;
	node_list_t* res = (node_list_t*)malloc(sizeof(node_list_t));
	if (res == NULL)
		return NULL;
	res->nodeNum = nodeNum;
	res->head = NULL;
	return res;
}

node_t* NewNode(int num) {
	if (num < 0)
		return NULL;
	node_t* res = (node_t*)malloc(sizeof(node_t));
	if (res == NULL )
		return NULL;
	res->edge_head = NULL;
	res->next = NULL;
	res->num = num;
	return res;
}

node_t* AddNode(node_list_t* list, node_t* node) {
	//if no nodes
	if (list->head == NULL) {
		list->head = node;
	}
	else {
		//if only 1 node
		if (list->head->next == NULL)
			if (node->num < list->head->num) {
				node->next = list->head;
				list->head = node;
			}
			else {
				if (node->num == list->head->num){
					FreeNode(node);
					return list->head;
				}
				else {
					list->head->next = node;
				}
				
			}
		//if >=2 nodes
		else {
			int key = node->num;
			node_t* temp1 = list->head;
			node_t* temp2 = list->head->next;

			//check if node is before list_head
			if (key < temp1->num) {
				node->next = temp1;
				list->head = node;
				return node;
			}
			else
				if (key == temp1->num) {
					FreeNode(node);
					return temp1;
				}

			//check if node in between of list head and list last
			int flag = 0;
			while (temp2 != NULL) {
				if (temp1->num < key && key < temp2->num) {
					flag = 1;
					break;
				}
				else {
					if (key == temp1->num) {
						FreeNode(node);
						return temp1;
					}
					else if (key == temp2->num) {
						FreeNode(node);
						return temp2;
					}
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}

			//flag == 1 => edge is in between of temp1 and temp2
			if (flag == 1) {
				temp1->next = node;
				node->next = temp2;
			}
			//flag == 0 => edge is after edge last
			else
			{
				temp1->next = node;
			}
		}
	}
	return node;
}

void FreeNode(node_t* node) {
	FreeEdgeList(node);
	free(node);
}

void FreeNodeList(node_list_t* list) {
	node_t* head = list->head;
	if (head == NULL)
		return;
	node_t* cur = head;
	node_t* next = head->next;
	do {
		FreeNode(cur);
		cur = next;
		if (cur!=NULL)
			next = cur->next;
	} while (cur != NULL);
}

edge_t* NewEdge(node_t* node) {
	if (node == NULL)
		return NULL;
	edge_t* res = (edge_t*)malloc(sizeof(edge_t));
	if (res == NULL)
		return NULL;
	res->node = node;
	res->next = NULL;
	return res;
}

void AddEdge(node_t* destination, edge_t* edge) {
	//if no edges
	if (destination->edge_head == NULL)
		destination->edge_head = edge;
	else {
		//if only 1 edge
		if (destination->edge_head->next==NULL)
			if (edge->node->num < destination->edge_head->node->num) {
				edge->next = destination->edge_head;
				destination->edge_head = edge;
			}
			else {
				if (edge->node->num == destination->edge_head->node->num) {
					FreeEdge(edge);
					return;
				}
				else {
					destination->edge_head->next = edge;
				}
			}
		//if >=2 edges
		else {
			int key = edge->node->num;
			edge_t* temp1 = destination->edge_head;
			edge_t* temp2 = destination->edge_head->next;
			
			//check if edge should be before edge_head
			if (key < temp1->node->num) {
				edge->next = temp1;
				destination->edge_head = edge;
				return;
			}
			else
				if (key == temp1->node->num) {
					FreeEdge(edge);
					return;
				}
					

			//check if edge in between of edge head and edge last
			int flag = 0;
			while (temp2 !=NULL) {
				if (temp1->node->num < key && key < temp2->node->num) {
					flag = 1;
					break;
				}
				else
					if (key == temp1->node->num || key == temp2->node->num) {
						FreeEdge(edge);
						return;
					}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			
			//flag == 1 => edge should be in between of temp1 and temp2
			if (flag == 1) {
				temp1->next = edge;
				edge->next = temp2;
			}
			//flag == 0 => edge should be after edge last
			else
			{
				temp1->next = edge;
			}
		}
	}
}

void FreeEdge(edge_t* edge) {
	free(edge);
}

void FreeEdgeList(node_t* node) {
	edge_t* head = node->edge_head;
	if (head == NULL)
		return;
	edge_t* cur = head;
	edge_t* next = head->next;
	do {
		FreeEdge(cur);
		cur = next;
		if (cur != NULL)
			next = cur->next;
	} while (cur != NULL);
}

void PrintNode(node_t* node) {
	printf("%d ", node->num);
}

void AttendNode(node_t* node, int* attendanceArray) {
	attendanceArray[node->num] = 1;
}

void DepthFirstSearch(node_list_t* list) {
	int nodeNum = list->nodeNum;
	int* attendanceArray = (int*)calloc(nodeNum, sizeof(int));
	if (attendanceArray == NULL)
		return;
	
	node_t* temp = list->head;

	while (temp != NULL) {
		SearchConnectedGraph(temp, attendanceArray);
		temp = temp->next;
	}

	free(attendanceArray);
}

BOOL IsAttended(node_t* node, int* attendanceArray) {
	if (node == NULL)
		return FALSE;
	return (BOOL) (attendanceArray[node->num] == 1);
}

void SearchConnectedGraph(node_t* node, int* attendanceArray) {
	if (node == NULL)
		return;
	if (IsAttended(node, attendanceArray))
		return;
	PrintNode(node);
	AttendNode(node, attendanceArray);

	edge_t* temp = node->edge_head;
	while (temp != NULL) {
		SearchConnectedGraph(temp->node, attendanceArray);
		temp = temp->next;
	}
}

