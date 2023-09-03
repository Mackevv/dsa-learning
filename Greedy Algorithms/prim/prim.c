#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../lib/heap.h"

typedef struct Node {
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct Graph {
    int V; // number of vertices in the graph
    Node **adjLists;
} Graph;

Node *create_node(int v, int w) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->weight = w;
  newNode->next = NULL;
  return newNode;
}

Graph *create_graph(int V) {
  Graph *newGraph = (Graph *)malloc(sizeof(Graph));
  newGraph->V = V;
  newGraph->adjLists = (Node **)malloc(V * sizeof(Node *));
  for (int i = 0; i < V; i++) {
    newGraph->adjLists[i] = NULL;
  }
  return newGraph;
}

void add_edge(Graph *graph, int src, int dest, int weight) {
  Node *newNode = create_node(dest, weight);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = create_node(src, weight);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

void prim(Graph *graph, Heap *heap) {
  int V = graph->V;
  int key[V];
  int parent[V];

  for (int i = 0; i < V; i++) {
    key[i] = INT_MAX;
    parent[i] = -1;
  }

  insert_key(heap, 0);
  key[0] = 0;

  while (heap->size > 0) {
    int u = extract_min(heap);

    Node *node = graph->adjLists[u];
    while (node != NULL) {
      int v = node->vertex;
      int weight = node->weight;

      if (weight < key[v]) {
        parent[v] = u;
        key[v] = weight;
        insert_key(heap, v);
      }

      node = node->next;
    }
  }

  // Print the minimum spanning tree
  printf("Edge \tWeight\n");
  for (int i = 1; i < V; i++) {
    printf("%d - %d \t%d\n", parent[i], i, key[i]);
  }

  free(heap->items);
  free(heap);
}

int main() {
  int V = 5;
  Graph *graph = create_graph(V);

  add_edge(graph, 0, 1, 2);
  add_edge(graph, 0, 3, 6);
  add_edge(graph, 1, 2, 3);
  add_edge(graph, 1, 3, 8);
  add_edge(graph, 1, 4, 5);
  add_edge(graph, 2, 4, 7);
  add_edge(graph, 3, 4, 9);

  prim(graph, make_heap(graph->V));

  // Free the memory
  for (int i = 0; i < graph->V; i++) {
    Node* current = graph->adjLists[i];
    while (current != NULL) {
      Node* next = current->next;
      free(current);
      current = next;
    }
  }
  free(graph->adjLists);
  free(graph);

  return 0;
}