/*Aim of the program: Write a menu driven program to sort list of array elements using
Insertion Sort technique and calculate the execution time only to sort the elements.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void readFile(int **arr, int size, char *filename)
{
    int i;
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }
    *arr = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
    {
        fscanf(fp, "%d", (*arr) + i);
    }
    fclose(fp);
}

void writeFile(int *arr, int size, char *filename)
{
    int i;
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }
    for (i = 0; i < size; i++)
    {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);
}

void merge(int *arr, int l, int m, int r, int *comparison)
{
    int i = l;
    int j = m + 1;
    while (i <= m && j <= r)
    {
        (*comparison)++;
        if (arr[i] <= arr[j])
        {
            i++;
        }
        else
        {
            int value = arr[j];
            int index = j;

            while (index != i)
            {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[i] = value;

            i++;
            m++;
            j++;
        }
    }
}

void mergeDesc(int *arr, int l, int m, int r, int *comparison)
{
    int i = l;
    int j = m + 1;
    while (i <= m && j <= r)
    {
        (*comparison)++;
        if (arr[i] >= arr[j])
        {
            i++;
        }
        else
        {
            int value = arr[j];
            int index = j;

            while (index != i)
            {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[i] = value;

            i++;
            m++;
            j++;
        }
    }
}

void mergeSort(int *arr, int l, int r, int *comparison)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparison);
        mergeSort(arr, m + 1, r, comparison);
        merge(arr, l, m, r, comparison);
    }
}

void mergeSortDesc(int *arr, int l, int r, int *comparison)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortDesc(arr, l, m, comparison);
        mergeSortDesc(arr, m + 1, r, comparison);
        mergeDesc(arr, l, m, r, comparison);
    }
}

void randomMerge(int *arr, int l, int m, int r, int *comparison)
{
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r)
    {
        (*comparison)++;
        if (rand() % 2 == 0)
        {
            arr[k] = arr[i];
            i++;
        }
        else
        {
            arr[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= m)
    {
        arr[k] = arr[i];
        i++;
        k++;
    }

    while (j <= r)
    {
        arr[k] = arr[j];
        j++;
        k++;
    }
}

void mergeSortRand(int *arr, int l, int r, int *comparison)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortRand(arr, l, m, comparison);
        mergeSortRand(arr, m + 1, r, comparison);
        randomMerge(arr, l, m, r, comparison);
    }
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main()
{
    int *arr;
    int size, ch = 5, comparison = 0;
    char filename[100];
    clock_t start, end;
    double cpu_time_used;
    printf("MAIN MENU (INSERTION SORT)\n");
    printf("1. Random Data Provide to the function\n");
    printf("2. Ascending Data Provide to the function\n");
    printf("3. Descending Data Provide to the function\n");
    printf("4. ERROR (EXIT)\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        printf("Enter Size: ");
        scanf("%d", &size);
        strcpy(filename, "inAsce.txt");
        readFile(&arr, size, filename);
        printf("Before SORT: \t");
        printArray(arr, size);
        start = clock();
        mergeSortRand(arr, 0, size - 1, &comparison);
        end = clock();
        printf("After SORT: \t");
        printArray(arr, size);
        writeFile(arr, size, "outMergeAsce.txt");
        printf("Total comparison: %d\n", comparison);
        break;

    case 2:
        printf("Enter Size: ");
        scanf("%d", &size);
        strcpy(filename, "inAsce.txt");
        readFile(&arr, size, filename);
        printf("Before SORT: \t");
        printArray(arr, size);
        start = clock();
        mergeSort(arr, 0, size - 1, &comparison);
        end = clock();
        printf("After SORT: \t");
        printArray(arr, size);
        writeFile(arr, size, "outMergeAsce.txt");
        printf("Total comparison: %d\n", comparison);
        break;

    case 3:
        printf("Enter Size: ");
        scanf("%d", &size);
        strcpy(filename, "inDesc.txt");
        readFile(&arr, size, filename);
        printf("Before SORT: \t");
        printArray(arr, size);
        start = clock();
        mergeSortDesc(arr, 0, size - 1, &comparison);
        end = clock();
        printf("After SORT: \t");
        printArray(arr, size);
        writeFile(arr, size, "outMergeDesc.txt");
        printf("Total comparison: %d\n", comparison);
        break;

    default:
        printf("ERROR: Invalid choice\n");
        return 1;
    }
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1e9;
    printf("Execution time: %f nanoseconds\n", cpu_time_used);
    free(arr);
    return 0;
}