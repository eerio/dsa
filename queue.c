#include <stdio.h>
#define QSIZE (20U)

typedef struct Queue {
    int arr[QSIZE];
    int head;
    int tail;
} Queue;

void enqueue(Queue *q, int x) {
    q->arr[q->tail++] = x;
    q->tail %= QSIZE;
}

int dequeue(Queue *q) {
    int res = q->arr[q->head++];
    q->head %= QSIZE;
    return res;
}

int main() {
    Queue q = { .arr = {0}, .head = 0, .tail = 0 };
    
    for (int i=0; i < 17; ++i) {
        enqueue(&q, 2 * i);
    }
    
    for (int i=0; i < 7; ++i) {
        printf("%d ", dequeue(&q));
    }

    for (int i=10; i < 20; ++i) {
        enqueue(&q, i * i);
    }

    for (int i=0; i < 20; ++i) {
        printf("%d ", dequeue(&q));
    }

    putchar('\n');

    return 0;
}

