/*
WAP to read a convert first n decimal number to binary and write the binary number to a file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readFile(int **arr, int *size)
{
    int i;
    FILE *fp;
    fp = fopen("progI2_2.txt", "r");
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

char *convertToBinary(int n)
{
    char *binary = (char *)malloc(32 * sizeof(char));
    int i = 0;
    while (n > 0)
    {
        binary[i] = n % 2 + '0';
        n = n / 2;
        i++;
    }
    binary[i] = '\0';
    return binary;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int *arr;
    int size;
    readFile(&arr, &size);
    FILE *fp;
    fp = fopen("progO2_2.txt", "w");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        char *binary = convertToBinary(arr[i]);
        printf("%s\n", binary);
        fprintf(fp, "%s\n", binary);
        free(binary);
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time: %f\n", cpu_time_used);
    return 0;
}