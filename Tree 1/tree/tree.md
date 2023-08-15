# Tree
## LeetCode exercises

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/n-ary-tree-preorder-traversal/">N-ary Tree Preorder Traversal</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/maximum-depth-of-n-ary-tree/">Maximum Depth of N-ary Tree</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/">Serialize and Deserialize N-ary Tree</a><br>
</div>

## Actual application exercise

<u>Title:</u> File System Structure<br>
<u>Statement:</u> Design a tree-based file system structure where each node represents a directory and can contain multiple files or sub-directories. Implement functions to add new files/directories, and traverse the file system.

Correction of this exercise in `fs_tree.c` file

# Binary tree
## LeetCode 

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/symmetric-tree/">Symmetric Tree</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/">Construct Binary Tree from Preorder and Inorder Traversal</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/binary-tree-maximum-path-sum/">Binary Tree Maximum Path Sum</a><br>
</div>

### Solution
<details>
<summary>Symmetric Tree</summary>
<br>

1. Recursive approach
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// Check if left subtrees and right subtrees are symmetric
bool traversal(struct TreeNode* left, struct TreeNode* right) {
    if (left == NULL && right == NULL ) return true;

    if (left == NULL || right == NULL) return false;
    if (left->val != right->val) return false;

    // Tree should be symmetric around it's center so we need
    // to compare nodes from the left most one (left->left) and 
    // the right most one (right->right) and decrease gradually by one 
    return (traversal(left->left, right->right) && traversal(left->right, right->left));
}

bool isSymmetric(struct TreeNode* root){
    if (root == NULL) return true;

    return traversal(root->left, root->right);
}
```

2. Iterative approach : here we will use breadth-first search to perferm a level order tree traversal

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define QUEUE_CAPACITY 1000

struct Queue {
    struct TreeNode* arr[QUEUE_CAPACITY];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = q->rear = -1;
}

bool isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, struct TreeNode* node) {
    if (q->rear == QUEUE_CAPACITY - 1) {
        return; // Queue is full
    }

    if (q->front == -1) {
        q->front = 0;
    }

    q->rear++;
    q->arr[q->rear] = node;
}

struct TreeNode* dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }

    struct TreeNode* node = q->arr[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }

    return node;
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;

    struct Queue q;
    initQueue(&q);

    enqueue(&q, root->left);
    enqueue(&q, root->right);

    while(!isEmpty(&q)) {
        struct TreeNode *leftNode = dequeue(&q);
        struct TreeNode *rightNode = dequeue(&q);

        if (leftNode == NULL && rightNode == NULL)
            continue;
        
        if (leftNode == NULL || rightNode == NULL)
            return false;

        if (leftNode->val != rightNode->val)
            return false;

        // tree should be mirrored, so we compare 
        // the opposite node of the two subtrees
        enqueue(&q, leftNode->left);
        enqueue(&q, rightNode->right);
        enqueue(&q, leftNode->right);
        enqueue(&q, rightNode->left);
    }

    return true;
}
```

</details>

## Actual application exercise

<u>Title:</u> Expression Tree Evaluation<br>
<u>Statement:</u> Create a binary expression tree to evaluate mathematical expressions involving operators (+, -, *, /) and operands. Implement a function that takes the root of the expression tree as input and returns the result of the expression.