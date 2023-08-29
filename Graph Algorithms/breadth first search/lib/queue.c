#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int is_empty(Queue *q)
{
  return q->front == -1;
}

int is_full(Queue *q)
{
  return q->rear == q->capacity - 1;
}

Queue *create_queue(int capacity)
{
  Queue *q = (Queue*)malloc(sizeof(Queue));
  q->front = q->rear = -1;
  q->items = (int*)malloc(capacity * sizeof(int));

  return q;
}

void enqueue(Queue *q, int item)
{
  if (is_full(q)) {
    printf("Queue is full\n");
    exit(EXIT_FAILURE);
  }
  
  if (q->front == -1 && q->rear == -1)
    q->front = q->rear = 0;

  q->items[q->rear] = item;
  q->rear++;
}

int dequeue(Queue *q)
{
  if (is_empty(q)) {
    printf("Queue is empty\n");
    exit(EXIT_FAILURE);
  }
  int deletedItem = q->items[q->front];
  q->front++;

  if (q->front > q->rear)
    q->front = q->rear = -1;

  return deletedItem;
}