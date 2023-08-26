// Implement priority queue using binary heap

#include <stdio.h>
#include <stdlib.h>
#include "lib/heap.h"

typedef struct PriorityQueue {
  Heap *heap;
  int size;
} PriorityQueue;

PriorityQueue *create_pqueue();
void enqueue(PriorityQueue *pqueue, int key);
int dequeue(PriorityQueue *pqueue);
void update_priority(PriorityQueue *pqueue, int key, int newKey);

int main(int *argc, char *argv[])
{
  PriorityQueue *pq = create_pqueue(10);
  enqueue(pq, 3); 
  enqueue(pq, 4); 
  enqueue(pq, 6); 
  enqueue(pq, 1); 
  enqueue(pq, 3); 
  enqueue(pq, 2); 
  enqueue(pq, 8); 
  enqueue(pq, 90); 
  enqueue(pq, 1);

  while (pq->size > 0) {
    printf("%d -> ", dequeue(pq));
  }

  return 0;
}

PriorityQueue *create_pqueue(int capacity)
{
  PriorityQueue *pqueue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
  pqueue->heap = make_heap(capacity);
  pqueue->size = 0;

  return pqueue;
}

void enqueue(PriorityQueue *pqueue, int key)
{
  insert_key(pqueue->heap, key);
  pqueue->size++;
}

int dequeue(PriorityQueue *pqueue)
{
  pqueue->size--;
  return extract_min(pqueue->heap);
}

void update_priority(PriorityQueue *pqueue, int key, int newKey)
{
  decrease_key(pqueue->heap, key, newKey);
}

// Heap *h = (Heap*)malloc(sizeof(Heap));
  // h->capacity = 10;
  // h->size = 0;
  // h->items = (int*)malloc(sizeof(int));

  // insert_key(h, 3);
  // insert_key(h, 2);
  // insert_key(h, 10);
  // insert_key(h, 5);
  // insert_key(h, 8);
  // insert_key(h, 6);
  // insert_key(h, 1);
  // insert_key(h, 4);
  // insert_key(h, 5);

  // printf("After insert:\n");
  // for (int i = 0; i < h->size; i++) {
  //   printf("%d, ", h->items[i]);
  // }
  // printf("\n\n");

  // decrease_key(h, 5, 3);
  // decrease_key(h, 5, 2);

  // printf("After decrease:\n");
  // for (int i = 0; i < h->size; i++) {
  //   printf("%d, ", h->items[i]);
  // }
  // printf("\n\n");

  // delete_key(h, 3);
  // delete_key(h, 6);

  // printf("After delete:\n");
  // for (int i = 0; i < h->size; i++) {
  //   printf("%d, ", h->items[i]);
  // }
  // printf("\n\n");

  // printf("After extraction of %d\n", extract_min(h));
  // for (int i = 0; i < h->size; i++) {
  //   printf("%d, ", h->items[i]);
  // }

  // free(h->items);
  // free(h);