#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 1
#define FAIL 0
#define SIZE 100
#define INCORRECTINPUT -1





struct node
{
    int vertex;
    struct node* next;
};

struct queue {
    struct node* head, * tail;
};


struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* visited;
   
};



struct Graph* createGraph(int vertices)
{
    if (vertices < 0) {
        return NULL;
    }
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists =(struct node**) malloc(vertices * sizeof(struct node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
      
    }

    return graph;
}



static int initNode(struct node** head)
{
    *head = (struct node*)malloc(sizeof(struct node));
    if (*head == NULL)
        return FAIL;
    return SUCCESS;
}
struct node* add2Graph(struct node* head, int to)
{
    struct node* cur = head;
    
    if (head == NULL) {
        if (initNode(&head) == FAIL)
            return NULL;
        head->vertex = to;
        head->next = NULL;
    }
    else {
       while (cur->next != NULL)
            cur = cur->next;
        cur->next = (struct node*)malloc(sizeof(struct node));
        if (cur->next == NULL)
            return NULL;
        cur->next->vertex = to;
        cur->next->next = NULL;
    }
    return head;
}

void addEdge(struct Graph* graph, int src, int dest) 
{

    graph->adjLists[src] = add2Graph(graph->adjLists[src], dest);
    graph->adjLists[dest] = add2Graph(graph->adjLists[dest], src);

}



struct queue* createQueue(void) {
    struct queue* queue = (struct queue*)malloc(sizeof(struct queue));

    if (queue == NULL)
        return NULL;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

//Inserts item at start of queue
int pushQueue(struct queue* queue, int vertex) {
    if (queue == NULL)
        return FAIL;
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    if (tmp == NULL)
        return FAIL;
    tmp->vertex = vertex;
    tmp->next = NULL;
    if (queue->tail == NULL) {
        queue->head = tmp;
        queue->tail = tmp;
        return SUCCESS;
    }
    queue->tail->next = tmp;
    queue->tail = tmp;

    return SUCCESS;
}

//Returns item at front of queue and removes it from queue
int popQueue(struct queue* queue) {
    int result;
    struct node* tmp;

    if (queue == NULL || queue->head == NULL)
        return FAIL;
    tmp = queue->head;
    result = tmp->vertex;
    queue->head = queue->head->next;
    free(tmp);
    if (queue->head == NULL)
        queue->tail = NULL;

    return result;
}
void destroyQueue(struct queue* queue) {
    struct node* tmp;
    struct node* next;
    if (queue == NULL)
        return;

    tmp = queue->head;
    while (tmp != NULL) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(queue);
}

//Checks for empty queue
int isEmpty(struct queue* q)
{
    if (q->head == NULL)
        return 1;
    else
        return 0;
}

void bfs(struct Graph* graph, int startVertex)
{
    struct queue* q = createQueue();
    int curVertex;

    //Add to visited list and put in queue
    graph->visited[startVertex] = 1;
    pushQueue(q, 0);
    //Iterate while queue not empty
    while (!isEmpty(q)) {
        curVertex = popQueue(q);
        printf("%d ", curVertex);
       
        struct node* temp = graph->adjLists[curVertex];
        //Add all unvisited neighbours of current vertex to queue to be printed next
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            //Only add if neighbour is unvisited
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                pushQueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    destroyQueue( q);
}

struct Graph* readGraph(void) {
    char str[100];
    char* newStr = 0 , * endStr;
    int  vertices = 0;
    int src, dest;
    struct Graph* graph;

   
    fgets(str, 100, stdin);
    vertices = (int)strtod(str, &endStr);
    graph = createGraph(vertices);
    
    if (vertices == 1)
        return graph;


    while (1) {
        fgets(str, 100, stdin);
        if (str[0] != '\0') {
            newStr = str;
            //get first part of edge
            while (isspace(*newStr))
                newStr++;
            if (feof(stdin))
                return graph;
            if (*newStr < '0' || *newStr >'9') {
                graph->numVertices = INCORRECTINPUT;
                return graph;
            }
            src = (int)strtod(newStr, &endStr);
            newStr = endStr;
            //get second part of edge
            while (isspace(*newStr))
                newStr++;
            if (*newStr < '0' || *newStr >'9') {
                graph->numVertices = INCORRECTINPUT;
                return graph;
            }
            dest = (int)strtod(newStr, &endStr);
            newStr = endStr;

            addEdge(graph, src, dest);
            if (graph->adjLists[src] == NULL || graph->adjLists[dest] == NULL) {
                graph->numVertices = INCORRECTINPUT;
                return graph;
            }
            
            }
            //read to the end of string
            while (isspace(*newStr))
                newStr++;
        }
   

       //if (feof(stdin))
           return graph;
}

void freeGraph(struct Graph* graph) {
    if (graph->numVertices > 1) {
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjLists[i] != NULL)
                if (graph->adjLists[i]->next != NULL) {
                    while (graph->adjLists[i] != NULL) {
                        struct node* tmp = graph->adjLists[i];
                        graph->adjLists[i] = graph->adjLists[i]->next;
                        free(tmp);
                    }
                }
            free(graph->adjLists[i]);
           
        }
        free(graph->adjLists);
    }
    free(graph);
}

int main()
{
    struct Graph* graph;
    graph = readGraph();
    bfs(graph,0);
    freeGraph(graph);


    

   /* struct Graph* graph = createGraph(10);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 6);
    addEdge(graph, 0, 8);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 6);
    addEdge(graph, 2, 8);
    addEdge(graph, 2, 9);
    addEdge(graph, 3, 7);
    addEdge(graph, 4, 6);
    addEdge(graph, 4, 7);
    addEdge(graph, 4, 8);
    addEdge(graph, 5, 6);
    addEdge(graph, 7, 8);*/

   // bfs(graph, 0);

    return 0;
}