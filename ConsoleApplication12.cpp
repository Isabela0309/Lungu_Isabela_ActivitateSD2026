#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pair {
    char* number;
    short base;
};

struct PairVector {
    struct Pair* data;
    int size;
    int capacity;
};

struct IntVector {
    int* data;
    int size;
    int capacity;
};

void initPairVector(struct PairVector* vec) {
    vec->size = 0;
    vec->capacity = 2;
    vec->data = (struct Pair*)malloc(vec->capacity * sizeof(struct Pair));
    if (vec->data == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}

void pushBackPair(struct PairVector* vec, const char* number, short base) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (struct Pair*)realloc(vec->data, vec->capacity * sizeof(struct Pair));
        if (vec->data == NULL) {
            printf("Memory reallocation failed.\n");
            exit(1);
        }
    }

    vec->data[vec->size].number = (char*)malloc(strlen(number) + 1);
    if (vec->data[vec->size].number == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(vec->data[vec->size].number, number);
    vec->data[vec->size].base = base;
    vec->size++;
}

void freePairVector(struct PairVector* vec) {
    int i;
    for (i = 0; i < vec->size; i++) {
        free(vec->data[i].number);
    }
    free(vec->data);
}

void initIntVector(struct IntVector* vec) {
    vec->size = 0;
    vec->capacity = 2;
    vec->data = (int*)malloc(vec->capacity * sizeof(int));
    if (vec->data == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}

void pushBackInt(struct IntVector* vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (int*)realloc(vec->data, vec->capacity * sizeof(int));
        if (vec->data == NULL) {
            printf("Memory reallocation failed.\n");
            exit(1);
        }
    }

    vec->data[vec->size] = value;
    vec->size++;
}

void freeIntVector(struct IntVector* vec) {
    free(vec->data);
}

int base10Transformation(struct Pair pair) {
    int value = 0;
    int i;
    char c;

    for (i = 0; pair.number[i] != '\0'; i++) {
        c = pair.number[i];
        switch (c) {
        case 'A': value = value * pair.base + 10; break;
        case 'B': value = value * pair.base + 11; break;
        case 'C': value = value * pair.base + 12; break;
        case 'D': value = value * pair.base + 13; break;
        case 'E': value = value * pair.base + 14; break;
        case 'F': value = value * pair.base + 15; break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            value = value * pair.base + (c - '0');
            break;
        default:
            printf("Invalid input.\n");
            return -1;
        }
    }

    return value;
}

void checkingEqualPairs(struct PairVector* vec) {
    struct IntVector base10Numbers;
    int i, j;

    initIntVector(&base10Numbers);

    for (i = 0; i < vec->size; i++) {
        int number = base10Transformation(vec->data[i]);
        if (number != -1) {
            pushBackInt(&base10Numbers, number);
        }
        else {
            freeIntVector(&base10Numbers);
            return;
        }
    }

    for (i = 0; i < base10Numbers.size; i++) {
        for (j = i + 1; j < base10Numbers.size; j++) {
            if (base10Numbers.data[i] == base10Numbers.data[j]) {
                printf("Number: %s in base: %d is equal to number: %s in base: %d\n",
                    vec->data[i].number, vec->data[i].base,
                    vec->data[j].number, vec->data[j].base);
            }
        }
    }

    freeIntVector(&base10Numbers);
}

int main() {
    struct PairVector vec;
    char buffer[100];
    short base;
    int n, i;

    initPairVector(&vec);

    printf("Enter the number of elements:\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%99s %hd", buffer, &base);
        pushBackPair(&vec, buffer, base);
    }

    checkingEqualPairs(&vec);

    freePairVector(&vec);

    return 0;
}