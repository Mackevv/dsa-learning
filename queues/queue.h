#ifndef H_QUEUE
#define H_QUEUE

typedef struct
{
  char name[100];
  int age;
} Person;

typedef struct QueueElement QueueElement;
struct QueueElement
{
  Person *person;
  QueueElement *next;
};

typedef struct
{
  QueueElement *first;
} Queue;

Queue *newQueue();
void enqueue(Queue *queue, Person *person);
Person dequeue(Queue *queue);
void displayQueue(Queue *queue);

#endif