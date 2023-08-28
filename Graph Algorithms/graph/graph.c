#include <stdio.h>
#include <stdlib.h>

// ------------------------------------------
// Adjacency Matrix representation of a graph
// ------------------------------------------

#define V 4 // number of vertices of the graph

void init(int arr[V][V])
{
  int i, j;
  for (i = 0; i < V; i++) {
    for (j = 0; j < V; j++) {
      arr[i][j] = 0;
    }
  }
}

void add_edge(int arr[V][V], int i, int j)
{
  arr[i][j] = 1;
  arr[j][i] = 1;
}

void print_matrix(int arr[V][V])
{
  int i, j;
  for (i = 0; i < V; i++) {
    printf("| ");
    for (j = 0; j < V; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("|\n");
  }
}

// ----------------------------------------
// Adjacency list representation of a graph
// ----------------------------------------

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

void add_edge_g(Graph *graph, int i, int j)
{
  // Adding edge from vertex i to j
  Node *vertex = create_node(j);
  vertex->next = graph->adjLists[i];
  graph->adjLists[i] = vertex;

  //Adding edge from vertex j to i
  vertex = create_node(i);
  vertex->next = graph->adjLists[j];
  graph->adjLists[j] = vertex;
}

void print_graph(Graph *graph)
{
  for (int i = 0; i < graph->numVertices; i++) {
    printf("%d: ", i);
    Node *currentVertex = graph->adjLists[i];
    while (currentVertex != NULL) {
      printf("%d", currentVertex->vertex);
      currentVertex = currentVertex->next;
      if (currentVertex != NULL)
        printf(" -> ");
    }
    printf("\n");
  }
}

int main()
{
  // Adjacency matrix
  int adjMatrix[V][V];

  init(adjMatrix);
  add_edge(adjMatrix, 0, 2);
  add_edge(adjMatrix, 0, 3);
  add_edge(adjMatrix, 1, 2);
  add_edge(adjMatrix, 1, 3);

  printf("Adjacency matrix: \n");
  print_matrix(adjMatrix);
  printf("\n");

  // Adjacency list
  Graph *graph = create_graph(4);

  add_edge_g(graph, 0, 2);
  add_edge_g(graph, 0, 3);
  add_edge_g(graph, 1, 2);
  add_edge_g(graph, 1, 3);

  printf("Adjacency list: \n");
  print_graph(graph);
  printf("\n");

  return 0;
}