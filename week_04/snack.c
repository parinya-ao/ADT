// #pragma optimize("Ofast")
#include <stdio.h>

int m = 0, v= 0;

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

int main()
{
    scanf("%i", &m);
    int arr[m];

    for (int i = 0; i < m; i++)
    {
        scanf("%i", &arr[i]);
    }
    scanf("%i", &v);

    //
    int dp[v+1];
    dp[0] = 0;
    for (int i =1 ; i<= v; i++)
    {
        dp[i] = 1e7;
    }

    for (int i = 1; i <= v; i++) 
    {
        for (int j = 0; j < m; j++)
        {
            if (i - arr[j] >= 0)
            {
                dp[i] = min(dp[i], 1+dp[i - arr[j]]);
            }
        }
    }
    if (dp[v] == 1e7)
    {
        for (int i = v; i >= 0; i--)
        {
            if (dp[i] != 1e7)
            {
                printf("%i", dp[i]);
                return 0;
            }
        }
    }
    printf("%i", dp[v]);


    return 0;
}