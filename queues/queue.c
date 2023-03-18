#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue *newQueue()
{
  Queue *queue = malloc(sizeof(*queue));
  queue->first = NULL;
  return queue;
}

void enqueue(Queue *queue, Person *person)
{
  QueueElement *new = malloc(sizeof(*new));
  new->person = malloc(sizeof(*new->person));

  if (queue == NULL || new == NULL || new->person == NULL)
    exit(EXIT_FAILURE);

  new->person->age = person->age;
  strncpy(new->person->name, person->name, sizeof(new->person->name));
  new->next = NULL;

  if (queue->first != NULL)
  {
    QueueElement *currentElement = queue->first;
    while (currentElement->next != NULL)
    {
      currentElement = currentElement->next;
    }
    currentElement->next = new;
  }
  else
  {
    queue->first = new;
  }
}

Person dequeue(Queue *queue)
{
  if (queue == NULL)
    exit(EXIT_FAILURE);

  Person removedPerson = { "", 0 };

  if (queue->first != NULL)
  {
    QueueElement *removedElement = queue->first;

    removedPerson.age = removedElement->person->age;
    strncpy(removedPerson.name, removedElement->person->name, sizeof(removedPerson.name));
    queue->first = removedElement->next;
    free(removedElement);
  }

  return removedPerson;
}

void displayQueue(Queue *queue)
{
  if (queue == NULL)
    exit(EXIT_FAILURE);

  QueueElement *current = queue->first;
  while (current != NULL)
  {
    printf("%s (%d) <- ", current->person->name, current->person->age);
    current = current->next;
  }
  printf("NULL\n");
}