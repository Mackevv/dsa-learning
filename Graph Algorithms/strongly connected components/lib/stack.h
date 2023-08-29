#ifndef STACK_H
#define STACK_H

typedef struct Stack {
  int top;
  int capacity;
  int *items;
} Stack;

Stack *create_stack(int capacity);
int is_empty(Stack *st);
int is_full(Stack *st);
void push(Stack *st, int item);
int pop(Stack *st);

#endif