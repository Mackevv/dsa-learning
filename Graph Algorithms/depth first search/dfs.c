#include <stdio.h>
#include <stdlib.h>

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
  // Add edge from vertex i to j
  Node *vertex = create_node(j);
  vertex->next = graph->adjLists[i];
  graph->adjLists[i] = vertex;

  // Add edge from vertex j to i
  vertex = create_node(i);
  vertex->next = graph->adjLists[j];
  graph->adjLists[j] = vertex;
}

void depth_first_search(Graph *graph, int firstVertex)
{
  int visited[10] = {0};
  Node *stack[10];
  int top = 0;

  stack[top] = create_node(firstVertex);

  // While the stack isn't empty
  while (top != -1) {
    Node *currentVertex = stack[top];
    top--;
    int vertex = currentVertex->vertex;

    if (!visited[vertex]) {
      printf("%d ", vertex);
      visited[vertex] = 1;
    }

    // Add to the stack all unvisited adjacent vertex of current vertex
    Node *temp = graph->adjLists[vertex];
    while (temp != NULL) {
      if (!visited[temp->vertex]) {
        top++;
        stack[top] = temp;
      }
      temp = temp->next;
    }

    free(currentVertex);
  }
}

int main()
{
  Graph *graph = create_graph(7);
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 4);
  add_edge(graph, 2, 5);
  add_edge(graph, 2, 6);

  printf("Depth-First Traversal starting from vertex 0:\n");
  depth_first_search(graph, 0);

  return 0;
}