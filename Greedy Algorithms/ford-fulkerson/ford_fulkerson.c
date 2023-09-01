#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6

typedef enum boolean {
  false,
  true
} bool;

int min(int a, int b)
{
  return (a < b) ? a : b;
}

bool bfs(int graph[V][V], int s, int t, int parent[])
{
  bool visited[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
  }

  visited[s] = true;
  parent[s] = -1;

  int queue[V];
  int front = 0, rear = 0;
  queue[rear] = s;
  rear++;

  while (front != rear) {
    int u = queue[front];
    front++;

    for (int v = 0; v < V; v++) {
      if (!visited[v] && graph[u][v] > 0) {
        visited[v] = true;
        parent[v] = u;
        queue[rear] = v;
        rear++;
      }
    }
  }
  return visited[t];
}

int ford_fulkerson(int graph[V][V], int s, int t)
{
  int u, v;
  int parent[V];

  int maxFlow = 0;

  // While there is a path from source to sink
  while (bfs(graph, s, t, parent)) {
    int pathFlow = INT_MAX;
    
    // Find the minimum residual capacity along the path found by bfs
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      pathFlow = min(pathFlow, graph[u][v]);
    }

    // Update residual capacities of edges and backward egdes
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      graph[u][v] -= pathFlow;
      graph[v][u] += pathFlow;
    }

    maxFlow += pathFlow;
  }

  return maxFlow;
}

int main()
{
  int graph[V][V] = {
    {0, 10, 0, 10, 0, 0},
    {0, 0, 4, 2, 8, 0},
    {0, 0, 0, 0, 0, 10},
    {0, 0, 0, 0, 9, 0},
    {0, 0, 6, 0, 0, 10},
    {0, 0, 0, 0, 0, 0}
  };

  int maxFlow = ford_fulkerson(graph, 0, 5);
  printf("Maximum flow: %d\n", maxFlow);

  return 0;
}