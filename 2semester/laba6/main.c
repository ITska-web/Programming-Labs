#include <stdio.h>
#include "sort.h"

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("arr: \n");
    printArray(arr1, n1);

    bubblesort(arr1, n1);

    printf("Bubble Sort: \n");
    printArray(arr1, n1);

    int arr2[] = {10, 7, 8, 9, 1, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("arr: \n");
    printArray(arr2, n2);

    quicksort(arr2, 0, n2 - 1);

    printf("Quick Sort: \n");
    printArray(arr2, n2);

    return 0;
}