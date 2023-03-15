#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

Stack *new()
{
    Stack *stack = malloc(sizeof(*stack));
    stack->first = NULL;
    return stack;
}

void push(Stack *stack, Person *person)
{
  StackElement *new = malloc(sizeof(*new));
  new->person = malloc(sizeof(Person));

  if (stack == NULL || new == NULL || new->person == NULL)
    exit(EXIT_FAILURE);

  strncpy(new->person->name, person->name, sizeof(new->person->name));
  new->person->age = person->age;
  new->next = stack->first;
  stack->first = new;
}

Person pop(Stack *stack)
{
  if (stack == NULL)
    exit(EXIT_FAILURE);

  Person poppedPerson = { "", 0 };
  StackElement *poppedElement = stack->first;
  
  if (stack != NULL && stack->first != NULL)
  {
    strncpy(poppedPerson.name, poppedElement->person->name, sizeof(poppedPerson.name));
    poppedPerson.age = poppedElement->person->age;
    stack->first = poppedElement->next;
    free(poppedElement);
  }

  return poppedPerson;
}

void display(Stack *stack)
{
  if (stack == NULL)
    exit(EXIT_FAILURE);
  
  StackElement *currentStack = stack->first;

  while (currentStack != NULL)
  {
    printf("%s, %d years old\n", currentStack->person->name, currentStack->person->age);
    currentStack = currentStack->next;
  }

  printf("\n");
}