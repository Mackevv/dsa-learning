#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int data;
  struct TreeNode *left, *right;
};

typedef struct TreeNode TreeNode;

TreeNode *create_node(int data);
void inorder(TreeNode *root);
TreeNode *insert(TreeNode *node, int data);
TreeNode *search(TreeNode *root, int key);
TreeNode *min_value_node(TreeNode *node);
TreeNode *delete(TreeNode *root, int key);

int main(int *argc, char *argv[])
{
  TreeNode *root = NULL;

  root = insert(root, 8);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 6);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 14);
  root = insert(root, 4);

  printf("In-Order traversal:\n");
  inorder(root);
  printf("\n");

  TreeNode *result = search(root, 10);
  if (result != NULL)
    printf("Node with key %d found\n", result->data);
  else
    printf("Node with key 10 not found\n");

  root = delete(root, 6);

  printf("In-Order traversal:\n");
  inorder(root);

  return 0;
}


TreeNode *create_node(int data)
{
  TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
  newNode->data = data;
  newNode->left = newNode->right = NULL;

  return newNode;
}

void inorder(TreeNode *root)
{
  if (root == NULL) return;

  inorder(root->left);
  printf("%d -> ", root->data);
  inorder(root->right);
}

TreeNode *insert(TreeNode *node, int data)
{
  if (node == NULL)
    return create_node(data);
  if (data < node->data)
    node->left = insert(node->left, data);
  if (data > node->data)
    node->right = insert(node->right, data);

  return node;
}

TreeNode *search(TreeNode *root, int key)
{
  if (root == NULL || root->data == key) return root;

  if (key < root->data)
    return search(root->left, key);
  if (key > root->data)
    return search(root->right, key);
}

// Find the inorder successor : the inorder successor of a node is
// the next node you would visit in an inorder traversal.
// We will pass the right subtree of a node to this function to find the inorder successor
TreeNode *min_value_node(TreeNode *node)
{
  TreeNode *current = node;

  while (current && current->left != NULL) {
    current = current->left;
  }

  return current;
}

TreeNode *delete(TreeNode *root, int key)
{
  if (root == NULL) return root;

  // Find the node to be deleted
  if (key < root->data) {
    root->left = delete(root->left, key);
  } else if (key > root->data) {
    root->right = delete(root->right, key);
  } else {

    if (root->left == NULL) {
      TreeNode *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      TreeNode *temp = root->left;
      free(root);
      return temp;
    }

    TreeNode *temp = min_value_node(root->right);

    root->data = temp->data;

    // Delete the inorder successor
    root->right = delete(root->right, temp->data);
  }

  return root;
}