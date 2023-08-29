#include <stdio.h>
#include <stdlib.h>
#include "lib/queue.h"

typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

typedef struct Graph {
  int numVertices;
  Node **adjLists;
} Graph;

Node *create_node(int v)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;

  return newNode;
}

Graph *create_graph(int numVertices)
{
  Graph *newGraph = (Graph*)malloc(sizeof(Graph));
  newGraph->numVertices = numVertices;
  newGraph->adjLists = (Node**)malloc(numVertices * sizeof(Node*));

  for (int i = 0; i < numVertices; i++) {
    newGraph->adjLists[i] = NULL;
  }

  return newGraph;
}

void add_edge(Graph *graph, int i, int j)
{
  Node *vertex = create_node(j);
  vertex->next = graph->adjLists[i];
  graph->adjLists[i] = vertex;

  vertex = create_node(i);
  vertex->next = graph->adjLists[j];
  graph->adjLists[j] = vertex;
}

void breadth_first_search(Graph *graph, int firstVertex)
{
  Queue *q = create_queue(graph->numVertices);

  int *visited = (int*)malloc(graph->numVertices * sizeof(int));
  for (int i = 0; i < graph->numVertices; i++)
    visited[i] = 0;

  enqueue(q, firstVertex);

  while (q->front != -1) {
    int currentVertex = dequeue(q);

    if (!visited[currentVertex]) {
      printf("%d ", currentVertex);
      visited[currentVertex] = 1;
    }

    Node *temp = graph->adjLists[currentVertex];
    while (temp != NULL) {
      if (!visited[temp->vertex])
        enqueue(q, temp->vertex);

      temp = temp->next;
    }
  }
  free(visited);
  free(q);
}

int main()
{
  Graph *graph = create_graph(5);
  add_edge(graph, 0, 2);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 4);

  printf("Breadth-First Traversal starting from vertex 0:\n");
  breadth_first_search(graph, 0);

  return 0;
}