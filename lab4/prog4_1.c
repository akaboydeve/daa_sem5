/* Write a menu driven program to sort list of array elements using Merge Sort technique and calculate the execution time only to sort the elements.  Count the number of comparisons.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readFile(char *filename, int *arr, int *n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        exit(1);
    }
    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++)
    {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}
void writeFile(char *filename, int *arr, int n)
{
    FILE *file = fopen(filename, "w");
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}
void merge(int *arr, int l, int m, int r, int *comp)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        (*comp)++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int *arr, int l, int r, int *comp)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comp);
        mergeSort(arr, m + 1, r, comp);
        merge(arr, l, m, r, comp);
    }
}

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int option;
    double start, end;
    int n = 500, comp = 0;
    int arr[500];

    while (1)
    {
        printf("\nMAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            comp = 0;
            readFile("inAsce.dat", arr, &n);
            printf("Unsorted array: ");
            printArray(arr, n);
            start = clock();
            mergeSort(arr, 0, n - 1, &comp);
            end = clock();
            writeFile("outMergeAsce.dat", arr, n);
            printf("Sorted array: ");
            printArray(arr, n);
            printf("\nNumber of comparisons: %d\n", comp);
            printf("Time taken in ns: %f\n", (end - start) * 1000000 / CLOCKS_PER_SEC);
        case 2:
            comp = 0;
            readFile("inDesc.dat", arr, &n);
            printf("Unsorted array: ");
            printArray(arr, n);
            start = clock();
            mergeSort(arr, 0, n - 1, &comp);
            end = clock();
            writeFile("outMergeDesc.dat", arr, n);
            printf("Sorted array: ");
            printArray(arr, n);
            printf("\nNumber of comparisons: %d\n", comp);
            printf("Time taken in ns: %f\n", (end - start) * 1000000 / CLOCKS_PER_SEC);
            break;
        case 3:
            comp = 0;
            readFile("inRand.dat", arr, &n);
            printf("Unsorted array: ");
            printArray(arr, n);
            start = clock();
            mergeSort(arr, 0, n - 1, &comp);
            end = clock();
            writeFile("outMergeRand.dat", arr, n);
            printf("Sorted array: ");
            printArray(arr, n);
            printf("\nNumber of comparisons: %d\n", comp);
            printf("Time taken in ns: %f\n", (end - start) * 1000000 / CLOCKS_PER_SEC);
            break;
        case 4:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    return 0;
}