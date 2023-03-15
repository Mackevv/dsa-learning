#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main(int argc, char *argv[])
{
  Stack *newStack = new();
  Person john = { "John Doe", 23 };
  Person joseph = { "Joseph Joestar", 81 };
  Person jonathan = { "Jonathan Joestar", 23 };

  push(newStack, &john);
  push(newStack, &joseph);
  push(newStack, &jonathan);

  printf("\n--- STACK STATE ---\n");
  display(newStack);

  printf("Removing person : %s\n", pop(newStack).name);

  printf("\n--- STACK STATE ---\n");
  display(newStack);

  return 0;
}