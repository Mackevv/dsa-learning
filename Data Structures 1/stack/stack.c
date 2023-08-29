#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *items;
  int top;
  unsigned int size;
} Stack;

Stack *create_stack(unsigned int size)
{
  Stack *stack = (Stack*)malloc(sizeof(Stack));
  stack->size = size;
  stack->top = -1;
  stack->items = (int*)malloc(sizeof(int) * stack->size);

  return stack;
}

int is_full(Stack *stack)
{
  return stack->top == stack->size - 1;
}

int is_empty(Stack *stack)
{
  return stack->top == -1;
}

void push(Stack *stack, int item)
{
  if (is_full(stack)) {
    printf("Stack is full");
  } else {
    stack->top++;
    stack->items[stack->top] = item;
    printf("%d pushed to stack\n", item);
  }
}

void pop(Stack *stack)
{
  if (is_empty(stack)) {
    printf("Stack is empty, nothing to remove\n");
  } else {
    int top = stack->top;
    stack->top--;
    printf("%d popped from stack\n", stack->items[top]);
  }
}

int peek(Stack *stack)
{
  if (is_empty(stack))
    printf("Stack is empty. No peek element\n");
  else
    return stack->items[stack->top];
}

void print_stack(Stack *stack)
{
  printf("\n--- STACK ---\n");
  for (int i = 0; i <= stack->top; i++)
  {
    printf("%d\n", stack->items[i]);
  }
  printf("\n");
}


int main(int argc, char *argv[])
{
  Stack *stack = create_stack(10);

  push(stack, 1);
  push(stack, 2);
  push(stack, 3);
  push(stack, 4);
  printf("Peek : %d", peek(stack));

  print_stack(stack);

  pop(stack);
  printf("Peek : %d", peek(stack));

  print_stack(stack);

  return 0;
}