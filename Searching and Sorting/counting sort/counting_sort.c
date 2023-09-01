#include <stdio.h>
#include <stdlib.h>

void counting_sort(int array[], int size)
{
  int *output = (int*)malloc(size * sizeof(int));
  output[0] = 0;

  // Find the larger number in array
  int max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
    output[i] = 0;
  }

  // Initialize a count array of size max + 1 to store the number of
  // occurences of each number
  int *count = (int*)malloc((max + 1) * sizeof(int));
  for (int i = 0; i < max + 1; i++) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    int num = array[i];
    count[num]++;
  }

  // Store the cumulative sum in the count array
  for (int i = 1; i < max + 1; i++) {
    count[i] += count[i-1];
  }

  // Find the count of each element in the original array, and place it at index
  // count[i] - 1 in the output array
  for (int i = size - 1; i >= 0; i--) {
    int num = array[i];
    output[count[num] - 1] = num;
    count[num]--;
  }

  // Copy the output element inside original array
  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }

  free(output);
  free(count);
}

int main()
{
  int array[] = {1, 2, 9, 3, 4, 3, 6, 7, 1};
  int size = sizeof(array) / sizeof(array[0]);

  counting_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
