#include <stdio.h>
#include <stdlib.h>

// Optimized bubble sort using a swapped boolean to indicate whether a swap 
// occurs in this iteration. If not, the element is already in place therefore 
// go to the next iteration without comparing it to the rest of the array

void bubble_sort(int *array, int size)
{
  for (int i = 0; i < size - 1; i++) {
    int swapped = 0;

    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j+1]) {
        int temp = array[j+1];
        array[j+1] = array[j];
        array[j] = temp;
        
        swapped = 1;
      }
    }

    if (swapped = 0) break;
  }
}

int main()
{
  int array[] = {8, 2, 4, 19, 5, 7, 56, 23, 11, 10, 3};

  int size = sizeof(array)/sizeof(array[0]);

  bubble_sort(array, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
}