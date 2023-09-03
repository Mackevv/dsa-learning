#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../lib/heap.h"

#define V 7

typedef enum boolean {
  false,
  true
} bool;

void dijkstra(int graph[V][V], int start)
{
  int dist[V];
  int prev[V];
  bool visited[V];
  Heap *heap = make_heap(V);

  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    visited[i] = false;
  }

  dist[start] = 0;
  visited[start] = true;

  insert_key(heap, start);

  while (heap->size > 0) {
    int u = extract_min(heap);
    visited[u] = true;

    for (int v = 0; v < V; v++) {
      if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        insert_key(heap, v);
      }
    }
  }

  // Print distances
  printf("Vertex\t\t\t");
  for (int i = 0; i < V; i++) {
    printf("%d ", i);
  }
  printf("\n");

  printf("Distance from source\t");
  for (int i = 0; i < V; i++) {
    printf("%d ", dist[i]);
  }

  free(heap->items);
  free(heap);
}

int main()
{
  int graph[V][V] = {
    {0, 1, 2, 0, 0, 0, 0},
    {1, 0, 0, 2, 0, 3, 0},
    {2, 0, 0, 3, 4, 0, 0},
    {0, 2, 3, 0, 2, 3, 3},
    {0, 0, 4, 2, 0, 0, 5},
    {0, 3, 0, 3, 0, 0, 4},
    {0, 0, 0, 3, 5, 4, 0}
  };

  dijkstra(graph, 0);

  return 0;
}