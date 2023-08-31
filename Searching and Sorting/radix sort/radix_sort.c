#include <stdio.h>
#include <stdlib.h>

void counting_sort(int array[], int size, int place)
{
  int *output = (int*)malloc(size * sizeof(int));

  int max = (array[0] / place) % 10;
  for (int i = 1; i < size; i++) {
    if ((array[i] / place) % 10 > max) {
      max = (array[i] / place) % 10;
    }
  }

  int *count = (int*)malloc((max + 1) * sizeof(int));
  for (int i = 0; i < max + 1; i++) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    int num = (array[i] / place) % 10;
    count[num]++;
  }

  for (int i = 1; i < max + 1; i++) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    output[count[(array[i] / place) % 10] - 1] = array[i];
    count[(array[i] / place) % 10]--;
  }

  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }

  free(output);
  free(count);
}

void radix_sort(int array[], int size)
{
  int max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }

  for (int place = 1; max / place > 0; place *= 10) {
    counting_sort(array, size, place);
  }
}

int main()
{
  int array[] = {112, 98, 21, 10, 445, 7, 65};
  int size = sizeof(array) / sizeof(array[0]);

  radix_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
