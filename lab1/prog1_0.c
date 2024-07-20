#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    int x;
    FILE *fp;
    fp = fopen("array.txt", "r");
    if (fp == NULL)
    {
        printf("Error: file not found\n");
    }
    for (int i = 0; i < 7; i++)
    {
        fscanf(fp, "%d", &x);
        printf("%d\n", x);
    }
    return 0;
}