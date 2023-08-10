## LeetCode exercises

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/design-circular-deque/">Design Circular Deque</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/maximal-rectangle/">Maximal Rectangle</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/sliding-window-maximum/">Sliding Window Maximum</a><br>
</div>

### My solution

<details>
<summary>Design Circular Deque</summary>
<br>

Notes : Nothing different from a regular deque

```c
typedef struct {
    int front;
    int rear;
    int *items;
    unsigned int size;
} MyCircularDeque;


MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque *deque = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    deque->front = -1;
    deque->rear = -1;
    deque->size = k;
    deque->items = (int*)malloc(sizeof(int) * k);

    return deque;
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
  return obj->front == -1;
}

bool myCircularDequeIsFull(MyCircularDeque* obj) {
  return (obj->front == obj->rear + 1) || (obj->front == 0 && obj->rear == obj->size - 1);
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
  if (myCircularDequeIsFull(obj)) {
      return false;
  } else {
      if (obj->front == -1)
        obj->front = obj->rear = 0;
    else if (obj->front == 0)
        obj->front = obj->size - 1;
    else
        obj->front--;

    obj->items[obj->front] = value;
    return true;
  }
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
  if (myCircularDequeIsFull(obj)) {
      return false;
  } else {
      if (obj->front == -1)
        obj->front = obj->rear = 0;
    else if (obj->rear == obj->size - 1)
        obj->rear = 0;
    else
        obj->rear++;

    obj->items[obj->rear] = value;
    return true;
  }
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
  if (myCircularDequeIsEmpty(obj)) {
      return false;
  } else {
      if (obj->front == obj->rear)
        obj->front = obj->rear = -1;
    else if (obj->front == obj->size - 1)
        obj->front = 0;
    else
        obj->front++;

    return true;
  }
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
  if (myCircularDequeIsEmpty(obj)) {
      return false;
  } else {
      if (obj->front == obj->rear)
        obj->front = obj->rear = -1;
    else if (obj->rear == 0)
        obj->rear = obj->size - 1;
    else
        obj->rear--;

    return true;
  }
}

int myCircularDequeGetFront(MyCircularDeque* obj) {
  if (myCircularDequeIsEmpty(obj)) return -1;
  return obj->items[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
  if (myCircularDequeIsEmpty(obj)) return -1;
  return obj->items[obj->rear];
}

void myCircularDequeFree(MyCircularDeque* obj) {
    free(obj->items);
    free(obj);
}
```
</details>