## LeetCode

<div>
  <span style="color: green">Easy</span> : <a href="https://leetcode.com/problems/valid-parentheses/">Valid Parentheses</a><br>
  <span style="color: #FFAE42">Medium</span> : <a href="https://leetcode.com/problems/evaluate-reverse-polish-notation/">Evaluate Reverse Polish Notation</a><br>
  <span style="color: red">Hard</span> : <a href="https://leetcode.com/problems/longest-valid-parentheses/">Longest Valid Parentheses</a><br>
</div>

### My solution

<details>
<summary>Valid Parentheses</summary>
<br>

Notes : Stack data structures is suitable in this problem because the **first** opening bracket should be the **last** to be closed. We recognize here the FILO (First In Last Out) pattern of stack data structure.

```c
typedef struct {
    char items[100000];
    int top;
} Stack;

Stack *create_stack()
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;

    return stack;
}

int is_empty(Stack *stack)
{
    return stack->top == -1;
}

int is_full(Stack *stack)
{
    return stack->top == 100000;
}

void push(Stack *stack, char item)
{
    if (is_full(stack))
        printf("Stack is full\n");
    else {
        stack->top++;
        stack->items[stack->top] = item;
    }
}

void pop(Stack *stack)
{
    if (is_empty(stack))
        printf("Stack is empty, nothing to remove\n");
    else
        stack->top--;
}

void printStack(Stack *stack)
{
  for (int i = 0; i <= stack->top; i++)
  {
    printf("%c", stack->items[i]);
  }
}

int isValid(char * s){
    Stack *stack = create_stack();

    int count;
    for (count = 0; s[count] != '\0'; count++);

    for (int i = 0; i < count; i++) 
    {
        char current = s[i];
        if (current == '(' || current == '[' || current == '{') {
            push(stack, s[i]);
        } else {
            if (is_empty(stack))
                return 0;
            if (
                current == ')' && stack->items[stack->top] != '('
                || current == ']' && stack->items[stack->top] != '['
                || current == '}' && stack->items[stack->top] != '{'
            ) {
              return 0;
            }
            pop(stack);
        }
    }

    return is_empty(stack);
}
```
</details>