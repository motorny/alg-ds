#include "C2.h"

#pragma warning (disable:4996)

node_t* CreateGraph(int n, int* err) {
  node_t* nodes = (node_t*)malloc(sizeof(node_t) * n);
  int i;

  if (*err != 0)
    return NULL;

  if (nodes != NULL) {
    for (i = 0; i < n; i++) {
      nodes[i].edgesQ = 0;
      nodes[i].color = WHITE;
      nodes[i].edges = NULL;
    }
  }
  else
    (*err)++;

  return nodes;
}

void AddEdge(node_t* node1, node_t* node2, int *err) {
  edge_t* edge1 = (edge_t*)malloc(sizeof(edge_t));
  edge_t* edge2 = (edge_t*)malloc(sizeof(edge_t));
  edge_t *edgeCur;

  if (*err != 0)
    return;

  if (edge1 != NULL && edge2 != NULL) {
    node1->edgesQ++;
    edge1->node = node2;
    edge1->next = NULL;
    edgeCur = node1->edges;
    if (edgeCur == NULL)
      node1->edges = edge1;
    else {
      while (edgeCur->next != NULL)
        edgeCur = edgeCur->next;
      edgeCur->next = edge1;
    }

    node2->edgesQ++;
    edge2->node = node1;
    edge2->next = NULL;
    edgeCur = node2->edges;
    if (edgeCur == NULL)
      node2->edges = edge2;
    else {
      while (edgeCur->next != NULL)
        edgeCur = edgeCur->next;
      edgeCur->next = edge2;
    }
  }
  else
    (*err)++;
}

void DestroyGraph(node_t* nodes, int n) {
  edge_t *edgeCur, *edgeNext;
  int i;

  for (i = 0; i < n; i++) {
    edgeCur = nodes[i].edges;
    while (edgeCur != NULL) {
      edgeNext = edgeCur->next;
      free(edgeCur);
      edgeCur = edgeNext;
    }
  }
  free(nodes);
}

node_t* FillFromStream(FILE* fp, int *n, int* err) {
  node_t *nodes;
  int i, j;

  if (fp != NULL && *err == 0) {
    fscanf(fp, "%i", n);
    nodes = CreateGraph(*n, err);
    while (!feof(fp) && *err == 0) {
      fscanf(fp, "%i %i", &i, &j);
      AddEdge(&nodes[i], &nodes[j], err);
    }
  }
  else
    (*err)++;

  return nodes;
}

void PrintEdges(node_t* nodes, int n) {
  edge_t *edgeCur;
  int i;

  for (i = 0; i < n; i++) {
    edgeCur = nodes[i].edges;
    while (edgeCur != NULL) {
      printf("%i %i\n", i, edgeCur->node - nodes);
      edgeCur = edgeCur->next;
    }
  }
}

static void _DFS(int* i, int* ans, int nodeNum, node_t* nodes, int n) {
  edge_t *edgeCur = nodes[nodeNum].edges;

  ans[(*i)++] = nodeNum;
  nodes[nodeNum].color = GRAY;
  while (edgeCur != NULL) {
    if (edgeCur->node->color == WHITE)
      _DFS(i, ans, edgeCur->node - nodes, nodes, n);
    edgeCur = edgeCur->next;
  }
  nodes[nodeNum].color = BLACK;
}

void RunDFS(int* ans, node_t* nodes, int n) {
  int i = 0, nodeNum = 0;

  _DFS(&i, ans, nodeNum, nodes, n);

  for (nodeNum = 0; nodeNum < n; nodeNum++) {
    if (nodes[nodeNum].color == WHITE)
      _DFS(&i, ans, nodeNum, nodes, n);
  }
}

void PrintDFS(int* ans, int n) {
  int i;

  printf("%i", ans[0]);
  for (i = 1; i < n; i++)
    printf(" %i", ans[i]);
  printf("\n");
}