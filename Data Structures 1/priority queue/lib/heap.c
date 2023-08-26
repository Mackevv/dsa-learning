#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int parent(int i)
{
  return (i-1)/2;
}

Heap *make_heap(int capacity)
{
  Heap *h = (Heap*)malloc(sizeof(Heap));
  h->items = (int*)malloc(sizeof(int) * capacity);
  h->capacity = capacity;
  h->size = 0;

  return h;
}

void min_heapify(Heap *heap, int i)
{
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int smallest = i;

  if (left < heap->size && heap->items[left] < heap->items[i])
    smallest = left;
  if (right < heap->size && heap->items[right] < heap->items[smallest])
    smallest = right;

  if (smallest != i) {
    swap(&heap->items[i], &heap->items[smallest]);
    min_heapify(heap, smallest);
  }
}

void build_min_heap(Heap *heap)
{
  int n = heap->size;
  for (int i = n/2; i >= 0; i--) {
    min_heapify(heap, i);
  }
}

void insert_key(Heap *heap, int key)
{
  if (heap->size == heap->capacity)
    exit(EXIT_FAILURE);

  int i = heap->size;
  heap->items[i] = key;
  heap->size++;

  while (i != 0 && heap->items[i] < heap->items[parent(i)]) {
    swap(&heap->items[i], &heap->items[parent(i)]);
    i = parent(i);
  }
}

void decrease_key(Heap *heap, int key, int newKey)
{
  int i;
  for (i = 0; i < heap->size; i++) {
    if (heap->items[i] == key) break;
  }

  if (i == heap->size)
    return;

  if (newKey > key)
    return;

  heap->items[i] = newKey;
  while (i != 0 && heap->items[i] < heap->items[parent(i)]) {
    swap(&heap->items[i], &heap->items[parent(i)]);
    i = parent(i);
  }
}

int extract_min(Heap *heap)
{
  if (heap->size == 0)
    exit(EXIT_FAILURE);
  if (heap->size == 1) {
    heap->size = 0;
    return heap->items[0];
  }

  int root = heap->items[0];
  heap->items[0] = heap->items[heap->size - 1];
  heap->size--;

  build_min_heap(heap);

  return root;
}

void delete_key(Heap *heap, int key)
{
  decrease_key(heap, key, -100000);
  extract_min(heap);
}