#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Fraction
{
    int numerator;
    int denominator;
};

int greatestCommonDivisor(int a, int b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0)
    {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

void reduction(struct Fraction* f)
{
    int divisor = greatestCommonDivisor(f->numerator, f->denominator);

    if (divisor != 0)
    {
        f->numerator /= divisor;
        f->denominator /= divisor;
    }

    if (f->denominator < 0)
    {
        f->numerator = -f->numerator;
        f->denominator = -f->denominator;
    }
}

struct Fraction arithmeticOperations(struct Fraction a, struct Fraction b, char s[])
{
    int i;
    struct Fraction result;

    for (i = 0; s[i] != '\0'; i++)
    {
        s[i] = toupper((unsigned char)s[i]);
    }

    if (strcmp(s, "ADDITION") == 0)
    {
        result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
        result.denominator = a.denominator * b.denominator;
        reduction(&result);
        return result;
    }
    else if (strcmp(s, "SUBTRACTION") == 0)
    {
        result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
        result.denominator = a.denominator * b.denominator;
        reduction(&result);
        return result;
    }
    else if (strcmp(s, "MULTIPLICATION") == 0)
    {
        result.numerator = a.numerator * b.numerator;
        result.denominator = a.denominator * b.denominator;
        reduction(&result);
        return result;
    }
    else if (strcmp(s, "DIVISION") == 0)
    {
        result.numerator = a.numerator * b.denominator;
        result.denominator = a.denominator * b.numerator;
        reduction(&result);
        return result;
    }
    else
    {
        printf("The arithmetic operation is unknown\n");
        result.numerator = 0;
        result.denominator = 0;
        return result;
    }
}

double transformationToDouble(struct Fraction a)
{
    return (double)a.numerator / a.denominator;
}

struct Fraction comparison(struct Fraction a, struct Fraction b)
{
    double fraction1 = transformationToDouble(a);
    double fraction2 = transformationToDouble(b);

    if (fraction1 < fraction2)
        return b;
    else
        return a;
}

struct Fraction* readData(int* n)
{
    int i;
    struct Fraction* vec;

    printf("Enter the number of elements: ");
    scanf("%d", n);

    vec = (struct Fraction*)malloc((*n) * sizeof(struct Fraction));

    printf("Enter the elements (numerator comes first, denominator after):\n");
    for (i = 0; i < *n; i++)
    {
        scanf("%d %d", &vec[i].numerator, &vec[i].denominator);
        reduction(&vec[i]);
    }

    return vec;
}

void displayData(struct Fraction vec[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d / %d ", vec[i].numerator, vec[i].denominator);
    }
    printf("\n");
}

void sortFractions(struct Fraction vec[], int n)
{
    int i, j;
    struct Fraction temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (transformationToDouble(vec[i]) > transformationToDouble(vec[j]))
            {
                temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

int main()
{
    int n, i;
    struct Fraction* vec = readData(&n);

    sortFractions(vec, n);

    printf("\nFractions after sorting:\n");
    displayData(vec, n);

    double sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += transformationToDouble(vec[i]);
    }

    printf("Sum of fractions transformed to double = %.2f\n", sum);

    struct Fraction arithmeticOperation1;
    printf("Enter the first fraction for the arithmetic operation:\n");
    scanf("%d %d", &arithmeticOperation1.numerator, &arithmeticOperation1.denominator);

    struct Fraction arithmeticOperation2;
    printf("Enter the second fraction for the arithmetic operation:\n");
    scanf("%d %d", &arithmeticOperation2.numerator, &arithmeticOperation2.denominator);

    char s[30];
    printf("Enter the type of operation you would like to do (addition, subtraction, multiplication, division): ");
    scanf("%s", s);

    struct Fraction resultFromArithmeticOperation;
    resultFromArithmeticOperation = arithmeticOperations(arithmeticOperation1, arithmeticOperation2, s);

    if (resultFromArithmeticOperation.numerator != 0 || resultFromArithmeticOperation.denominator != 0)
    {
        printf("The result from the arithmetic operation is: %d / %d\n",
            resultFromArithmeticOperation.numerator,
            resultFromArithmeticOperation.denominator);
    }

    free(vec);

    return 0;
}