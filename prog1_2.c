#include <stdio.h>
#include <stdlib.h>

void readFile(int **arr, int *size)
{
    int i;
    FILE *fp;
    fp = fopen("prog1_1.txt", "r");
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

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void prefixSum(int *arr, int size, int **arr2)
{
    *arr2 = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        (*arr2)[i] = 0;
    }
    int x = 0;
    for (int i = 0; i < size; i++)
    {

        (*arr2)[i] = arr[i] + x;
        x = (*arr2)[i];
    }
}

int main()
{
    int *arr, *arr2;
    int size;
    readFile(&arr, &size);
    prefixSum(arr, size, &arr2);
    printArray(arr, size);
    printArray(arr2, size);
    return 0;
}
