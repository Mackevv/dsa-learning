/**
 * File System Structure exercise
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
  char name[50];
  struct TreeNode *parent;
  struct TreeNode *children[100];
  int numChildren;
};

typedef struct TreeNode TreeNode;

// Functions prototype
TreeNode *create_node(TreeNode *parent, const char *name);
void add_child(TreeNode *parent, TreeNode *child);
void traverse_tree(TreeNode *root, int depth, const char *indentation);

int main(int argc, char *argv[])
{
  const char* indentation = "    ";

  // Root
  TreeNode *root = create_node(NULL, "DSA");

  // Root / Data Structures 1
  TreeNode *DSOne = create_node(root, "Data Structure 1");
  add_child(root, DSOne);

  // Root / Data Structures 1 / circular queue
  TreeNode *circularQueueDir = create_node(DSOne, "circular queue");
  TreeNode *circularQueueFile = create_node(circularQueueDir, "circular_queue.c");
  TreeNode *circularQueueMD = create_node(circularQueueDir, "circular_queue.md");
  add_child(DSOne, circularQueueDir);
  add_child(circularQueueDir, circularQueueFile);
  add_child(circularQueueDir, circularQueueMD);
  // Root / Data Structures 1 / deque
  TreeNode *dequeDir = create_node(DSOne, "deque");
  TreeNode *dequeFile = create_node(dequeDir, "deque.c");
  TreeNode *dequeMD = create_node(dequeDir, "deque.md");
  add_child(DSOne, dequeDir);
  add_child(dequeDir, dequeFile);
  add_child(dequeDir, dequeMD);
  // Root / Data Structures 1 / queue
  TreeNode *queueDir = create_node(DSOne, "queue");
  TreeNode *queueFile = create_node(queueDir, "queue.c");
  TreeNode *queueMD = create_node(queueDir, "queue.md");
  add_child(DSOne, queueDir);
  add_child(queueDir, queueFile);
  add_child(queueDir, queueMD);
  // Root / Data Structures 1 / stack
  TreeNode *stackDir = create_node(DSOne, "stack");
  TreeNode *stackFile = create_node(stackDir, "stack.c");
  TreeNode *stackMD = create_node(stackDir, "stack.md");
  add_child(DSOne, stackDir);
  add_child(stackDir, stackFile);
  add_child(stackDir, stackMD);

  // Root / Data Structures 2
  TreeNode *DSTwo = create_node(root, "Data Structure 2");
  add_child(root, DSTwo);

  // Root / Data Structures 2 / hash table
  TreeNode *hashTableDir = create_node(DSOne, "hash table");
  TreeNode *hashTableFile = create_node(hashTableDir, "hash_table.c");
  TreeNode *hashTableMD = create_node(hashTableDir, "hash_table.md");
  add_child(DSTwo, hashTableDir);
  add_child(hashTableDir, hashTableFile);
  add_child(hashTableDir, hashTableMD);

  // Root / Data Structure 2 / linked list
  TreeNode *linkedListDir = create_node(DSTwo, "linked list");
  TreeNode *linkedListFile = create_node(linkedListDir, "linked_list.c");
  TreeNode *linkedListMD = create_node(linkedListDir, "linked_list.md");
  add_child(DSTwo, linkedListDir);
  add_child(linkedListDir, linkedListFile);
  add_child(linkedListDir, linkedListMD);

  // Root / Tree 1
  TreeNode *treeOneDir = create_node(root, "Tree 1");
  add_child(root, treeOneDir);

  // Root / Tree 1 / tree
  TreeNode *treeDir = create_node(treeOneDir, "tree");
  add_child(treeOneDir, treeDir);

  // Root / Tree 1 / tree / assets
  TreeNode *assetsDir = create_node(treeDir, "assets");
  TreeNode *balancedTreeImage = create_node(assetsDir, "balanced-binary-tree.png");
  TreeNode *completeTreeImage = create_node(assetsDir, "complete-binary-tree.png");
  TreeNode *fullTreeImage = create_node(assetsDir, "full-binary-tree.png");
  TreeNode *perfectTreeImage = create_node(assetsDir, "perfect-binary-tree.png");
  add_child(treeDir, assetsDir);
  add_child(assetsDir, balancedTreeImage);
  add_child(assetsDir, completeTreeImage);
  add_child(assetsDir, fullTreeImage);
  add_child(assetsDir, perfectTreeImage);

  // Root / Tree 1 / tree
  TreeNode *treeFile = create_node(treeDir, "tree.c");
  TreeNode *treeMD = create_node(treeDir, "tree.md");
  TreeNode *treeReadmeMD = create_node(treeDir, "readme.md");
  add_child(treeDir, treeFile);
  add_child(treeDir, treeMD);
  add_child(treeDir, treeReadmeMD);

  // Root / .gitignore, readmde.md
  TreeNode *gitignore = create_node(root, ".gitignore");
  TreeNode *readme = create_node(root, "readme.md");
  add_child(root, gitignore);
  add_child(root, readme);

  traverse_tree(root, 0, indentation);

  /*---- Output -----
   * DSA
   * |-- Data Structure 1
   *     |-- circular queue
   *         |-- circular_queue.c
   *         |-- circular_queue.md
   *     |-- deque
   *         |-- deque.c
   *         |-- deque.md
   *     |-- queue
   *         |-- queue.c
   *         |-- queue.md
   *     |-- stack
   *         |-- stack.c
   *         |-- stack.md
   * |-- Data Structure 2
   *     |-- hash table
   *         |-- hash_table.c
   *         |-- hash_table.md
   *     |-- linked list
   *         |-- linked_list.c
   *         |-- linked_list.md
   * |-- Tree 1
   *     |-- tree
   *         |-- assets
   *             |-- balanced-binary-tree.png
   *             |-- complete-binary-tree.png
   *             |-- full-binary-tree.png
   *             |-- perfect-binary-tree.png
   *         |-- tree.c
   *         |-- tree.md
   *         |-- readme.md
   * |-- .gitignore
   * |-- readme.md
  */

  return 0;
}

TreeNode *create_node(TreeNode *parent, const char *name)
{
  TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));

  strcpy(newNode->name, name);
  newNode->parent = parent;
  newNode->numChildren = 0;

  for (int i = 0; i < sizeof(newNode->children)/sizeof(newNode->children[0]); i++) {
    newNode->children[i] = NULL;
  }

  return newNode;
}

void add_child(TreeNode *parent, TreeNode *child)
{
  if (parent->numChildren < sizeof(parent->children)/sizeof(parent->children[0])) {
    parent->children[parent->numChildren] = child;
    parent->numChildren++;
  } else {
    printf("Cannot insert new element under \"%s\".\n", parent->name);
    exit(EXIT_FAILURE);
  }
}

void traverse_tree(TreeNode *root, int depth, const char *indentation)
{
  if (root == NULL) return;
  
  // Print appropriate indentation
  for (int i = 0; i < depth - 1 ; i++) {
    printf("%s", indentation);
  }

  if (depth > 0) {
    printf("%c-- ", '|');
  }

  printf("%s\n", root->name);

  for (int i = 0; i < root->numChildren; i++) {
    traverse_tree(root->children[i], depth + 1, indentation);
  }
}