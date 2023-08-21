#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AVLNode {
  char *word;
  int frequency;
  struct AVLNode *left, *right;
  int height;
};

typedef struct AVLNode AVLNode;

int max(int a, int b);
int height(AVLNode *node);
int get_balance(AVLNode *node);
void inorder(AVLNode *root, const char *prefix);
void free_tree(AVLNode *root);

AVLNode *create_node(const char *word);
AVLNode *left_rotate(AVLNode *node);
AVLNode *right_rotate(AVLNode *node);
AVLNode *insert_word(AVLNode *node, const char *word);

int main(int *argc, char *argv[])
{
  AVLNode *root = NULL;

  root = insert_word(root, "eat");
  root = insert_word(root, "access");
  root = insert_word(root, "access");
  root = insert_word(root, "access");
  root = insert_word(root, "abyssal");
  root = insert_word(root, "academy");
  root = insert_word(root, "acapnia");
  root = insert_word(root, "acceleration");
  root = insert_word(root, "acceleration");
  root = insert_word(root, "accept");
  root = insert_word(root, "accept");
  root = insert_word(root, "accept");
  root = insert_word(root, "accept");
  root = insert_word(root, "accessary");
  root = insert_word(root, "accessary");
  root = insert_word(root, "acclimate");
  root = insert_word(root, "background");
  root = insert_word(root, "background");
  root = insert_word(root, "background");
  root = insert_word(root, "backdoor");
  root = insert_word(root, "backdoor");
  root = insert_word(root, "backing");
  root = insert_word(root, "hacking");
  root = insert_word(root, "backslash");

  char prefix[] = "bac";
  printf("Auto-complete suggestions: \n");
  inorder(root, prefix);

  free_tree(root);

  return 0;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int height(AVLNode *node)
{
  if (node == NULL) return 0;
  return node->height;
}

int get_balance(AVLNode *node)
{
  if (node == NULL) return 0;
  return (height(node->left) - height(node->right));
}

AVLNode *create_node(const char *word)
{
  AVLNode *newNode = (AVLNode*)malloc(sizeof(AVLNode));
  newNode->word = strdup(word);
  newNode->frequency = 1;
  newNode->left = newNode->right = NULL;
  newNode->height = 1;

  return newNode;
}

AVLNode *left_rotate(AVLNode *node)
{
  AVLNode *rightChild = node->right;
  AVLNode *rightChildLeftSubtree = rightChild->left;

  rightChild->left = node;
  node->right = rightChildLeftSubtree; // check if order matter

  node->height = 1 + max(height(node->left), height(node->right));
  rightChild->height = 1 + max(height(rightChild->left), height(rightChild->right));

  return rightChild;
}

AVLNode *right_rotate(AVLNode *node)
{
  AVLNode *leftChild = node->left;
  AVLNode *leftChildRightSubtree = leftChild->right;

  leftChild->right = node;
  node->left = leftChildRightSubtree;

  node->height = 1 + max(height(node->left), height(node->right));
  leftChild->height = 1 + max(height(leftChild->left), height(leftChild->right));

  return leftChild;
}

AVLNode *insert_word(AVLNode *node, const char *word)
{
  if (node == NULL)
    return create_node(word);
  
  int cmp = strcmp(word, node->word);
  if (cmp == 0)
    node->frequency++;
  else if (cmp < 0)
    node->left = insert_word(node->left, word);
  else
    node->right = insert_word(node->right, word);

  node->height = 1 + max(height(node->left), height(node->right));

  int balanceFactor = get_balance(node);

  // Left left heavy case
  if (balanceFactor > 1 && strcmp(word, node->left->word) < 0)
    return right_rotate(node);

  // Right right heavy case
  if (balanceFactor < -1 && strcmp(word, node->right->word) > 0)
    return left_rotate(node);

  // Left right heavy case
  if (balanceFactor > 1 && strcmp(word, node->left->word) > 0) {
    node->left = left_rotate(node->left);
    return right_rotate(node);
  }

  // Right left heavy case
  if (balanceFactor < -1 && strcmp(word, node->right->word) < 0) {
    node->right = right_rotate(node->right);
    return left_rotate(node);
  }

  return node;
}

void inorder(AVLNode *root, const char *prefix)
{
  if (root == NULL) return;

  inorder(root->left, prefix);

  if (strstr(root->word, prefix) == root->word)
    printf("%s (%d)\n", root->word, root->frequency);

  inorder(root->right, prefix);
}

void free_tree(AVLNode *node)
{
    if (node == NULL) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node->word); // Free the memory for the word
    free(node);
}
