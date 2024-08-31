#include <stdio.h>

struct ITEM
{
    int item_id;
    double item_profit;
    double item_weight;
    double profit_weight_ratio;
};

void swap(struct ITEM *a, struct ITEM *b)
{
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct ITEM arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(struct ITEM arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

double fractionalKnapsack(struct ITEM items[], int n, double knapsack_capacity)
{
    heapSort(items, n);

    double max_profit = 0.0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (knapsack_capacity == 0)
            break;

        if (items[i].item_weight <= knapsack_capacity)
        {
            knapsack_capacity -= items[i].item_weight;
            max_profit += items[i].item_profit;
            printf("Item No %d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, 1.0);
        }
        else
        {
            double fraction = knapsack_capacity / items[i].item_weight;
            max_profit += items[i].item_profit * fraction;
            printf("Item No %d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            knapsack_capacity = 0;
        }
    }

    return max_profit;
}

int main()
{
    int n;
    double capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    for (int i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%lf %lf", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%lf", &capacity);

    double max_profit = fractionalKnapsack(items, n, capacity);

    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}
