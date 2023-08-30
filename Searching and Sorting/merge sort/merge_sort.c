#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int p, int q, int r)
{
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = array[p + i];

  for (int i = 0; i < n2; i++)
    M[i] = array[q + 1 + i];

  int i, j, k;
  i = j = 0;
  k = p;

  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      array[k] = L[i];
      i++;
    } else {
      array[k] = M[j];
      j++;
    }
    
    k++;
  }

  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    array[k] = M[j];
    j++;
    k++;
  }
}

void merge_sort(int array[], int p, int r)
{
  if (p < r) {
    int q = p + (r - p)/2;

    merge_sort(array, p, q);
    merge_sort(array, q+1, r);

    merge(array, p, q, r);
  }
}

int main()
{
  int array[] = {8, 2, 4, 19, 5, 7, 56, 23, 11, 10, 3};
  int size = sizeof(array)/sizeof(array[0]);

  merge_sort(array, 0, size - 1);

  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
     
  return 0;
}
