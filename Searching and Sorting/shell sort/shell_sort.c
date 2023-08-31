#include <stdio.h>
#include <stdlib.h>

void shell_sort(int array[], int size)
{
  for (int gap = size / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < size; i++) {
      int temp = array[i];
      int j;

      for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
        array[j] = array[j - gap];
      }

      array[j] = temp;
    }
  }
}

int main()
{
  int array[] = {8, 2, 4, 19, 5, 7, 56, 23, 11, 10, 3};
  int size = sizeof(array) / sizeof(array[0]);

  shell_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
