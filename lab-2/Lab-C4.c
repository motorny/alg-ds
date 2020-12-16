// BFS algorithm in C

#include <stdio.h>
#include <stdlib.h>
//#include <io.h>
#include <ctype.h>
#define SIZE 300
#pragma warning (disable:4996)

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int);

struct Graph {
    int numVertices;
    struct node** adjLists; // массив односвязанных списков
    int* visited;
};

// BFS algorithm
void bfs(struct Graph* graph, int startVertex) {
    struct queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        //printQueue(q);
        int currentVertex = dequeue(q);
        // printf("Visited %d\n", currentVertex);
        printf("%d ", currentVertex);

        struct node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Creating a node
struct node* createNode(int v) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Creating a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode, * nextNode;

    // Add edge from src to dest
    newNode = createNode(dest);
    if (graph->adjLists[src] == NULL) {
        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;
    }
    else if (graph->adjLists[src]->vertex > dest) {
        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;
    }
    else {
        nextNode = graph->adjLists[src];
        while (nextNode->next != NULL) {
            if (nextNode->next->vertex > dest) break;
            nextNode = nextNode->next;
        }
        newNode->next = nextNode->next;
        nextNode->next = newNode;
    }

    // Add edge from dest to src
    newNode = createNode(src);
    if (graph->adjLists[dest] == NULL) {
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    }
    else if (graph->adjLists[dest]->vertex > src) {
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    }
    else {
        nextNode = graph->adjLists[dest];
        while (nextNode->next != NULL) {
            if (nextNode->next->vertex > src) break;
            nextNode = nextNode->next;
        }
        newNode->next = nextNode->next;
        nextNode->next = newNode;
    }
}
// Create a queue
struct queue* createQueue() {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
    if (q->rear == SIZE - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Removing elements from queue
int dequeue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    }
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            //printf("Resetting queue ");
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Print the queue
void printQueue(struct queue* q) {
    int i = q->front;

    if (isEmpty(q)) {
        printf("Queue is empty");
    }
    else {
        printf("\nQueue contains \n");
        for (i = q->front; i < q->rear + 1; i++) {
            printf("%d ", q->items[i]);
        }
    }
}


int main() {

    int num, i = 0, a_1, b_1;
    char tmp, a[20], b[20];
    scanf("%i", &num);
    struct Graph* graph = createGraph(num);

    tmp = getchar();
    while (tmp != EOF) {

        i = 0;
        while (isspace(tmp)) {
            tmp = getchar();
        }
        while (isdigit(tmp)) {
            a[i] = tmp;
            i++;
            tmp = getchar();
        }
        a[i] = '\0';

      i = 0;
        while (isspace(tmp)) {
            tmp = getchar();
        }
        while (isdigit(tmp)) {
            b[i] = tmp;
            i++;
            tmp = getchar();
        }
        b[i] = '\0';

        a_1 = atoi(a);
        b_1 = atoi(b);

        addEdge(graph, a_1, b_1);

        tmp = getchar();
    }

    bfs(graph, 0);

    return 0;
}