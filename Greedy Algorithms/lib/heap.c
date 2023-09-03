#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int parent(int i)
{
  return (i - 1) / 2;
}

Heap *make_heap(int capacity)
{
  Heap *newHeap = (Heap*)malloc(sizeof(Heap));
  newHeap->size = 0;
  newHeap->capacity = capacity;
  newHeap->items = (int*)malloc(capacity * sizeof(int));

  return newHeap;
}

void min_heapify(Heap *heap, int index)
{
  int smallest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < heap->size && heap->items[left] < heap->items[smallest])
    smallest = left;
  if (right < heap->size && heap->items[right] < heap->items[smallest])
    smallest = right;

  if (smallest != index) {
    swap(&heap->items[smallest], &heap->items[index]);
    min_heapify(heap, smallest);
  }
}

void build_min_heap(Heap *heap)
{
  int n = heap->size;
  for (int i = floor(n/2); i >= 0; i--) {
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

int extract_min(Heap *heap)
{
  if (heap->size == 0)
    exit(EXIT_FAILURE);
  if(heap->size == 1) {
    heap->size = 0;
    return heap->items[0];
  }

  int root = heap->items[0];
  heap->items[0] = heap->items[heap->size - 1];
  heap->size--;

  build_min_heap(heap);

  return root;
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