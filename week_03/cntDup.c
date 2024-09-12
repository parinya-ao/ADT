#pragma optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>

#define size 1000 

int i = 0, j = 0;

int main()
{
    int **a = NULL;
    a = (int **)malloc(sizeof(int *) * size);
    for (i = 0; i < size; i++)
    {
        a[i] = (int *)malloc(sizeof(int) * 2);
        a[i][0] = i;
        a[i][1] = 0;
    }

    int n;
    scanf("%i", &n);
    int arr[n];
    for (i = 0; i < n; i++)
    {
        scanf("%i", &arr[i]);
        a[arr[i]][1]++;
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%i %i \n", a[i][0], a[i][1]);
    }


    int max = -1;
    for (i = 0; i < size; i++)
    {
        if (a[i][1] >= max)
        {
            max = a[i][1];
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (a[i][1] == max)
        {
            printf("%i ", a[i][0]);
        }
    }

    return 0;
}