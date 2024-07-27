/*WAP to find GCD using recurssion read and write from file
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readFile(int **arr, int *size)
{
    int i;
    FILE *fp;
    fp = fopen("progI2_1.txt", "r");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }
    fscanf(fp, "%d", size);
    *arr = (int *)malloc(*size * sizeof(int));
    for (i = 0; i < *size; i++)
    {
        fscanf(fp, "%d", (*arr) + i);
    }
    fclose(fp);
}

void writeFile(int n)
{
    int i;
    FILE *fp;
    fp = fopen("progO2_1.txt", "w");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }
    fprintf(fp, "%d\n", n);
    fclose(fp);
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
}

int recurssiveGCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return recurssiveGCD(b, a % b);
}

int main()
{
    // printf("Hello\n");
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int *arr;
    int size, n = 1;
    readFile(&arr, &size);
    FILE *fp;
    fp = fopen("progO2_1.txt", "w");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }

    while (n < size)
    {
        printf("GCD of %d and %d is %d\n", arr[n], arr[n + 1], recurssiveGCD(arr[n], arr[n + 1]));
        fprintf(fp, "%d\n", recurssiveGCD(arr[n], arr[n + 1]));
        n = n + 2;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time: %f\n", cpu_time_used);
    return 0;
}