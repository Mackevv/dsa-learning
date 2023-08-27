#include <stdio.h>
#include <stdlib.h>

typedef enum Color {
  RED,
  BLACK
} Color;

typedef struct Node {
  int key;
  Color color;
  struct Node *parent, *left, *right;
} Node;

typedef struct RedBlackTree {
  Node *root;
  Node *nil;
} RedBlackTree;

Node *create_node(int key);
RedBlackTree *create_rb_tree();
void left_rotate(RedBlackTree *tree, Node *x);
void right_rotate(RedBlackTree *tree, Node *x);
void insert(RedBlackTree *tree, int key);
void insert_fixup(RedBlackTree *tree, Node *z);
void delete(RedBlackTree *tree, int key);
void delete_fixup(RedBlackTree *tree, Node *x);
void transplant(RedBlackTree *tree, Node *u, Node *v);
Node *min_value_node(RedBlackTree *tree, Node *node);
Node *search(RedBlackTree *tree, int key);
void inorder(Node *root);
char nodeColor(Node *node);

int main(int *argc, char *argv[])
{
  RedBlackTree *tree = create_rb_tree();

  insert(tree, 10);
  insert(tree, 1);
  insert(tree, 67);
  insert(tree, 43);
  insert(tree, 3);
  insert(tree, 13);
  insert(tree, 4);
  insert(tree, 11);

  printf("After insertion: \n");
  inorder(tree->root);
  printf("\n\n");

  delete(tree, 67);
  delete(tree, 1);

  printf("After deletion: \n");
  inorder(tree->root);

  return 0;
}

Node *create_node(int key)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->key = key;
  newNode->color = RED;
  newNode->parent = newNode->left = newNode->right = NULL;

  return newNode;
}

RedBlackTree *create_rb_tree()
{
  RedBlackTree *RBTree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
  RBTree->nil = create_node(-1);
  RBTree->nil->color = BLACK;
  RBTree->root = RBTree->nil;

  return RBTree;
}

void left_rotate(RedBlackTree *tree, Node *x)
{
  Node *y = x->right;
  x->right = y->left;

  if (y->left != tree->nil)
    y->left->parent = x;

  y->parent = x->parent;

  if (x->parent == tree->nil) // if x is root node
    tree->root = y;
  else if (x == x->parent->left) // if x is a left child
    x->parent->left = y;
  else // else x is a right child
    x->parent->right = y;

  y->left = x;
  x->parent = y;
} 

void right_rotate(RedBlackTree *tree, Node *x)
{
  Node *y = x->left;
  x->left = y->right;

  if (y->right != tree->nil)
    y->right->parent = x;

  y->parent = x->parent;

  if (x->parent == tree->nil)
    tree->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else 
    x->parent->right = y;

  y->right = x;
  x->parent = y;
}

void insert(RedBlackTree *tree, int key)
{
  Node *z = create_node(key);
  Node *x = tree->root;
  Node *y = tree->nil;

  while (x != tree->nil) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;

  if (y == tree->nil)
    tree->root = z;
  else if (z->key < y->key)
    y->left = z;
  else 
    y->right = z;

  z->right = z->left = tree->nil;

  insert_fixup(tree, z);
}

void insert_fixup(RedBlackTree *tree, Node *z)
{
  while (z->parent != tree->nil && z->parent->color == RED) {
    Node *grandParent = z->parent->parent;
    Node *uncle = (grandParent->right == z->parent) ? grandParent->left : grandParent->right;

    // Case 1: z uncle is red
    if (uncle->color == RED) {
      z->parent->color = BLACK;
      uncle->color = BLACK;
      grandParent->color = RED;
      z = z->parent->parent;
    } else {
      if (z->parent == grandParent->right) {
        if (z == z->parent->left) { // Case 2: z uncle black (triangle)
          z = z->parent;
          right_rotate(tree, z);
        }

        // Case 3: z uncle black (line)
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        left_rotate(tree, grandParent);
      } else {
        // Same but reversed 
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(tree, z);
        }

        z->parent->color = BLACK;
        z->parent->parent = RED;
        right_rotate(tree, grandParent);
      }
    }
  }

  // Case 0: if z is the root node
  tree->root->color = BLACK;
}

void delete(RedBlackTree *tree, int key)
{
  Node *z = search(tree, key);
  Node *x;

  Node *y = z;
  Color originalColor = y->color;

  if (z == tree->nil)
    exit(EXIT_FAILURE);

  if (z->left == tree->nil) {
    x = z->right;
    transplant(tree, z, z->right);
  } else if (z->right == tree->nil) {
    x = z->left;
    transplant(tree, z, z->left);
  } else {
    y = min_value_node(tree, z->right);
    originalColor = y->color;
    x = y->right;

    if (y->parent == z) {
      x->parent = z;
    } else {
      transplant(tree, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (originalColor == BLACK)
    delete_fixup(tree, x);
}

void delete_fixup(RedBlackTree *tree, Node *x)
{
  while (x != tree->nil && x->color == BLACK) {
    Node *sibling = (x == x->parent->left) ? x->parent->right : x->parent->left;
    
    // When sibling is a right child
    if (x == x->parent->left) {
      // Case 1
      if (sibling->color == RED) {
        sibling->color = BLACK;
        x->parent->color = RED;
        left_rotate(tree, x->parent);
        sibling = x->parent->right;
      }

      // Case 2
      if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        x = x->parent;
      } else {
        // Case 3
        if (sibling->right->color == BLACK) {
          sibling->left->color = BLACK;
          sibling->color = RED;
          right_rotate(tree, sibling);
          sibling = x->parent->right;
        }
        
        // Case 4
        sibling->color = x->parent->color;
        x->parent->color = BLACK;
        sibling->right->color = BLACK;
        left_rotate(tree, x->parent);
        x = tree->root;
      }
    // When sibling is a left child
    } else {
      // Same but reversed
      if (sibling->color == RED) {
        sibling->color = BLACK;
        x->parent->color = RED;
        right_rotate(tree, x->parent);
        sibling = x->parent->left;
      }

      if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        x = x->parent;
      } else {
        if (sibling->left->color == BLACK) {
          sibling->right->color = BLACK;
          sibling->color = RED;
          left_rotate(tree, sibling);
          sibling = x->parent->left;
        }

        sibling->color = x->parent->color;
        x->parent->color = BLACK;
        sibling->left->color = BLACK;
        right_rotate(tree, x->parent);
        x = tree->root;
      }
    }
  }
  x->color = BLACK;
}

void transplant(RedBlackTree *tree, Node *u, Node *v) 
{
  if (u->parent == tree->nil) {
    tree->root = v;
  } else if (u == u->parent->right) {
    u->parent->right = v;
  } else {
    u->parent->left = v;
  }

  v->parent = u->parent;
}

Node *min_value_node(RedBlackTree *tree, Node *node)
{
  while (node->left != tree->nil)
    node = node->left;

  return node;
}

Node *search(RedBlackTree *tree, int key)
{
  Node *current = tree->root;
  while (key != current->key) {
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }

  return current;
}

void inorder(Node *root)
{
  if (root == NULL || root->key == -1) return;

  inorder(root->left);
  printf("%d (%c), ", root->key, nodeColor(root));
  inorder(root->right);
}

char nodeColor(Node *node)
{
  if (node->color == RED)
    return 'R';
  else
    return 'B';
}