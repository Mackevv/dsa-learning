#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int array[], int size)
{
  for (int i = 1; i <= size - 1; i++) {
    int key = array[i];
    int j = i - 1;

    while (key < array[j] && j >= 0) {
      array[j + 1] = array[j];
      j--;
    }

    array[j + 1] = key;
  }
}

int main()
{
  int array[] = {8, 2, 4, 19, 5, 7, 56, 23, 11, 10, 3};
  int size = sizeof(array) / sizeof(array[0]);

  insertion_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
