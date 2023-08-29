#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
  int front;
  int rear;
  int capacity;
  int *items;
} Queue;

Queue *create_queue(int capacity);
void enqueue(Queue *q, int item);
int dequeue(Queue *q);

#endif