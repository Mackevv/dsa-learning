#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b);
void heapify(int array[], int size, int index);
void build_max_heap(int array[], int size);
void insert(int array[], int *size, int data);
void delete(int array[], int *size, int data);

int main(int *argc, char *argv[])
{
  int array[10];
  int size = 0;

  insert(array, &size, 9);
  insert(array, &size, 3);
  insert(array, &size, 1);
  insert(array, &size, 2);
  insert(array, &size, 6);
  insert(array, &size, 11);
  insert(array, &size, 21);
  insert(array, &size, 17);
  insert(array, &size, 7);
  insert(array, &size, 90);
  insert(array, &size, 27);
  insert(array, &size, 18);

  for (int i = 0; i < size; i++) {
    printf("%d, ", array[i]);
  } 

  return 0;
}

void swap(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

void heapify(int array[], int size, int index)
{
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int max = index;

  if (left < size && array[left] > array[index])
    max = left;
  if (right < size && array[right] > array[index])
    max = right;

  if (max != index) {
    swap(&array[index], &array[max]);
    heapify(array, size, max);
  }
}

void build_max_heap(int array[], int size)
{
  for (int i = floor(size/2) + 1; i >= 0; i--) {
    heapify(array, size, i);
  }
}

void insert(int array[], int *size, int data)
{
  if (size == 0) {
    array[0] = data;
    (*size)++;
  } else {
    array[*size] = data;
    (*size)++;

    build_max_heap(array, *size);
  }
}

void delete(int array[], int *size, int data)
{
  int i;
  for (i = 0; i < *size; i++) {
    if (array[i] == data) break;
  }

  swap(&array[i], &array[*size - 1]);
  (*size)--;
  build_max_heap(array, *size);
}