#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char data;
  int frequency;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct MinHeap {
  int size;
  int capacity;
  Node **array;
} MinHeap;

Node *create_node(int data, int frequency);
MinHeap *create_min_heap(int capacity);
void swap_nodes(Node **a, Node **b);
int parent(int i);
void min_heapify(MinHeap *heap, int index);
void insert_node(MinHeap *heap, Node *node);
Node *extract_min(MinHeap *heap);
MinHeap *build_min_heap(char data[], int frequency[], int size);
Node *build_huffman_tree(char data[], int frequency[], int size);
void print_codes(Node *root, int array[], int top);
void free_huffman_tree(Node *root);

int main()
{
  char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int frequency[] = {5, 6, 1, 13, 17, 31};
  int size = sizeof(data)/sizeof(data[0]);

  Node *root = build_huffman_tree(data, frequency, size);
  int array[256];

  print_codes(root, array, 0);

  free_huffman_tree(root);

  return 0;
}

Node *create_node(int data, int frequency)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->frequency = frequency;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

MinHeap *create_min_heap(int capacity)
{
  MinHeap *newMinHeap = (MinHeap*)malloc(sizeof(MinHeap));
  newMinHeap->size = 0;
  newMinHeap->capacity = capacity;
  newMinHeap->array = (Node**)malloc(capacity * sizeof(Node*));

  return newMinHeap;
}

void swap_nodes(Node **a, Node **b)
{
  Node *temp = *a;
  *a = *b;
  *b = temp;
}

int parent(int i)
{
  return (i - 1) / 2;
}

void min_heapify(MinHeap *heap, int index)
{
  int smallest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency)
    smallest = left;
  if (right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency)
    smallest = right;

  if (smallest != index) {
    swap_nodes(&heap->array[smallest], &heap->array[index]);
    min_heapify(heap, smallest);
  }
}

void insert_node(MinHeap *heap, Node *node)
{
  heap->size++;
  int i = heap->size - 1;

  while (i != 0 && node->frequency < heap->array[parent(i)]->frequency) {
    heap->array[i] = heap->array[parent(i)];
    i = parent(i);
  }

  heap->array[i] = node;
}

Node *extract_min(MinHeap *heap)
{
  Node *rootNode = heap->array[0];
  heap->array[0] = heap->array[heap->size - 1];
  heap->size--;

  min_heapify(heap, 0);

  return rootNode;
}

MinHeap *build_min_heap(char data[], int frequency[], int size)
{
  MinHeap *minHeap = create_min_heap(size);
  for (int i = 0; i < size; i++) {
    minHeap->array[i] = create_node(data[i], frequency[i]);
  }
  minHeap->size = size;

  for (int i = (size / 2) - 1; i >= 0; i--) {
    min_heapify(minHeap, i);
  }

  return minHeap;
}

Node *build_huffman_tree(char data[], int frequency[], int size)
{
  Node *left, *right, *top;
  MinHeap *minHeap = build_min_heap(data, frequency, size);

  while (minHeap->size != 1) {
    left = extract_min(minHeap);
    right = extract_min(minHeap);
    top = create_node('$', left->frequency + right->frequency);
    top->left = left;
    top->right = right;
    insert_node(minHeap, top);
  }

  return extract_min(minHeap);
}

void print_codes(Node *root, int array[], int top)
{
  if (root->left) {
    array[top] = 0;
    print_codes(root->left, array, top + 1);
  }

  if (root->right) {
    array[top] = 1;
    print_codes(root->right, array, top + 1);
  }

  if (!root->left && !root->right) {
    printf("%c: ", root->data);
    for (int i = 0; i < top; i++) {
      printf("%d", array[i]);
    }
    printf("\n");
  }
}

void free_huffman_tree(Node *root)
{
  if (root == NULL) return;

  free_huffman_tree(root->left);
  free_huffman_tree(root->right);
  free(root);
}