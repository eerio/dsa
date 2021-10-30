#include<stdio.h>

typedef struct Stack {
    int a[10];
    int top;
} Stack;

void push(Stack *s, int x) {
    s->a[s->top++] = x;
}

int pop(Stack *s) {
    return s->a[--s->top];
}

int main() {
    Stack s = { .a = {0}, .top = 0 };

    for (int i=0; i < 10; ++i) {
        push(&s, i * 2);
    }

    for (int i=0; i < 10; ++i) {
        printf("%d ", pop(&s));
    }

    return 0;
}

