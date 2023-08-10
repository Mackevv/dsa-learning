#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int front;
  int rear;
  unsigned int size;
  int *items;
} CircularQueue;

int is_full(CircularQueue *cqueue);
int is_empty(CircularQueue *cqueue);
CircularQueue *init_cqueue(unsigned int size);
void enqueue(CircularQueue *cqueue, int item);
int dequeue(CircularQueue *cqueue);
void print_queue(CircularQueue *cqueue);

int main(int argc, char *argv[])
{
  CircularQueue *myCircularQueue = init_cqueue(5);

  dequeue(myCircularQueue); // Queue is empty

  enqueue(myCircularQueue, 1);
  enqueue(myCircularQueue, 2);
  enqueue(myCircularQueue, 3);
  enqueue(myCircularQueue, 4);
  enqueue(myCircularQueue, 5);

  enqueue(myCircularQueue, 6); // Queue is full

  print_queue(myCircularQueue);

  dequeue(myCircularQueue);

  print_queue(myCircularQueue);

  return 0;
}

CircularQueue *init_cqueue(unsigned int size)
{
  CircularQueue *cqueue = (CircularQueue*)malloc(sizeof(CircularQueue));
  cqueue->front = cqueue->rear = -1;
  cqueue->size = size;
  cqueue->items = (int*)malloc(sizeof(int) * size);

  return cqueue;
}

int is_full(CircularQueue *cqueue)
{
  return (cqueue->front == 0 && cqueue->rear == cqueue->size - 1) 
        || (cqueue->front == (cqueue->rear + 1) % cqueue->size);
}

int is_empty(CircularQueue *cqueue)
{
  return (cqueue->front == -1);
}

void enqueue(CircularQueue *cqueue, int item)
{
  if (is_full(cqueue)) 
    printf("Queue is full\n");
  else {
    if (is_empty(cqueue))
      cqueue->front = 0;

    cqueue->rear = (cqueue->rear + 1) % cqueue->size;
    cqueue->items[cqueue->rear] = item;

    printf("Inserted item %d\n", item);
  }
}

int dequeue(CircularQueue *cqueue)
{
  if (is_empty(cqueue)) {
    printf("Queue is empty\n");
    return -1;
  } else {
    int deletedItem = cqueue->items[cqueue->front];

    if (cqueue->front == cqueue->rear)
      cqueue->front = cqueue->rear = -1;
    else {
      cqueue->front = (cqueue->front + 1) % cqueue->size;
    }

    printf("Deleted item %d\n", deletedItem);

    return deletedItem;
  } 
}

void print_queue(CircularQueue *cqueue)
{
  if (is_empty(cqueue))
    printf("\nQUEUE : Empty\n");
  else {
    printf("\nFRONT -> REAR\n");
    printf("\nQUEUE : ");
    
    int i = cqueue->front;
    while (i != cqueue->rear) {
      printf("%d -> ", cqueue->items[i]);
      i = (i + 1) % cqueue->size;
    }

    printf("%d\n", cqueue->items[i]);
  }
}