/*Wap to find max and min using divident and conquer approach*/

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

void findMaxMin(int arr[], int low, int high, int *max, int *min)
{
    if (low == high)
    {
        *max = *min = arr[low];
        return;
    }

    if (low + 1 < high)
    {
        if (arr[low] > arr[high])
        {
            *max = arr[low];
            *min = arr[high];
        }
        else
        {
            *max = arr[high];
            *min = arr[low];
        }
        return;
    }

    int mid = (low + high) / 2;
    int max1, min1;

    findMaxMin(arr, low, mid, max, min);

    findMaxMin(arr, mid + 1, high, &max1, &min1);
    if (*max < max1)
    {
        *max = max1;
    }
    if (*min > min1)
    {
        *min = min1;
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int *arr;
    readFile("prog5_1.txt", arr, n);
    int max, min;
    double start, end;
    start = clock();
    findMaxMin(arr, 0, n - 1, &max, &min);
    end = clock();
    printf("Max: %d\nMin: %d\n", max, min);
    printf("Time taken: %f\n", (end - start) / CLOCKS_PER_SEC);
    writeFile("progO5_1.txt", arr, n);
    return 0;
}