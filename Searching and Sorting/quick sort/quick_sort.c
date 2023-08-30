#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int array[], int low, int high)
{
  int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] < pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);

  return (i + 1);
}

void quick_sort(int array[], int low, int high)
{
  if (low < high) {
    int pivot = partition(array, low, high);

    quick_sort(array, low, pivot - 1);
    quick_sort(array, pivot + 1, high);
  }
}

int main()
{
  int array[] = {3, 4, 5, 3, 5, 8, 56, 23, 11, 10, 3};
  int size = sizeof(array) / sizeof(array[0]);

  quick_sort(array, 0, size - 1);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
