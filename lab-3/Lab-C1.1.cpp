#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef char bool_t;

typedef struct{
	int nbrNum;
	int *neighbors;
	bool_t visited;
}node_t;

typedef struct{
	int size;
	node_t* node;
}graph_t;

graph_t* Create(int size){
	graph_t* graph = (graph_t*)malloc(sizeof(graph));
	int i;
	if(graph==NULL){
		return NULL;
	}
	graph->size=size;
	graph->node=(node_t*)malloc(size*sizeof(node_t));
	for(int i=0; i<size; i++){
		graph->node[i].nbrNum=0;
		graph->node[i].visited=0;
		graph->node[i].neighbors=(int*)calloc(size,sizeof(int));
	}
	return graph;
}

void Destroy(graph_t* graph){
	int i;
	if(graph==NULL){
		return;
	}
	for(int i=0; i<graph->size; i++){
		free(graph->node[i].neighbors);
	}
	
	free(graph->node);
	free(graph);
}

void GetLine(graph_t* graph){
	int i=0, index=0, n, line=0;
	char c=' ', num[10];
	scanf("%d%c", &line, &c);
		while(c==' '){
			scanf("%d%c", &n, &c);
				if(n!=line){
					graph->node[line].neighbors[graph->node[line].nbrNum] = n;
					graph->node[line].nbrNum++;
					if(line!=0){
						graph->node[n].neighbors[graph->node[n].nbrNum] = line;
						graph->node[n].nbrNum++;
					}
					
				}
		}
}

void Input(graph_t* graph){
	int i, j;
	for(i=0; i<graph->size; i++){
		GetLine(graph);
	}
}

void PrintBranch(graph_t* graph, int start) {
    int i, nbr;
	if (graph==NULL){
		return;
	}
    graph->node[start].visited = (bool_t)1;
    printf("%d ", start);
    for (i = 0; i < graph->node[start].nbrNum; i++){
    	nbr=graph->node[start].neighbors[i];
    	if (!graph->node[nbr].visited){
    		PrintBranch(graph, nbr);
		} 
	}
    
}

void Print(graph_t* graph){
	PrintBranch(graph, 0);
}

void PrintGraph(graph_t* graph){
	int i, j;
	for(i=0;i<graph->size; i++){
		for(j=0;j<graph->size; j++){
			printf("%d ", graph->node[i].neighbors[j]);
		}
		printf("\n");
	}
}

int main(void){
	graph_t* graph;
	int size, i;
	scanf("%d", &size);
	graph=Create(size);
	Input(graph);
	//PrintGraph(graph);
	Print(graph);
	Destroy(graph);
	return 0;
}

#ifdef __cplusplus
}
#endif
