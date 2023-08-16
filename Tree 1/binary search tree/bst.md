## LeetCode

<div>
  <span style="color: green">Medium</span> : <a href="https://leetcode.com/problems/validate-binary-search-tree/">Validate Binary Search Tree</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/binary-tree-inorder-traversal/">Binary Tree Inorder Traversal</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst//">Number of Ways to Reorder Array to Get Same BST</a><br>
</div>

### My solution
<details>
<summary>Validate Binary Search Tree</summary>
<br>

Note : Approach using inorder traversal and store the element in a queue. Inorder traversal of a BST give the element in a sorted ways, if the elements are not sorted, it's not a BST. Definitely not the best solution but the simplest one in my opinion

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

typedef struct Queue {
    int front;
    int rear;
    int *items;
    int size;
} Queue;

void enqueue(Queue* q, int val)
{
    if (q->rear == QUEUE_CAPACITY - 1) return;

    if (q->front == -1)
        q->front = q->rear = 0;
    else
        q->rear++;

    q->size++;
    q->items[q->rear] = val;
}

// Inorder traversal give a sorted list for BST, if not
// then it's not a BST.
void inorder(struct TreeNode* root, Queue *q){
    if (root == NULL) return;

    inorder(root->left, q);
    enqueue(q, root->val);
    inorder(root->right, q);
}

bool isValidBST(struct TreeNode* root){
    if (root == NULL) return true;

    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = -1;
    q->size = 0;
    q->items = (int*)malloc(sizeof(int) * QUEUE_CAPACITY);

    inorder(root, q);

    for (int i = 0; i < q->size - 1; i++) {
        if (q->items[i] >= q->items[i+1])
            return false;
    }

    free(q->items);
    free(q);

    return true;
}
```
</details>

## Actual application exercise

<u>Title:</u> Virtual Memory Area Management with Binary Search Tree (Simplified) <br>
<u>Statement:</u> In this exercise, you will simulate a simplified version of virtual memory area management using a binary search tree (BST). Virtual memory area management is an essential component of operating systems, including Unix kernels, to efficiently allocate and deallocate memory segments for processes.

You will implement a basic memory management system that supports memory allocation, deallocation, and retrieval of memory segments using a BST. Each memory segment is represented by a pair of start and end addresses. The goal is to provide a simplified understanding of how a BST can be utilized to manage memory segments.

<details>
<summary>Help</summary>

1. Implement the createMemorySegment function:

This function should create a new memory segment with the given start and end addresses.
Initialize the left and right pointers of the segment to NULL.
Return the newly created memory segment.

2. Implement the insert function:

This function should insert a memory segment into the BST based on the start address.
If the BST is empty, create a new node for the memory segment and return it.
Traverse the BST to find the appropriate position to insert the segment.
Return the updated root of the BST.

3. Implement the findSegment function:

Given an address, this function should search the BST to find the memory segment that contains the address.
If the address is within the range of a memory segment, return that segment; otherwise, return NULL.

4. Implement the deallocateSegment function:

This function should remove a memory segment from the BST based on the start address.
If the segment is found, deallocate the memory and adjust the BST accordingly.
Return the updated root of the BST.

5. Implement the inorderTraversal function:

This function should perform an inorder traversal of the BST and print the start and end addresses of each memory segment.

6. In the main function:

Simulate memory allocation and deallocation by inserting and deallocating memory segments using the BST.
Retrieve a memory segment containing a specific address and print its details.
After deallocation, print the remaining memory segments using inorder traversal.
</details>

<details>
<summary>Correction</summary>

```c
#include <stdio.h>
#include <stdlib.h>

// Structure for a memory segment
struct MemorySegment {
    unsigned int start;
    unsigned int end;
    struct MemorySegment* left;
    struct MemorySegment* right;
};

// Function to create a new memory segment
struct MemorySegment* createMemorySegment(unsigned int start, unsigned int end) {
    struct MemorySegment* segment = (struct MemorySegment*)malloc(sizeof(struct MemorySegment));
    segment->start = start;
    segment->end = end;
    segment->left = segment->right = NULL;
    return segment;
}

// Function to insert a memory segment into the BST
struct MemorySegment* insert(struct MemorySegment* root, unsigned int start, unsigned int end) {
    if (root == NULL) {
        return createMemorySegment(start, end);
    }

    if (start < root->start) {
        root->left = insert(root->left, start, end);
    } else if (start > root->start) {
        root->right = insert(root->right, start, end);
    }

    return root;
}

// Function to find a memory segment that contains the specified address
struct MemorySegment* findSegment(struct MemorySegment* root, unsigned int address) {
    if (root == NULL || (address >= root->start && address <= root->end)) {
        return root;
    }

    if (address < root->start) {
        return findSegment(root->left, address);
    } else {
        return findSegment(root->right, address);
    }
}

// Function to deallocate a memory segment
struct MemorySegment* deallocateSegment(struct MemorySegment* root, unsigned int start) {
    if (root == NULL) {
        return NULL;
    }

    if (start < root->start) {
        root->left = deallocateSegment(root->left, start);
    } else if (start > root->start) {
        root->right = deallocateSegment(root->right, start);
    } else {
        // Found the segment to deallocate
        free(root);
        return NULL;
    }

    return root;
}

// Function to print the memory segments using inorder traversal
void inorderTraversal(struct MemorySegment* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Memory Segment: [%u, %u]\n", root->start, root->end);
        inorderTraversal(root->right);
    }
}

int main() {
    struct MemorySegment* memoryTree = NULL;

    // Simulate memory allocation and deallocation
    memoryTree = insert(memoryTree, 1000, 2000);
    memoryTree = insert(memoryTree, 3000, 4000);
    memoryTree = insert(memoryTree, 5000, 6000);

    printf("Initial Memory Segments:\n");
    inorderTraversal(memoryTree);

    unsigned int addressToAllocate = 1500;
    unsigned int addressToDeallocate = 3000;

    struct MemorySegment* allocatedSegment = findSegment(memoryTree, addressToAllocate);
    if (allocatedSegment != NULL) {
        printf("Allocated Memory Segment: [%u, %u]\n", allocatedSegment->start, allocatedSegment->end);
    } else {
        printf("Address not found in memory tree.\n");
    }

    memoryTree = deallocateSegment(memoryTree, addressToDeallocate);

    printf("Memory Segments after Deallocation:\n");
    inorderTraversal(memoryTree);

    // Clean up memory
    // Note: This part is simplified and doesn't fully simulate real memory management.
    // In practice, additional cleanup and proper memory deallocation are required.
    // This exercise focuses on the basic concept of using a BST for memory management.
    // It's important to handle memory management properly in a real system.
    return 0;
}
```
</details>