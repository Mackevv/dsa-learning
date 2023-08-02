#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void enqueue(int item);
int dequeue();
void print_queue();

int queue[SIZE];
int front = -1, rear = -1;

int main(int argc, char *argv[])
{
  enqueue(1);
  enqueue(10);
  enqueue(100);
  enqueue(1000);

  print_queue(&queue);

  printf("Remove element %d from the queue\n", dequeue());
  enqueue(1);

  print_queue(&queue);

  return 0;
}

void enqueue(int item)
{
  if (rear == SIZE - 1) {
    printf("Queue is full");
  } else {
    if (front == -1)
      front = 0;
    rear++;
    queue[rear] = item;
  }
}

int dequeue()
{
  if (front == -1 && rear == -1) {
    printf("Queue is empty");
  } else {
    int deletedItem = queue[front];
    front++;
    if (front > rear)
      front = rear = -1;
    return deletedItem;
  }
}

void print_queue(int *queue)
{
  if (rear == -1) {
    printf("Queue is empty");
  }
  else {
    for (int i = front; i <= rear; i++)
      printf("%d - ", queue[i]);
  }
  
  printf("\n");
}