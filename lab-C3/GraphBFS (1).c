
#include <stdio.h>
#include <stdlib.h>
#include "GraphBFS.h"
#include "Queue.h"

#pragma warning (disable:4996)

struct vertex
{
    int vertex_id;
    char visited;
    struct vertex* next;
};

struct Graph
{
    int vertex_count;
    struct vertex** adjLists;
};

struct Graph* createGraph(int vertex_count);
struct vertex* createVertex(int);
void addEdge(struct Graph* graph, int src, int dest);
void destroyGraph(struct Graph* graph);

void printGraph(struct Graph* graph);


int main()
{
    int vertex_count;
    int vertex_id;
    int adj_vertex_id;
    char c;
 

    scanf("%d", &vertex_count);
    struct Graph* graph = createGraph(vertex_count);
  

    for (int i = 0; i < vertex_count; i++) {
        //Read vertex id from line
        scanf("%i%c", &vertex_id, &c);
        // Read the list of adj vertex, if it present
        while(c != '\n' && c != 'EOF') {
            scanf("%i%c", &adj_vertex_id, &c);
            addEdge(graph, vertex_id, adj_vertex_id);
        }
    }


    //struct Graph* graph = createGraph(10);
    struct queue* Q = initQueue();

    //addEdge(graph, 0, 2);
    //addEdge(graph, 0, 4);
    //addEdge(graph, 0, 6);
    //addEdge(graph, 1, 3);
    //addEdge(graph, 1, 8);
    //addEdge(graph, 2, 5);
    //addEdge(graph, 2, 8);
    //addEdge(graph, 3, 4);
    //addEdge(graph, 3, 6);
    //addEdge(graph, 3, 9);
    //addEdge(graph, 4, 5);
    //addEdge(graph, 4, 6);
    //addEdge(graph, 4, 9);
    //addEdge(graph, 5, 7);
    //addEdge(graph, 8, 9);

    //printGraph(graph);



    appendQueueItem(Q, 0);
    
    graph->adjLists[0]->visited = 1;
    printf("%d", graph->adjLists[0]->vertex_id);

//    while (Q->current != NULL) {
    //Пока в очереди есть оть один элемент
   while (Q->count) {
       //Получаем первый элемент очереди
        vertex_id = getCurrentQueueItem(Q);
        //Перебираем и Добавляем в очередь все его смежные вершины, недобавленные ранее
        struct vertex* temp = graph->adjLists[vertex_id]->next;
        while (temp)
        {
            if (!graph->adjLists[temp->vertex_id]->visited) {
                appendQueueItem(Q, temp->vertex_id);
                graph->adjLists[temp->vertex_id]->visited = 1;
                printf(" %d", temp->vertex_id);

            }

            //if (!graph->adjLists[vertex_id]->visited) {
            //    appendQueueItem(Q, temp->vertex_id);
            //    graph->adjLists[temp->vertex_id]->visited = 1;
            //}
            temp = temp->next;
        }
        shiftCurrentQueueItem(Q);
        //printf("\n");

   }

   destroyQueue(Q);
   destroyGraph(graph);
    return 0;
}




struct vertex* createVertex(int v)
{
    struct vertex* newVertex = (struct vertex*) malloc(sizeof(struct vertex));
    newVertex->vertex_id = v;
    newVertex->visited = 0;
    newVertex->next = NULL;
    return newVertex;
}

struct Graph* createGraph(int vertex_count)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->vertex_count = vertex_count;

    graph->adjLists = malloc(vertex_count * sizeof(struct vertex*));

    int i;
    for (i = 0; i < vertex_count; i++)
        graph->adjLists[i] = createVertex(i);

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    struct vertex* v_tmp;
    // Add edge from src to dest
    struct vertex* newVertex = createVertex(dest);
    
    v_tmp = graph->adjLists[src]->next;
    while (v_tmp != NULL && v_tmp->next != NULL) {
        v_tmp = v_tmp->next;
    }

    if (v_tmp == NULL) {
        //If it is the first Edge for vertex src
        graph->adjLists[src]->next = newVertex;
    }
    else {
        v_tmp->next = newVertex;
    }



    // Add edge from dest to src
    newVertex = createVertex(src);
 
    v_tmp = graph->adjLists[dest]->next;
    if (v_tmp != NULL && v_tmp->next != NULL) {
        v_tmp = v_tmp->next;
    }

    if (v_tmp == NULL) {
        //If it is the first Edge for vertex src
        graph->adjLists[dest]->next = newVertex;
    }
    else {
        v_tmp->next = newVertex;
    }


}

void destroyList(struct vertex* v) {
    if (v->next) destroyList(v->next);
    free(v);
}


void destroyGraph(struct Graph* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if(graph->adjLists[i]->next) destroyList(graph->adjLists[i]->next);
    }
    free(graph);
};



void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->vertex_count; v++)
    {
        struct vertex* temp = graph->adjLists[v]->next;
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex_id);
            temp = temp->next;
        }
        printf("\n");
    }
}