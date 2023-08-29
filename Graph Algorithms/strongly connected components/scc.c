#include <stdio.h>
#include <stdlib.h>
#include "lib/stack.h"

// Implement directed graph to find strongly
// connected components using kosaraju's algorithm

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    int numVertices;
    Node **adjLists;
} Graph;

Node *create_node(int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph *create_graph(int numVertices) {
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;
    newGraph->adjLists = (Node **)malloc(numVertices * sizeof(Node *));
    for (int i = 0; i < numVertices; i++) {
        newGraph->adjLists[i] = NULL;
    }
    return newGraph;
}

void add_edge(Graph *graph, int i, int j) {
    Node *vertex = create_node(j);
    vertex->next = graph->adjLists[i];
    graph->adjLists[i] = vertex;
}

void first_dfs(Graph *graph, int vertex, int *visited, Stack *stack)
{
  visited[vertex] = 1;
  Node *adjList = graph->adjLists[vertex];
  while (adjList != NULL) {
    int neighbor = adjList->vertex;
    if (!visited[neighbor])
      first_dfs(graph, neighbor, visited, stack);

    adjList = adjList->next;
  }
  push(stack, vertex);
}

// Function to reverse the direction of all the graph's edges
Graph *transpose(Graph *graph) {
  Graph *transposedGraph = create_graph(graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++) {
      Node *current = graph->adjLists[i];
      while (current != NULL) {
        add_edge(transposedGraph, current->vertex, i);
        current = current->next;
      }
    }
  return transposedGraph;
}

void second_dfs(Graph *graph, int vertex, int *visited)
{
  printf("%d ", vertex);

  visited[vertex] = 1;
  Node *adjList = graph->adjLists[vertex];
  while (adjList != NULL) {
    int neighbor = adjList->vertex;
    if (!visited[neighbor])
      second_dfs(graph, neighbor, visited);

    adjList = adjList->next;
  }
}

void kosaraju(Graph *graph)
{
  int *visited = (int*)malloc(graph->numVertices * sizeof(int));
  Stack *stack = create_stack(graph->numVertices);

  for (int i = 0; i < graph->numVertices; i++) {
    visited[i] = 0;
  }

  // First depth first traversal to push the vertex in the stack
  for (int i = 0; i < graph->numVertices; i++) {
    if (!visited[i]) {
      first_dfs(graph, i, visited, stack);
    }
  }

  // Create a graph with the reversed edges 
  Graph *transposedGraph = transpose(graph);

  // Reset the visited array
  for (int i = 0; i < graph->numVertices; i++) {
    visited[i] = 0;
  }

  // Second depth first traversal and print the SCC
  printf("Strongly Connected Components:\n");
  while (!is_empty(stack)) {
    int vertex = pop(stack);
    if (!visited[vertex]) {
      second_dfs(transposedGraph, vertex, visited);
      printf("\n");
    }
  }

  free(visited);
  free(stack->items);
  free(stack);
}

int main() {
  Graph *graph = create_graph(8);

  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 0);
  add_edge(graph, 2, 3);
  add_edge(graph, 3, 4);
  add_edge(graph, 4, 5);
  add_edge(graph, 5, 3);
  add_edge(graph, 6, 5);
  add_edge(graph, 6, 7);

  kosaraju(graph);

  return 0;
}
