#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int checkSuperiority(int* vec, int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += vec[i];
    }

    int average = sum / size;
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (vec[i] > average)
        {
            count++;
        }
    }

    int half = size / 2;

    if (half >= count)
    {
        return 0;
    }

    return 1;
}

int main()
{
    int* vec;
    int n;

    printf("Enter the vector size: ");
    scanf("%d", &n);

    vec = (int*)malloc(n * sizeof(int));

    if (vec == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the vector elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vec[i]);
    }

    if (checkSuperiority(vec, n))
    {
        printf("The vector is superior\n");
    }
    else
    {
        printf("The vector is inferior\n");
    }

    free(vec);

    return 0;
}
