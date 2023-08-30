#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashTable {
  char *keys[TABLE_SIZE];
  int values[TABLE_SIZE];
} HashTable;

int hash_function(const char *key);
void init(HashTable *ht);
void insert(HashTable *ht, const char *key, int value);
int get(HashTable *ht, const char *key);
void delete(HashTable *ht, const char *key);
void clean(HashTable *ht);
void display(HashTable *ht);

int main(int argc, char *argv[])
{
  HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
  init(ht);

  insert(ht, "Jonathan", 19);
  insert(ht, "Joseph", 18);
  insert(ht, "Jotaro", 17);
  insert(ht, "Josuke", 16);
  insert(ht, "Jolyne", 19);

  printf("Jonathan is %d year old\n", get(ht, "Jonathan"));

  display(ht);

  delete(ht, "Jonathan");
  delete(ht, "Josuke");

  if (get(ht, "Jonathan") == -1) {
    printf("Key \"Jonathan\" doesn't exist\n");
  }

  display(ht);

  clean(ht);

  return 0;
}

// Use linear probing to resolve collision
int hash_function(const char *key)
{
  unsigned int hash = 0;
  while (*key) {
    hash = (hash * 131) + *key++;
  }
  return hash % TABLE_SIZE;
}

void init(HashTable *ht)
{
  for (int i = 0; i < TABLE_SIZE; i++) {
    ht->keys[i] = NULL;
    ht->values[i] = -1;
  }
}

void insert(HashTable *ht, const char *key, int value)
{
  unsigned int index = hash_function(key);
  unsigned int initialIndex = index;

  while (ht->keys[index] != NULL) {
    // Use linear probing to move to the next slot
    index = (index + 1) % TABLE_SIZE;

    if (index == initialIndex) {
      printf("Hash table is full, cannot insert\n");
    }
  }

  ht->keys[index] = strdup(key);
  ht->values[index] = value;
}

int get(HashTable *ht, const char *key)
{
  unsigned int index = hash_function(key);
  unsigned int initialIndex = index;

  while (ht->keys[index] != NULL) {
    if (strcmp(ht->keys[index], key) == 0) {
      return ht->values[index];
    }

    index = (index + 1) % TABLE_SIZE;

    if (index == initialIndex || ht->keys[index] == NULL)
      return -1;
  }

  return -1;
}

void delete(HashTable *ht, const char *key)
{
  unsigned int index = hash_function(key);
  unsigned int initialIndex = index;

  while (ht->keys[index] != NULL) {
    if (strcmp(ht->keys[index], key) == 0) {
      ht->keys[index] = NULL;
      ht->values[index] = -1;
      return;
    }

    index = (index + 1) % TABLE_SIZE;

    if (index == initialIndex || ht->keys[index] == NULL) {
      printf("Key doesn't exist, cannot delete\n");
      return;
    }
  }
}

void clean(HashTable *ht)
{
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (ht->keys[i] != NULL) {
      free(ht->keys[i]);
      ht->keys[i] = NULL;
      ht->values[i] = -1;
    }
  }
}

void display(HashTable *ht)
{
  printf("\nHash table :\n");
  printf("-------------\n");
  printf("\"Key\": Value\n\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (ht->keys[i] != NULL) {
      printf("\"%s\": %d\n", ht->keys[i], ht->values[i]);
    }
  }
  printf("\n");
}