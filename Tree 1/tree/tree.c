#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

typedef struct Node Node;

// Implement queue for Breadth-first search
typedef struct Queue {
  int front;
  int rear;
  Node **items;
  int size;
} Queue;

Queue *init_queue(int size)
{
  Queue *queue = (Queue*)malloc(sizeof(Queue));
  queue->front = -1;
  queue->rear = -1;
  queue->size = size;
  queue->items = (Node**)malloc(sizeof(Node*) * size);

  return queue;
}

void enqueue(Queue *queue, Node *node)
{
  if (queue->rear == queue->size - 1) {
    printf("Queue is full\n");
  } else {
    if (queue->front == -1)
      queue->front = 0;
    queue->rear++;

    queue->items[queue->rear] = node;
  }
}

Node *dequeue(Queue *queue)
{
  if (queue->front == -1) {
    printf("Queue is empty");
  } else {
    Node *deletedNode = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear)
      queue->front = queue->rear = -1;

    return deletedNode;
  }
}

Node *create_node(int data);
Node *insert_left(Node *parent, int data);
Node *insert_right(Node *parent, int data);

// Tree traversal - Depth-first
void preorder_traversal(Node *root);
void inorder_traversal(Node *root);
void postorder_traversal(Node *root);
// Tree traversal - Breadth-first
void levelorder_traversal(Node *root);

int main(int *argc, char *argv[])
{
  Node *root = create_node(1);
  int height = 0;

  insert_left(root, 12);
  insert_right(root, 9);

  insert_left(root->left, 5);
  insert_right(root->left, 6);

  printf("Pre-order traversal :\n");
  preorder_traversal(root);
  printf("\n\n");
  
  printf("In-order traversal :\n");
  inorder_traversal(root);
  printf("\n\n");

  printf("Post-order traversal :\n");
  postorder_traversal(root);
  printf("\n\n");

  printf("Level-order traversal :\n");
  levelorder_traversal(root);

  return 0;
}

Node *create_node(int data) {
  Node *newNode = (Node*)malloc(sizeof(Node));

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

Node *insert_left(Node *parent, int data)
{
  Node *newNode = create_node(data);
  parent->left = newNode;

  return parent->left;
}

Node *insert_right(Node *parent, int data)
{
  Node *newNode = create_node(data);
  parent->right = newNode;

  return parent->right;
}

void preorder_traversal(Node *root)
{
  if (root == NULL) return;
  printf("%d - ", root->data);
  preorder_traversal(root->left);
  preorder_traversal(root->right);
}

void inorder_traversal(Node *root)
{
  if (root == NULL) return;
  inorder_traversal(root->left);
  printf("%d - ", root->data);
  inorder_traversal(root->right);
}

void postorder_traversal(Node *root)
{
  if (root == NULL) return;
  postorder_traversal(root->left);
  postorder_traversal(root->right);
  printf("%d - ", root->data);
}

void levelorder_traversal(Node *root)
{
  if (root == NULL) return;

  Queue *q = init_queue(10);
  enqueue(q, root);

  while (q->front != -1) {
    Node *currentNode = dequeue(q);
    printf("%d -> ", currentNode->data);

    if (currentNode->left != NULL)
      enqueue(q, currentNode->left);
    if (currentNode->right != NULL)
      enqueue(q, currentNode->right);
  }

  free(q);

  printf("\n");
}