#pragma optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void findSD(const int *nums, const int n, double *sigma)
{
    double mean = 0;
    for (int i = 0; i < n; i++)
    {
        mean += *(nums+i);
    }
    mean /= n;
    for (int i = 0; i < n; i++)
    {
        *sigma += pow(*(nums+i), 2);
    }
    *sigma /= n;
    *sigma -= pow(mean, 2);
    *sigma = sqrt(*sigma);
}

int n = 0, i = 0;
double sigma = 0;
int *nums = NULL;

int main()
{
    scanf("%i", &n);
    nums = (int*) malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
    {
        scanf("%i", nums+i);
    }
    double *ptr = &sigma;
    findSD(nums, n, ptr);
    printf("%.2f", sigma);

    return 0;
}