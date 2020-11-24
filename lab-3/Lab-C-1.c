#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
#define NUMBER(ptr) ((*(ptr))>='0'&&(*(ptr))<='9')
#define MULTIPLIER 10 //to transform char data to int number
#define SIZE 300

typedef enum {
  FALSE,
  TRUE
} bool_t;

typedef struct elem_t {
  int vertex; //vertex's number
  struct elem_t* next;
} elem_t;

typedef struct {
  bool_t* isVisited; //mark visited vertexes in graph
  int numofvertexes;
  elem_t* lists;
}graph_t;

typedef struct {
  int top;
  int* numbers;
} visitedlist_t;

visitedlist_t graphOrder = { 0, (int*)NULL };

//read directed graph from stdin
graph_t* DirectedGraphRead() {
  bool_t firstnum = TRUE;
  char arr[SIZE], *cursor;
  int i;
  int vertexes = 0, vertexsnum = 0;
  graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
  elem_t* ptr = NULL;

  scanf("%i\n", &vertexes);

  if (!graph)
    return NULL;

  if (vertexes <= 0) {
    graph->numofvertexes = vertexes;
    graph->lists = NULL;
    graph->isVisited = NULL;
    return graph;
  }

  graphOrder.top = 0;
  graphOrder.numbers = (int*)malloc(vertexes * sizeof(int));
  if (!graphOrder.numbers) 
    return NULL;

  graph->isVisited = (bool_t*)malloc(vertexes * sizeof(bool_t));
  if (!graph->isVisited)
    return NULL;
  graph->numofvertexes = vertexes;
  graph->lists = (elem_t*)malloc(vertexes*sizeof(elem_t));
  if (!graph->lists)
    return NULL;

  for (i = 0; i < vertexes; i++) {
    graph->lists[i].vertex = i;
    graph->isVisited[i] = FALSE;
    fgets(arr, SIZE, stdin);
    cursor = arr;

    ptr = &(graph->lists[i]); //helping pointer
    ptr->next = NULL;
    while ((*cursor) != '\n') {
      //reading number
      if (NUMBER(cursor)) {

        if (firstnum == TRUE) {
          firstnum = FALSE;
          //skip first number
          while (NUMBER(cursor))
            cursor++;
        }

        else { //not first number, so elemets of list
          vertexsnum = 0;
          while (NUMBER(cursor)){
            vertexsnum = vertexsnum * MULTIPLIER + ((int)(*cursor)-(int)'0');
            cursor++;
          }
          ptr->next = (elem_t*)malloc(sizeof(elem_t));
          if (!ptr->next)
            return NULL;

          ptr = ptr->next;
          ptr->vertex = vertexsnum;
          ptr->next = NULL;
        }
      }

      else //isspace char but not '\n', skip it
        cursor++;
    }
    //line was ended, so next number will be first in next list
    firstnum = TRUE; 
  }

  return graph;
}

//transfrom oriented graph into undirected
graph_t* UndirectedGraphCreate(graph_t* graph) {
  bool_t isExists = FALSE;
  int i;
  elem_t* temp, *vertptr, *mallocptr;

  //for each vertex
  for (i = 0; i < graph->numofvertexes; i++) {
    isExists = FALSE;
    temp = &(graph->lists[i]);
    temp = temp->next;

    while (temp) {
      vertptr = &(graph->lists[temp->vertex]);
      isExists = FALSE;
      //check vertex in vertptr exists
      vertptr = vertptr->next;
      while (vertptr) {
        if (vertptr->vertex == graph->lists[i].vertex) {
          isExists = TRUE;
          break;
        }
        vertptr = vertptr->next;
      }

      //two cases: exists or not

      //not exists, need to add new vertex in undirected graph
      if (isExists == FALSE) {
        mallocptr = (elem_t*)malloc(sizeof(elem_t));

        if (!mallocptr) //delete graph in main fuction
          return NULL;
        

        mallocptr->vertex = graph->lists[i].vertex;
        mallocptr->next = NULL;

        //move back
        vertptr = &(graph->lists[temp->vertex]);

        //all edges come TO this vertex, not FROM
        
        while (vertptr->next) {
          //put new vertex
          if (vertptr->next->vertex > graph->lists[i].vertex) {
            mallocptr->next = vertptr->next;
            vertptr->next = mallocptr;
            break;
          }
          vertptr = vertptr->next;
        }

        if (!vertptr->next)
          vertptr->next = mallocptr;
      }

      //if exists, do nothing

      temp = temp->next;
    }
  }

  return graph;
}

void DFS(graph_t* graph, elem_t* elem) {
  if (graph->isVisited[elem->vertex] == TRUE)
    return;

  graph->isVisited[elem->vertex] = TRUE;
  graphOrder.numbers[graphOrder.top] = elem->vertex;
  graphOrder.top++;
  int i = 0;

  //need to such find vertex
  elem_t* ptr = &(graph->lists[i]);
  while (ptr->vertex != elem->vertex)
    ptr = &(graph->lists[++i]);

  while (ptr) {
    if (graph->isVisited[ptr->vertex] == FALSE) { //did not go there previously
      DFS(graph, ptr);
    }
    ptr = ptr->next;
  }
}

void DestroyGraph(graph_t* graph) {
  int i;
  elem_t* temp, *temp1;
  for (i = 0; i < graph->numofvertexes; ++i) {
    temp = graph->lists[i].next;
    while (temp) {
      temp1 = temp;
      temp = temp->next;
      free(temp1);
    }
  }
  if(graph->lists)
    free(graph->lists);
  if (graph->isVisited)
    free(graph->isVisited);
  if (graph)
    free(graph);
  if (graphOrder.numbers)
    free(graphOrder.numbers);
}

int main(void) {
  int i;
  graph_t* graph = DirectedGraphRead();

  if (!graph) {
    DestroyGraph(graph);
    return 1;
  }

  graph = UndirectedGraphCreate(graph);

  if (!graph || graph->numofvertexes <= 0) {
    DestroyGraph(graph);
    return 1;
  }

  DFS(graph, &(graph->lists[0]));

  for (i = 0; i < graphOrder.top; ++i)
    printf("%i ", graphOrder.numbers[i]);

  DestroyGraph(graph);
  return 0;
}