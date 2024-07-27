/*
WAP in c to sort n no of elemrnts using insertion sort and read and write from file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readFile(int **arr, int *size)
{
    int i;
    FILE *fp;
    fp = fopen("progI2_3.txt", "r");
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

void insertionSort(int *arr, int size)
{
    int i, j, key;
    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int *arr;
    int size;
    readFile(&arr, &size);
    insertionSort(arr, size);
    FILE *fp;
    fp = fopen("progO2_3.txt", "w");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%d\n", arr[i]);
    }
    printf("Data written to file\n");
    fclose(fp);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", cpu_time_used);
    return 0;
}