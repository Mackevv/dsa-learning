#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  struct Node *left, *right;
  int height;
};

typedef struct Node Node;

// helper functions
int max(int a, int b);
int height(Node *node);
int get_balance(Node *node);
Node *min_value_node(Node *node);
void inorder(Node *root);
// AVL Tree operations
Node *create_node(int key);
Node *left_rotate(Node *node);
Node *right_rotate(Node *node);
Node *insert(Node *node, int key);
Node *delete(Node *root, int key);

int main(int *argc, char *arvg[])
{
  Node *root = NULL;

  root = insert(root, 2);
  root = insert(root, 1);
  root = insert(root, 7);
  root = insert(root, 4);
  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 8);

  printf("In-Order:\n");
  inorder(root);
  printf("\n");
  
  root = delete(root, 3);

  printf("In-Order:\n");
  inorder(root);
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int height(Node *node)
{
  if (node == NULL) return 0;
  return node->height;
}

int get_balance(Node *node)
{
  if (node == NULL) return 0;
  return height(node->left) - height(node->right);
}

Node *min_value_node(Node *node)
{
  Node *current = node;

  while (current && current->left != NULL) {
    current = current->left;
  }

  return current;
}

void inorder(Node *root)
{
  if (root == NULL) return;

  inorder(root->left);
  printf("%d -> ", root->key);
  inorder(root->right);
}

Node *create_node(int key)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->left = newNode->right = NULL;
  newNode->key = key;
  newNode->height = 1;

  return newNode;
}

// Left rotate : node is flip on the left side of his right child
Node *left_rotate(Node *node)
{
  Node *rightChild = node->right;
  Node *rightChildLeftSubtree = rightChild->left;

  rightChild->left = node;
  node->right = rightChildLeftSubtree;

  node->height = 1 + max(height(node->left), height(node->right));
  rightChild->height = 1 + max(height(rightChild->left), height(rightChild->right));
  
  return rightChild;
}

// Right rotate : node is flip on the right side of his left child
Node *right_rotate(Node *node)
{
  Node *leftChild = node->left;
  Node *leftChildRightSubtree = leftChild->right;

  leftChild->right = node;
  node->left = leftChildRightSubtree;

  node->height = 1 + max(height(node->left), height(node->right));
  leftChild->height = 1 + max(height(leftChild->left), height(leftChild->right));

  return leftChild;
}

Node *insert(Node *node, int key)
{
  if (node == NULL)
    return create_node(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else
    return node; // test sans

  node->height = 1 + max(height(node->left), height(node->right));

  // Update balance factor
  int balance = get_balance(node);

  if (balance > 1 && key < node->left->key)
    return right_rotate(node);
  if (balance < -1 && key > node->right->key)
    return left_rotate(node);
  if (balance > 1 && key > node->left->key) {
    node->left = left_rotate(node->left);
    return right_rotate(node);
  }
  if (balance < -1 && key < node->right->key) {
    node->right = right_rotate(node->right);
    return left_rotate(node);
  }

  return node;
}

Node *delete(Node *root, int key)
{
  if (root == NULL) return root;

  if (key < root->key) {
    root->left = delete(root->left, key);
  } else if (key > root->key) {
    root->right = delete(root->right, key);
  } else {
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    } else {
      // Inorder successor
      Node *temp = min_value_node(root->right);
      root->key = temp->key;
      // Delete inorder successor
      root->right = delete(root->right, temp->key);
    }
  }

  if (root == NULL) return root;

  root->height = 1 + max(height(root->left), height(root->right));

  // Update balance factor
  int balance = get_balance(root);

  if (balance > 1 && get_balance(root->left) >= 0)
    return right_rotate(root);
  if (balance < -1 && get_balance(root->right) <= 0)
    return left_rotate(root);
  if (balance > 1 && get_balance(root->left) < 0) {
    root->left = left_rotate(root->left);
    return right_rotate(root);
  }
  if (balance < -1 && get_balance(root->right) > 0) {
    root->right = right_rotate(root->right);
    return left_rotate(root);
  }

  return root;
}