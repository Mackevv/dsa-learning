#include <stdio.h>
#include <stdlib.h>

void selection_sort(int array[], int size)
{
  for (int i = 0; i < size - 1; i++) {
    int minimum = i;

    for (int j = i+1; j < size; j++) {
      if (array[j] < array[minimum]) {
        minimum = j;
      }
    }

    int temp = array[minimum];
    array[minimum] = array[i];
    array[i] = temp;
  }
}

int main()
{
  int array[] = {8, 2, 4, 19, 5, 7, 56, 23, 11, 10, 3};
  int size = sizeof(array) / sizeof(array[0]);

  selection_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
