/*Write a program to find the maximum profit nearest to but not exceeding the given knapsack capacity using the Fractional Knapsack algorithm.
Notes# Declare a structure ITEM having data members item_id, item_profit, item_weight and profit_weight_ratio.
 Apply heap sort technique to sort the items in non-increasing order, according to their profit /weight.
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
} ITEM;
void swap(ITEM *a, ITEM *b)
{
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(ITEM arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
    {
        largest = left;
    }
    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(ITEM arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
void fractionalKnapsack(ITEM items[], int n, float capacity)
{
    float total_profit = 0.0;
    printf("\nItem No  Profit   Weight  Amount to be taken\n");
    for (int i = 0; i < n; i++)
    {
        if (capacity <= 0)
        {
            break;
        }
        if (items[i].item_weight <= capacity)
        {
            capacity -= items[i].item_weight;
            total_profit += items[i].item_profit;
            printf("%-8d  %-8.2f  %-8.2f  %-8.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, 1.0);
        }
        else
        {
            float fraction = capacity / items[i].item_weight;
            total_profit += items[i].item_profit * fraction;
            printf("%-8d  %-8.2f  %-8.2f  %-8.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            capacity = 0;
        }
    }
    printf("Maximum profit: %.6f\n", total_profit);
}
int main()
{
    int n;
    float capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    ITEM items[n];
    for (int i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);
    heapSort(items, n);
    fractionalKnapsack(items, n, capacity);
    return 0;
}