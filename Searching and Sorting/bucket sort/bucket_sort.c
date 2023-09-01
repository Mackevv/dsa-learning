#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  float value;
  struct Node *next;
} Node;

void insertion_sort(Node *bucket)
{
  if (bucket == NULL || bucket->next == NULL)
    return;

  Node *sorted = NULL;
  Node *current = bucket;

  while (current != NULL) {
    Node *next = current->next;

    if (sorted == NULL || current->value < sorted->value) {
      current->next = sorted;
      sorted = current;
    } else {
      Node *search = sorted;
      while (search->next != NULL && current->value >= search->next->value) {
        search = search->next;
      }

      current->next = search->next;
      search->next = current;
    }

    current = next;
  }

  bucket = sorted;
}

void bucket_sort(float array[], int size)
{
  Node **buckets = (Node**)malloc(size * sizeof(Node*));

  for (int i = 0; i < size; i++) {
    buckets[i] = NULL;
  }

  for (int i = 0; i < size; i++) {
    int index = 10 * array[i];
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = array[i];
    node->next = buckets[index];
    buckets[index] = node;
  }

  for (int i = 0; i < size; i++) {
    insertion_sort(buckets[i]);
  }

  int index = 0;
  for (int i = 0; i < size; i++) {
    Node *current = buckets[i];
    while (current != NULL) {
      array[index] = current->value;
      index++;
      current = current->next;
    }
  }
}

int main() {
  float array[] = {0.42, 0.32, 0.33, 0.52, 0.37, 0.47, 0.51};
  int size = sizeof(array) / sizeof(array[0]);

  bucket_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%.2f ", array[i]);
  }

  return 0;
}