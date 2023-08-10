#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct Node Node;

void insert_beginning(Node **headRef, int newData)
{
  Node *newNode = (Node*)malloc(sizeof(Node));

  newNode->data = newData;
  newNode->next = (*headRef);

  (*headRef) = newNode;
}

void insert_after(Node *prevNode, int newData)
{
  if (prevNode == NULL) {
    printf("The given previous node cannot be NULL.\n");
    return;
  }

  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->data = newData;
  newNode->next = prevNode->next;
  prevNode->next = newNode;
}

void insert_end(Node **headRef, int newData)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->data = newData;
  newNode->next = NULL;

  Node *last = (*headRef);

  if (*headRef == NULL) {
    (*headRef) = newNode;
    return;
  }

  while (last->next != NULL)
    last = last->next;

  last->next = newNode;
}

void delete_node(Node **headRef, int key)
{
  Node *current = *headRef;
  Node *previous;

  // If the first node is the targetted one, delete it
  if (current != NULL && current->data == key) {
    *headRef = current->next;
    free(current);
  }

  while (current != NULL && current->data != key) {
    previous = current;
    current = current->next;
  }

  // If the key was not find
  if (current == NULL) return;

  // Delete the targetted node
  previous->next = current->next;
  free(current);
}

int search_node(Node **headRef, int key)
{
  Node *current = *headRef;

  while (current != NULL) {
    if (current->data == key) return 1;
    current = current->next;
  }

  return 0;
}

// Sort linked list using bubble sort
void sort_linked_list(Node **headRef)
{
  Node *current = *headRef;
  Node *index = NULL;
  int temp;

  if (headRef == NULL) {
    return;
  } else {
    while (current != NULL) {
      index = current->next;

      while (index != NULL) {
        if (current->data > index->data) {
          temp = current->data;
          current->data = index->data;
          index->data = temp;
        }
        index = index->next;
      }

      current = current->next;
    }
  }
}

void print_linked_list(Node *node) {
  printf("\n");
  while (node != NULL) {
    printf("%d -> ", node->data);
    node = node->next;
  }
  printf("\n\n");
}

int main(int *argc, char *argv[])
{
  Node *head = NULL;

  insert_beginning(&head, 2);
  insert_end(&head, 3);
  insert_end(&head, 5);
  insert_beginning(&head, 9);
  insert_after(head->next->next, 4);

  print_linked_list(head);

  delete_node(&head, 3);
  print_linked_list(head);

  if (search_node(&head, 4))
    printf("%d was found\n", 4);
  else
    printf("%d was not found\n", 4);

  printf("Sorted linked list :\n");
  sort_linked_list(&head);
  print_linked_list(head);

  return 0;
}