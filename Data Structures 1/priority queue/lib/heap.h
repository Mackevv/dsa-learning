#ifndef H_HEAP
#define H_HEAP

typedef struct Heap {
  int *items;
  int capacity;
  int size;
} Heap;

void swap(int *a, int *b);
int parent(int i);
Heap *make_heap();
void min_heapify(Heap *heap, int i);
void insert_key(Heap *heap, int key);
void delete_key(Heap *heap, int key);
void decrease_key(Heap *heap, int key, int newKey);
int extract_min(Heap *heap);
void build_min_heap(Heap *heap);

#endif