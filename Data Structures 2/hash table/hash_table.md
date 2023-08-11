## LeetCode

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/two-sum/">Two Sum</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/group-anagrams/">Group Anagrams</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/longest-substring-without-repeating-characters/">Longest Substring Without Repeating Characters</a><br>
</div>

### My solution
<details>
<summary>Two Sum</summary>
<br>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// Create hash table data structure
typedef struct HashNode {
    int key;
    int value;
} HashNode;

HashNode **arr;

int hash_function(int key, int capacity)
{
    // Add capacity to the rest of the division of key by capacity
    // to ensure that the generated hash is a positive number
    return (key % capacity + capacity) % capacity;
}

void insert(int key, int value, int capacity) 
{
    HashNode *temp = (HashNode*)malloc(sizeof(HashNode));
    temp->key = key;
    temp->value = value;

    int hashIndex = hash_function(key, capacity);

    while (arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1) {
        hashIndex = (hashIndex + 1) % capacity;
    }

    arr[hashIndex] = temp;
}

int find(int key, int capacity)
{
    int hashIndex = hash_function(key, capacity);

    while (arr[hashIndex] != NULL) {
        if (arr[hashIndex]->key == key)
            return arr[hashIndex]->value;

        hashIndex = (hashIndex + 1) % capacity;
    }

    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Initialize hash
    arr = (HashNode**)malloc(sizeof(HashNode*) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        arr[i] = NULL;
    }
    
    int *result = (int*)malloc(sizeof(int) * 2);

    // Iterate through the nums array, insert nums[i] as key and index as value
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = find(complement, numsSize);

        if (complementIndex != -1 && complementIndex != i) {
            result[0] = complementIndex;
            result[1] = i;
            *returnSize = 2;
            return result;
        }

        insert(nums[i], i, numsSize);
    }

    free(result);
    return NULL;
}

```
</details>

## Actual application exercise

<u>Title:</u> Database Indexing<br>
<u>Statement:</u> Create a simple key-value database using a hash table in C. Implement functions to insert, retrieve, and delete records based on a unique key. Handle hash collisions using a suitable collision resolution technique, such as chaining or open addressing.