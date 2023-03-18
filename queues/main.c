#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char *argv[])
{
  Queue *myQueue = newQueue();
  Person johnny = { "Johnny", 19 };
  Person gyro = { "Gyro", 24 };
  Person diego = { "Diego", 20 };

  enqueue(myQueue, &johnny);
  enqueue(myQueue, &gyro);
  enqueue(myQueue, &diego);

  printf("\n--- QUEUE STATE ---\n");
  displayQueue(myQueue);

  printf("Dequeue : %s\n", dequeue(myQueue).name);
  printf("Dequeue : %s\n", dequeue(myQueue).name);

  printf("\n--- QUEUE STATE ---\n");
  displayQueue(myQueue);
}