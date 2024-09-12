#include <stdio.h>

void bbsort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                 arr[j] =  arr[j+1];
                 arr[j+1] = temp;
            }
        }
    }

}

int main()
{
    int arr[] = {5 , 4, 3, 2, 6, 4, -123, 4,5, 3, 444444444, 434};
    int size_of_arr = sizeof(arr) / sizeof(int);
    bbsort(arr, size_of_arr);
    for (int i = 0; i < size_of_arr; i++)
    {
        printf("%i ", arr[i]);
    }

    return 0;
}