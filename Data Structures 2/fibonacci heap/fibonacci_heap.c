#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum boolean {
  false,
  true
} bool;

struct Node {
  int key;
  int degree;
  bool mark;

  // left and right pointers refer to right and left siblings, 
  // not child like in a binary tree
  struct Node *parent;
  struct Node *child;
  struct Node *left;
  struct Node *right;
};

typedef struct Node Node;

typedef struct FibonacciHeap {
  int n;
  Node *min;
  Node *rootList;
} FibonacciHeap;

int calc_max_degree(int n);
void merge_with_root_list(FibonacciHeap *fh, Node *node);
void remove_from_root_list(FibonacciHeap *fh, Node *node);
void merge_with_child_list(FibonacciHeap *fh, Node *parent, Node *node);
void remove_from_child_list(FibonacciHeap *fh, Node *parent, Node *node);
void consolidate(FibonacciHeap *fh);
void heap_link(FibonacciHeap *fh, Node *x, Node *y);
void cut(FibonacciHeap *fh, Node *cutted, Node *parent);
void cascading_cut(FibonacciHeap *fh, Node *parent);
FibonacciHeap *make_heap();
Node *insert(FibonacciHeap *fh, int key);
FibonacciHeap *union_heaps(FibonacciHeap *fh, FibonacciHeap *fh2);
Node *extract_min(FibonacciHeap *fh);
void decrease_key(FibonacciHeap *fh, Node *node, int key);
Node *delete(FibonacciHeap *fh, Node *node);
void print_heap(Node *node);

int main(int *argc, char *argv[])
{
  FibonacciHeap *FH = make_heap();

  Node *one = insert(FH, 1);
  Node *two = insert(FH, 2);  
  Node *three = insert(FH, 3);  
  Node *five = insert(FH, 5);  
  Node *seven = insert(FH, 7);  
  Node *ten = insert(FH, 10);  
  Node *twelve = insert(FH, 12);  
  Node *fifteen = insert(FH, 15);  
  Node *twenty = insert(FH, 20);  
  Node *twenty_five = insert(FH, 25);  
  Node *thirty_four = insert(FH, 34);  
  Node *eleven = insert(FH, 11);

  printf("\nHeap structure:\n");
  print_heap(FH->rootList);

  // work in progress

  return 0;
}

int calc_max_degree(int n)
{
  int count = 0;
  while (n > 0) {
    n = n / 2;
    count++;
  }

  return count;
}

void merge_with_root_list(FibonacciHeap *fh, Node *node)
{
  if (fh->rootList == NULL) {
    fh->rootList = node;    
  } else {
    node->right = fh->rootList;
    node->left = fh->rootList->left;
    fh->rootList->left->right = node;
    fh->rootList->left = node;
  }
}

void remove_from_root_list(FibonacciHeap *fh, Node *node)
{
  if (fh->rootList == node)
    fh->rootList = node->right;
  (node->left)->right = node->right;
  (node->right)->left = node->left;
}

void merge_with_child_list(FibonacciHeap *fh, Node *parent, Node *node)
{
  if (parent->child != NULL) {
    parent->child = node;
  } else {
    node->right = parent->child;
    node->left = parent->child->left;
    (parent->child->left)->right = node;
    parent->child->left = node;
  }
}

void remove_from_child_list(FibonacciHeap *fh, Node *parent, Node *node)
{
  if (parent->child == parent->child->right) {
    parent->child = NULL;
  } else if (parent->child == node) {
    parent->child = node->right;
    node->right->parent = parent;
  }
  (node->left)->right = node->right;
  (node->right)->left = node->left;
}

void consolidate(FibonacciHeap *fh)
{
  int degree = calc_max_degree(fh->n);
  Node *A[degree]; // use to store nodes according to their degree
  for (int i = 0; i < degree; i++) {
    A[i] = NULL;
  }

  Node *x = fh->rootList;
  do {
    int d = x->degree;

    while (A[d] != NULL) {
      Node *y = A[d];
      // Swap x and y node to ensure that y will always have the larger key
      if (x->key > y->key) {
        Node *temp = x;
        x = y;
        y = temp;
      }
      // Make y a child of x
      heap_link(fh, y, x);
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->right;
  } while (x != fh->rootList);

  for (int i = 0; i < degree; i++) {
    if (A[i] != NULL && A[i]->key < fh->min->key) {
      fh->min = A[i];
    }
  }
}

void heap_link(FibonacciHeap *fh, Node *y, Node *x)
{
  remove_from_root_list(fh, y);
  y->left = y->right = y;
  merge_with_child_list(fh, x, y);
  x->degree++;
  y->parent = x;
  y->mark = false;
}

void cut(FibonacciHeap *fh, Node *cutted, Node *parent)
{
  remove_from_child_list(fh, parent, cutted);
  parent->degree--;
  merge_with_root_list(fh, cutted);
  cutted->parent = NULL;
  cutted->mark = false;
}

void cascading_cut(FibonacciHeap *fh, Node *parent) 
{
  Node *current = parent->parent;
  if (current != NULL) {
    if (parent->mark == false)
      parent->mark = true;
    else {
      cut(fh, parent, current);
      cascading_cut(fh, current);
    }
  }
}

FibonacciHeap *make_heap()
{
  FibonacciHeap *FH = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
  FH->n = 0;
  FH->min = NULL;
  FH->rootList = NULL;

  return FH;
}

Node *insert(FibonacciHeap *fh, int key)
{
  Node *node = (Node*)malloc(sizeof(Node));
  node->key = key;
  node->degree = 0;
  node->mark = false;
  node->left = node;
  node->right = node;

  merge_with_root_list(fh, node);

  if (fh->min == NULL || key < fh->min->key)
    fh->min = node;

  fh->n++;
  return node;
}

FibonacciHeap *union_heaps(FibonacciHeap *fh1, FibonacciHeap *fh2)
{
  FibonacciHeap *mergedFH = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
  mergedFH->rootList = fh1->rootList;
  mergedFH->min = fh1->min < fh2->min ? fh1->min : fh2->min;

  Node *last = fh2->rootList->left;
  (fh2->rootList)->left = mergedFH->rootList->left;
  (mergedFH->rootList->left)->right = fh2->rootList;
  (mergedFH->rootList)->left = last;
  (mergedFH->rootList->left)->right = mergedFH->rootList;

  mergedFH->n = fh1->n + fh2->n;

  return mergedFH;
}

Node *extract_min(FibonacciHeap *fh)
{
  Node *z = fh->min;
  if (z != NULL) {
    if (z->child != NULL) {
      Node *current = z->child;
      while (current != z->child) {
        merge_with_root_list(fh, current);
        current->parent = NULL;
        current = current->right;
      }
    }

    remove_from_root_list(fh, z);

    if (z == z->right) {
      fh->min = NULL;
      fh->rootList = NULL;
    } else {
      fh->min = z->right; // temporarily
      consolidate(fh);
    }

    fh->n--;
  }

  return z;
}

void decrease_key(FibonacciHeap *fh, Node *node, int key)
{
  if (key > node->key)
    return;

  node->key = key;
  Node *parent = node->parent;
  if (parent != NULL && node->key < parent->key) {
    cut(fh, node, parent);
    cascading_cut(fh, parent);
  }
  if (node->key < fh->min->key)
    fh->min = node;
}

Node *delete(FibonacciHeap *fh, Node *node)
{
  decrease_key(fh, node, -10000);
  return extract_min(fh);
}

void print_heap(Node *node) {
  Node *current = node;
  do {
    printf("%d - ", current->key);
    current = current->right;
  } while (current != node);
}
