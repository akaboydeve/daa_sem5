/*
Write a menu driven program to sort a list of elements in ascending order using Quick Sort technique.
Each choice for the input data has its own disc file.
A separate output file can be used for sorted elements.
After sorting display the content of the output file along with number of comparisons.
Based on the partitioning position for each recursive call,
conclude the input scenario is either best-case partitioning or worst-case partitioning.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readFile(int **arr, int *size, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }
    *size = 0;
    int temp;
    while (fscanf(fp, "%d", &temp) != EOF)
    {
        (*size)++;
    }
    rewind(fp);
    *arr = (int *)malloc((*size) * sizeof(int));
    for (int i = 0; i < *size; i++)
    {
        fscanf(fp, "%d", (*arr) + i);
    }
    fclose(fp);
}

void writeFile(int *arr, int size, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partition(int *arr, int low, int high, int *comparison, int *scenario)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        (*comparison)++;
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    int leftSize = i - low + 1;
    int rightSize = high - (i + 1);

    // Determine the scenario: Best-case or Worst-case
    if (leftSize == 0 || rightSize == 0)
    {
        *scenario = 0; // Worst-case
    }
    else if (abs(leftSize - rightSize) <= 1)
    {
        *scenario = 1; // Best-case
    }
    else
    {
        *scenario = -1; // Neither best nor worst
    }

    return i + 1;
}

void quickSort(int *arr, int low, int high, int *comparison, int *scenario)
{
    if (low < high)
    {
        int sc;
        int pi = partition(arr, low, high, comparison, &sc);
        if (*scenario != 0 && *scenario != 1)
        {
            *scenario = sc;
        }
        quickSort(arr, low, pi - 1, comparison, scenario);
        quickSort(arr, pi + 1, high, comparison, scenario);
    }
}

int main()
{
    int *arr;
    int size, ch = 5, comparison = 0, scenario = -1;
    char filename[100];
    clock_t start, end;
    double cpu_time_used;

    printf("MAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
    printf("Enter option: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        strcpy(filename, "inAsce.dat");
        readFile(&arr, &size, filename);
        printf("Before Sorting: \n");
        printArray(arr, size);
        start = clock();
        quickSort(arr, 0, size - 1, &comparison, &scenario);
        end = clock();
        writeFile(arr, size, "outQuickAsce.dat");
        printf("After Sorting: \n");
        printArray(arr, size);
        break;

    case 2:
        strcpy(filename, "inDesc.dat");
        readFile(&arr, &size, filename);
        printf("Before Sorting: \n");
        printArray(arr, size);
        start = clock();
        quickSort(arr, 0, size - 1, &comparison, &scenario);
        end = clock();
        writeFile(arr, size, "outQuickDesc.dat");
        printf("After Sorting: \n");
        printArray(arr, size);
        break;

    case 3:
        strcpy(filename, "inRand.dat");
        readFile(&arr, &size, filename);
        printf("Before Sorting: \n");
        printArray(arr, size);
        start = clock();
        quickSort(arr, 0, size - 1, &comparison, &scenario);
        end = clock();
        writeFile(arr, size, "outQuickRand.dat");
        printf("After Sorting: \n");
        printArray(arr, size);
        break;

    default:
        printf("ERROR: Invalid choice\n");
        return 1;
    }

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1e6; // time in microseconds
    printf("Number of Comparisons: %d\n", comparison);
    printf("Execution time: %f microseconds\n", cpu_time_used);

    if (scenario == 1)
    {
        printf("Scenario: Best-case partitioning\n");
    }
    else if (scenario == 0)
    {
        printf("Scenario: Worst-case partitioning\n");
    }
    else
    {
        printf("Scenario: Neither best-case nor worst-case partitioning\n");
    }

    free(arr);
    return 0;
}
