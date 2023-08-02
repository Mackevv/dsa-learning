## LeetCode

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/implement-queue-using-stacks/">Implement Queues using Stacks</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/number-of-recent-calls/">Number of Recent Calls</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/sliding-window-maximum/">Sliding Window Maximum</a><br>
</div>


### My solution

<details>
<summary>Implement Queues using Stacks</summary>
<br>

Notes :

1. Push O(n), Pop O(1)
```c
// Stack implementation

typedef struct {
  int *items;
  int top;
  unsigned int size;
} Stack;

Stack *new_stack(unsigned int size) {
  Stack *stack = (Stack*)malloc(sizeof(Stack));
  stack->size = size;
  stack->top = -1;
  stack->items = (int*)malloc(sizeof(int) * stack->size);

  return stack;
}

int is_empty(Stack *stack) {
  return stack->top == -1;
}

int is_full(Stack *stack) {
  return stack->top == stack->size;
}

void push(Stack *stack, int item) {
  if (!is_full(stack)) {
    stack->top++;
    stack->items[stack->top] = item;
  }
}

int pop(Stack *stack) {
  if (!is_empty(stack)) {
    stack->top--;
    return stack->items[stack->top + 1];
  } else {
    printf("Queue is empty");
  }
  return 0;
}

// Queue implementation using only two stacks

typedef struct {
    Stack *stack1;
    Stack *stack2;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue *queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->stack1 = new_stack(1000);
    queue->stack2 = new_stack(1000);
    return queue;
}

void myQueuePush(MyQueue* obj, int x) {
    if (is_empty(obj->stack1)) {
        push(obj->stack1, x);
    } else {
        while(!is_empty(obj->stack1))
          push(obj->stack2, pop(obj->stack1));
        push(obj->stack1, x);
        while(!is_empty(obj->stack2))
          push(obj->stack1, pop(obj->stack2));
    }
}

int myQueuePop(MyQueue* obj) {
  return pop(obj->stack1);
}

int myQueuePeek(MyQueue* obj) {
  return obj->stack1->items[obj->stack1->top];
}

bool myQueueEmpty(MyQueue* obj) {
  return is_empty(obj->stack1);
}

void myQueueFree(MyQueue* obj) {
    free(obj->stack1->items);
}
```

2. Push O(1), Pop amortized O(1)

```c
// Stack implementation

typedef struct {
  int *items;
  int top;
  unsigned int size;
} Stack;

Stack *new_stack(unsigned int size) {
  Stack *stack = (Stack*)malloc(sizeof(Stack));
  stack->size = size;
  stack->top = -1;
  stack->items = (int*)malloc(sizeof(int) * stack->size);

  return stack;
}

int is_empty(Stack *stack) {
  return stack->top == -1;
}

int is_full(Stack *stack) {
  return stack->top == stack->size;
}

void push(Stack *stack, int item) {
  if (!is_full(stack)) {
    stack->top++;
    stack->items[stack->top] = item;
  }
}

int pop(Stack *stack) {
  if (!is_empty(stack)) {
    stack->top--;
    return stack->items[stack->top + 1];
  } else {
    printf("Queue is empty");
  }
  return 0;
}

// Queue implementation using only two stacks

typedef struct {
    Stack *stack1;
    Stack *stack2;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue *queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->stack1 = new_stack(1000);
    queue->stack2 = new_stack(1000);
    return queue;
}

void myQueuePush(MyQueue* obj, int x) {
    push(obj->stack1, x);
}

int myQueuePop(MyQueue* obj) {
  if(is_empty(obj->stack2)) {
    while (!is_empty(obj->stack1)) {
      push(obj->stack2, pop(obj->stack1));
    }
  }
  return pop(obj->stack2);
}

int myQueuePeek(MyQueue* obj) {
  if (!is_empty(obj->stack2))
    return obj->stack2->items[obj->stack2->top];
  else
    return obj->stack1->items[0];
}

bool myQueueEmpty(MyQueue* obj) {
  return (is_empty(obj->stack1) && is_empty(obj->stack2));
}

void myQueueFree(MyQueue* obj) {
    free(obj->stack1->items);
}
```
</details>