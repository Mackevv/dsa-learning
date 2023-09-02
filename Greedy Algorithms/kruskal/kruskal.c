#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define MAX_EDGES 100

typedef struct Edge {
  int source, destination, weight;
} Edge;

// Create Union Find data structure for kruskal's algorithm

typedef struct Subset {
  int parent;
  int rank; // Rank or depth of tree
} Subset;

int find(Subset subsets[], int element)
{
  if (element != subsets[element].parent) {
    // Path compression: Make every visited node point directly to the root
    subsets[element].parent = find(subsets, subsets[element].parent);
  }
  return subsets[element].parent;
}

void union_sets(Subset subsets[], int x, int y)
{
  int rootX = find(subsets, x);
  int rootY = find(subsets, y);

  // If x and y are already in the same set
  if (rootX == rootY) return;

  if (subsets[rootX].rank < subsets[rootY].rank) {
    subsets[rootX].parent = rootY;
  } else if (subsets[rootX].rank > subsets[rootY].rank) {
    subsets[rootY].parent = rootX;
  } else {
    subsets[rootY].parent = rootX;
    subsets[rootX].rank++;
  }
}

// Kruskal's algorithm

int compare(const void *a, const void *b)
{
  return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

Edge *kruskal(Subset subsets[], Edge edges[], int numNodes, int numEdges) 
{
  Edge result[MAX_NODES];
  int resultIndex = 0;

  qsort(edges, numEdges, sizeof(edges[0]), compare);

  for (int i = 0; i < numEdges; i++) {
    int rootSource = find(subsets, edges[i].source);
    int rootDestination = find(subsets, edges[i].destination);

    // If including this edges create a cycle (two nodes are already in the same set)
    // don't add them to the minimum spanning tree
    if (rootSource != rootDestination) {
      result[resultIndex++] = edges[i];
      union_sets(subsets, rootSource, rootDestination);
    }
  }

  // Print the minimum spanning tree
  printf("Minimum spanning tree:\n");
  for (int i = 0; i < resultIndex; i++) {
    printf("%d - %d (W: %d)\n", result[i].source, result[i].destination, result[i].weight);
  }
}

int main() {
  int numNodes = 5;
  int numEdges = 7;

  Subset subsets[MAX_NODES];
  Edge edges[MAX_EDGES];

  for (int i = 0; i < numNodes; i++) {
    subsets[i].parent = i;
    subsets[i].rank = 0;
  }

  edges[0].source = 0;
  edges[0].destination = 1;
  edges[0].weight = 2;

  edges[1].source = 0;
  edges[1].destination = 2;
  edges[1].weight = 4;

  edges[2].source = 1;
  edges[2].destination = 2;
  edges[2].weight = 1;

  edges[3].source = 1;
  edges[3].destination = 3;
  edges[3].weight = 3;

  edges[4].source = 2;
  edges[4].destination = 3;
  edges[4].weight = 5;

  edges[5].source = 2;
  edges[5].destination = 4;
  edges[5].weight = 6;

  edges[6].source = 3;
  edges[6].destination = 4;
  edges[6].weight = 7;

  kruskal(subsets, edges, numNodes, numEdges);

  return 0;
}
