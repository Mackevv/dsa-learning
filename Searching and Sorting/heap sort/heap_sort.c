#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(int array[], int size, int index)
{
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int largest = index;

  if (left < size && array[left] > array[largest])
    largest = left;
  if (right < size && array[right] > array[largest])
    largest = right;

  if (largest != index) {
    swap(&array[index], &array[largest]);
    heapify(array, size, largest);
  }
}

void heap_sort(int array[], int size)
{
  for (int i = floor(size/2); i >= 0; i--) {
    heapify(array, size, i);
  }

  for (int i = size - 1; i >= 0; i--) {
    swap(&array[0], &array[i]);

    // Heapify root element to have again highest number at index 0
    heapify(array, i, 0);
  }
}

int main()
{
  int array[] = {8, 2, 4, 19, 5, 7, 56, 23, 11, 10, 3};
  int size = sizeof(array) / sizeof(array[0]);

  heap_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
