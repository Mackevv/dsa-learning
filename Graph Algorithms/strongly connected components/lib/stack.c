#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *create_stack(int capacity)
{
  Stack *newStack = (Stack*)malloc(sizeof(Stack));
  newStack->top = -1;
  newStack->capacity = capacity;
  newStack->items = (int*)malloc(capacity * sizeof(int));

  return newStack;
}

int is_empty(Stack *st)
{
  return st->top == -1;
}

int is_full(Stack *st)
{
  return st->top == st->capacity - 1;
}

void push(Stack *st, int item)
{
  if (is_full(st)) {
    printf("Stack is full\n");
    exit(EXIT_FAILURE);
  }
  st->top++;
  st->items[st->top] = item;
}

int pop(Stack *st)
{
  if (is_empty(st)) {
    printf("Stack is empty\n");
    exit(EXIT_FAILURE);
  }
  int deletedItem = st->items[st->top];
  st->top--;

  return deletedItem;
}