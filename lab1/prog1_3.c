#include <stdio.h>
#include <stdlib.h>

void readFile(int **arr, int size)
{
    int i;
    FILE *fp;
    fp = fopen("prog1_3.txt", "r");
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

void findDup(int *arr, int size)
{
    int count = 0, max = 0;
    int *arr2 = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i != j)
            {
                if (arr[i] == arr[j])
                {
                    count++;
                    arr2[i] = count;
                }
            }
        }
        max = (count > max) ? count : max;
    }
    printf("Total no of duplicate vaules %d\n", count);
    for (int i = 0; i < size; i++)
    {
        if (arr2[i] == max)
        {
            printf("The most repeating element in the array = %d\n", arr[i]);
            break;
        }
    }
}

int main()
{
    int *arr;
    int size;
    printf("How many numbers you want to read from file : \n");
    scanf("%d", &size);
    readFile(&arr, size);
    printArray(arr, size);
    findDup(arr, size);
    return 0;
}
