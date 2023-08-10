## LeetCode

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/reverse-linked-list/">Reverse Linked List</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/remove-nth-node-from-end-of-list/">Remove Nth Node From End of List</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/merge-k-sorted-lists/">Merge k Sorted Lists</a><br>
</div>

### Solution
<details>
<summary>Reverse Linked List</summary>
<br>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head){
    // If list has no element or only one element
    if (head == NULL || head->next == NULL) return head;

    struct ListNode *current = head->next;
    head->next = NULL;

    while (head != NULL && current != NULL) {
        struct ListNode *next = current->next;
        current->next = head;

        head = current;
        current = next;
    }

    return head;
}
```
</details>

## Actual application exercise

<u>Title:</u> Music Playlist<br>
<u>Statement:</u> Design a music playlist management system using a singly linked list. Implement the following functionalities in C language:

1. Add a new song to the end of the playlist.
2. Remove a song from the playlist based on the song's name.
3. Print the entire playlist.