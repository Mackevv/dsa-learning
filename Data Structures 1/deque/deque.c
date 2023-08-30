#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int front;
  int rear;
  unsigned int size;
  int *items;
} Deque;

Deque *init_deque(unsigned int size);
int is_full (Deque *deque);
int is_empty (Deque *deque);
void insert_front(Deque *deque, int item);
void insert_rear(Deque *deque, int item);
int delete_front(Deque *deque);
int delete_rear(Deque *deque);
void print_deque(Deque *deque);


int main(int argc, char *argv[])
{
  Deque *myDeque = init_deque(5);

  insert_front(myDeque, 1);
  insert_front(myDeque, 2);
  insert_front(myDeque, 3);
  insert_front(myDeque, 4);

  print_deque(myDeque);

  insert_rear(myDeque, 5);
  insert_rear(myDeque, 6);

  printf("%d deleted from the front.\n", delete_front(myDeque));
  printf("%d deleted from the front.\n", delete_front(myDeque));

  print_deque(myDeque);

  printf("%d deleted from the rear.\n", delete_rear(myDeque));

  insert_front(myDeque, 3);
  insert_front(myDeque, 4);
  insert_front(myDeque, 5);

  print_deque(myDeque);

  printf("%d deleted from the rear.\n", delete_rear(myDeque));
  printf("%d deleted from the front.\n", delete_front(myDeque));
  printf("%d deleted from the rear.\n", delete_rear(myDeque));
  printf("%d deleted from the front.\n", delete_front(myDeque));

  print_deque(myDeque);

  return 0;
}

Deque *init_deque(unsigned int size)
{
  Deque *deque = (Deque*)malloc(sizeof(Deque));
  deque->front = -1;
  deque->rear = -1;
  deque->size = size;
  deque->items = (int*)malloc(sizeof(int) * size);
}

int is_full(Deque *deque)
{
  return (deque->front == 0 && deque->rear == deque->size - 1) || (deque->front == deque->rear + 1);
  
}

int is_empty(Deque *deque)
{
  return deque->front == -1;
}

void insert_front(Deque *deque, int item)
{
  if (is_full(deque)) {
    printf("Deque is full, cannot insert.\n");
  } else {
    if (deque->front == -1) {
      deque->front = 0;
      deque->rear = 0;
    } else if (deque->front < 1) {
      deque->front = deque->size - 1;
    } else {
      deque->front--;
    }

    deque->items[deque->front] = item;
  }
}

void insert_rear(Deque *deque, int item)
{
  if (is_full(deque)) {
    printf("Deque is full, cannot insert.\n");
  } else {
    if (deque->front == -1) {
      deque->front = 0;
      deque->rear = 0;
    } else if (deque->rear == deque->size - 1) {
      deque->rear = 0;
    } else {
      deque->rear++;
    }

    deque->items[deque->rear] = item;
  }
}

int delete_front(Deque *deque)
{
  if (is_empty(deque)) {
    printf("Deque is empty, nothing to delete.\n");
  } else {
    int item = deque->items[deque->front];

    if (deque->front == deque->rear)
      deque->front = deque->rear = -1;
    else if (deque->front == deque->size - 1)
      deque->front = 0;
    else 
      deque->front++;

    return item;
  }
}

int delete_rear(Deque *deque)
{
  if (is_empty(deque)) {
    printf("Deque is empty, nothing to delete.\n");
  } else {
    int item = deque->items[deque->rear];

    if (deque->rear == deque->front)
      deque->rear = deque->front = -1;
    else if (deque->rear == 0)
      deque->rear = deque->size - 1;
    else 
      deque->rear--;

    return item;
  }
}

void print_deque(Deque *deque)
{
  if (is_empty(deque)) {
    printf("Deque is empty, nothing here.\n");
  }

printf("\n");
  int i = deque->front;
  while(i != deque->rear) {
    printf("%d -> ", deque->items[i]);
    i = (i + 1) % deque->size;
  }

  printf("%d\n\n", deque->items[i]);
}