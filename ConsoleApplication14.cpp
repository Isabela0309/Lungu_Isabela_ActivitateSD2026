#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct COADA {
    int* DATA;
    int size_max;
    int BEGIN;
    int END;
};

void initCoada(struct COADA* q, int size_max) {
    q->size_max = size_max;
    q->DATA = (int*)malloc(size_max * sizeof(int));
    q->BEGIN = 0;
    q->END = 0;
}

int EMPTY(struct COADA* q) {
    return q->BEGIN == q->END;
}

int FULL(struct COADA* q) {
    return (q->END + 1) % q->size_max == q->BEGIN;
}

void PUSH(struct COADA* q, int elem) {
    if (!FULL(q)) {
        q->DATA[q->END] = elem;
        q->END = (q->END + 1) % q->size_max;
    }
    else {
        printf("Coada este plina\n");
    }
}

void POP(struct COADA* q) {
    if (!EMPTY(q)) {
        q->BEGIN = (q->BEGIN + 1) % q->size_max;
    }
    else {
        printf("Coada este goala\n");
    }
}

int FRONT(struct COADA* q) {
    if (!EMPTY(q)) {
        return q->DATA[q->BEGIN];
    }
    else {
        printf("Coada este goala\n");
        return -1;
    }
}

void CLEAR(struct COADA* q) {
    q->BEGIN = 0;
    q->END = 0;
}

void freeCoada(struct COADA* q) {
    free(q->DATA);
}

int main() {
    int n, i, elem;
    struct COADA q;

    printf("Introduceti capacitatea maxima a cozii: ");
    scanf("%d", &n);

    initCoada(&q, n);

    printf("Introduceti %d elemente:\n", n - 1);
    for (i = 0; i < n - 1; i++) {
        scanf("%d", &elem);
        PUSH(&q, elem);
    }

    printf("Elementele extrase sunt:\n");
    while (!EMPTY(&q)) {
        printf("%d ", FRONT(&q));
        POP(&q);
    }

    freeCoada(&q);
    return 0;
}