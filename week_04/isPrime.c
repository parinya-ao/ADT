// O(sqrt(n)
#pragma optimize("Ofast")
#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    scanf("%i", &n);

    for (int i = 2; i <= (int)sqrt(n); i++)
    {
        if (n % i == 0)
        {
            printf("0");
            return 0;
        }
    }
    printf("1");

    return 0;
}