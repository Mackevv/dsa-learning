#ifndef H_STACK
#define H_STACK

typedef struct {
  char name[100];
  int age;
} Person;

typedef struct StackElement StackElement;
struct StackElement
{
  Person *person;
  StackElement *next;
};

typedef struct 
{
  StackElement *first;
} Stack;

Stack *new();
void push(Stack *stack, Person *person);
Person pop(Stack *stack);
void display(Stack *stack);

#endif