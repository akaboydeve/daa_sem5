/*Wap to search an element in an array using binary search technique*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readFile(char *filename, int *arr, int n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

void writeFile(char *filename, int *arr, int n)
{
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

int binarySearch(int *arr, int low, int high, int key)
{
    if (low > high)
    {
        return -1;
    }

    int mid = (low + high) / 2;

    if (arr[mid] == key)
    {
        return mid;
    }
    else if (arr[mid] < key)
    {
        return binarySearch(arr, mid + 1, high, key);
    }
    else
    {
        return binarySearch(arr, low, mid - 1, key);
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    readFile("prog5_2.txt", arr, n);

    int key;
    printf("Enter the element to search: ");
    scanf("%d", &key);

    long start = clock();
    int index = binarySearch(arr, 0, n - 1, key);
    long end = clock();

    printf("Time taken: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    if (index == -1)
    {
        printf("Element not found\n");
    }
    else
    {
        printf("Element found at index %d\n", index);
    }

    return 0;
}
