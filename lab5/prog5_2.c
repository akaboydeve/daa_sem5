// search an element in an array using binary search technique and find out all different types of complexity
#include <stdio.h>

int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
        {
            return mid; // Element found
        }

        if (arr[mid] < target)
        {
            low = mid + 1; // Search right half
        }
        else
        {
            high = mid - 1; // Searc left half
        }
    }

    return -1; // Element not found
}

int main()
{
    int arr[] = {2, 4, 6, 8, 10, 12, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    int result = binarySearch(arr, n, target);

    if (result != -1)
    {
        printf("Element found at index %d\n", result);
    }
    else
    {
        printf("Element not found\n");
    }

    return 0;
}