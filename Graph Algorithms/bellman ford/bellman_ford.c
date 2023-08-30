#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 999999

typedef struct Edge {
  int source;
  int destination;
  int weight;
} Edge;

typedef struct Graph {
  int V, E; // Number of vertices and edges
  Edge *edges;
} Graph;

Graph *create_graph(int V, int E)
{
  Graph *newGraph = (Graph*)malloc(sizeof(Graph));
  newGraph->V = V;
  newGraph->E = E;
  newGraph->edges = (Edge*)malloc(E * sizeof(Edge));

  return newGraph;
}

void bellman_ford(Graph *graph, int source)
{
  int V = graph->V;
  int E = graph->E;

  // Initialize distances array
  int distances[V];
  for (int i = 0; i < V; i++) {
    distances[i] = INF;
  }
  distances[source] = 0;

  // Relax edges |V| - 1 times
  for (int i = 1; i < V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = graph->edges[j].source;
      int v = graph->edges[j].destination;
      int w = graph->edges[j].weight;

      if (distances[u] + w < distances[v])
        distances[v] = distances[u] + w;
    }
  }

  // After |V| - 1 iterations, distances should not change anymore
  // therefore if changes occured in the next iteration, it means
  // we have a negative-weight cycle
  for (int i = 0; i < E; i++) {
    int u = graph->edges[i].source;
    int v = graph->edges[i].destination;
    int w = graph->edges[i].weight; 

    if (distances[u] + w < distances[v]) {
      printf("Graph contains negative-weight cycle.\n");
      return;
    }
  }

  // Print shortests paths
  printf("Vertex\t\t\t");
  for (int i = 0; i < V; i++) {
    printf("%d ", i);
  }
  printf("\n");

  printf("Distance from source\t");
  for (int i = 0; i < V; i++) {
    printf("%d ", distances[i]);
  }
}

int main() 
{
  int V, E;
  printf("Enter number of vertices and edges: ");
  scanf("%d %d", &V, &E);

  Graph* graph = create_graph(V, E);

  printf("Enter source, destination, and weight for each edge:\n");
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &graph->edges[i].source, &graph->edges[i].destination, &graph->edges[i].weight);
  }

  int source;
  printf("Enter source vertex: ");
  scanf("%d", &source);

  bellman_ford(graph, source);

  return 0;
}
