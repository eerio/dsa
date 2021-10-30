#include<stdio.h>
#define LSIZE (10U)

typedef struct LinkedList {
    int next[LSIZE];
    int key[LSIZE];
    int prev[LSIZE];
    size_t head;
    size_t free;
} LinkedList;

size_t search(LinkedList *list, int x) {
    size_t elem = list->head;
    
    while (list->key[elem] != x) {
        elem = list->next[elem];
    }

    return elem;
}

void push_front(LinkedList *list, int x) {
    size_t ind = list->free;
    list->free = list->key[list->free];  // just get next free
    list->key[ind] = x;
    list->next[ind] = list->head;
    list->prev[ind] = NULL;
    list->head = ind;
}


int pop(LinkedList *list, size_t ind) {
    int ret = list->key[ind];
    list->key[ind] = (int)list->free;
    list->free = ind;
    list->next[ind] = NULL;
    list->prev[ind] = NULL;
    return ret;
}

void remove(LinkedList *list, int x) {
    pop(list, search(list, x));
}

void init_list(LinkedList *list) {
    for (int i=0; i < LSIZE - 1; ++i) {
        list->key[i] = i + 1;
    }
    list->key[LSIZE - 1] = NULL;
    
    for (int i=0; i < LSIZE; ++i) {
        list->next[i] = NULL;
        list->prev[i] = NULL;
    }
    list->head = 0;
    list->free = 0;
}

int main() {
    LinkedList list;
    init_list(&list);

    push_front(list, 14);
    push_front(list, 15);
    
    return 0;
}

