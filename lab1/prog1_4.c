#include <stdio.h>
#include <stdlib.h>

void readFile(int **arr, int size)
{
    int i;
    FILE *fp;
    fp = fopen("prog1_4.txt", "r");
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

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}
void exchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void rotate_right(int *arr, int p)
{
    for (int i = 0; i < p; i++)
    {
        exchange(&arr[p - 1], &arr[i]);
    }
}

int main()
{
    int *arr;
    int size, p;
    printf("Enter Size: ");
    scanf("%d", &size);
    readFile(&arr, size);
    printf("Enter rotate position: ");
    scanf("%d", &p);
    printf("Before ROTATE: \t");
    printArray(arr, size);
    rotate_right(arr, p);
    printf("After ROTATE: \t");
    printArray(arr, size);
    return 0;
}
