#include <stdio.h>
#include <stdlib.h>

int binary_search(int array[], int x, int low, int high)
{
  while (low < high) {
    int mid = low + (high - low) / 2;

    if (array[mid] == x) {
      return mid;
    } else if (x > array[mid]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  
  return -1;
}

int main()
{
  int array[] = {1, 2, 4, 5, 11, 12, 13, 17, 80};
  int size = sizeof(array)/sizeof(array[0]);

  int result = binary_search(array, 11, 0, size - 1);
  if (result == -1) {
    printf("Element not found");
  } else {
    printf("Element %d found at index %d", array[result], result);
  }
}