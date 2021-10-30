#include <stdio.h>
#define QSIZE (20U)

typedef struct Queue {
    int arr[QSIZE];
    int head;
    int tail;
} Queue;

void push_back(Queue *q, int x) {
    q->arr[q->tail] = x;
    q->tail = (q->tail + 1) % QSIZE;
}

void push_front(Queue *q, int x) {
    q->head = (q->head - 1 + QSIZE) % QSIZE;
    q->arr[q->head] = x;
}

int pop_back(Queue *q) {
    q->tail = (q->tail - 1 + QSIZE) % QSIZE;
    return q->arr[q->tail];
}

int pop_front(Queue *q) {
    int res = q->arr[q->head];
    q->head = (q->head + 1) % QSIZE;
    return res;
}

int main() {
    Queue q = { .arr = {0}, .head = 0, .tail = 0 };
    push_front(&q, 1231);
    pop_front(&q);
    push_back(&q, 2137);
    pop_back(&q);
    
    for (int i=0; i < 17; ++i) {
        push_back(&q, 2 * i);
    }
    
    for (int i=0; i < 7; ++i) {
        printf("%d ", pop_front(&q));
    }

    for (int i=10; i < 20; ++i) {
        push_back(&q, i * i);
    }

    for (int i=0; i < 20; ++i) {
        printf("%d ", pop_front(&q));
    }

    putchar('\n');

    return 0;
}

