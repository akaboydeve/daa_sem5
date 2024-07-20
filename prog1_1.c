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
    printf("Size: %d\n", *size);
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
        printf("%d\n", arr[i]);
    }
}

void bubbleSort(int *arr, int size)
{
    int i, j, temp;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int *arr;
    int size;
    readFile(&arr, &size);
    bubbleSort(arr, size);
    printf("Second largest element: %d\n", arr[size - 2]);
    printf("Second smallest element: %d\n", arr[1]);
    return 0;
}
