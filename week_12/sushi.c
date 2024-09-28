#include <stdio.h>
#include <stdlib.h>

void longestIncreasingSubsequence(double *weights, int *prices, int n)
{
    int *predecessors = (int *)malloc(n * sizeof(int));
    int *lisEnd = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++)
        lisEnd[i] = -1;
    long length = 0;

    for (long i = 0; i < n; i++)
    {
        long low = 1, high = length + 1;

        while (low < high)
        {
            long mid = low + (high - low) / 2;
            if (weights[lisEnd[mid]] > weights[i])
            {
                high = mid;
            }
            else
            {
                low = mid + 1;
            }
        }

        long lisLength = low;
        predecessors[i] = lisEnd[lisLength - 1];
        lisEnd[lisLength] = i;

        if (lisLength > length)
        {
            length = lisLength;
        }
    }

    int *resultSequence = (int *)malloc(length * sizeof(int));
    long k = lisEnd[length];

    for (long j = length - 1; j >= 0; j--)
    {
        resultSequence[j] = k;
        k = predecessors[k];
    }

    int *binaryResult = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
        binaryResult[j] = 0;
    }
    int totalPrice = 0;
    for (int j = 0; j < length; j++)
    {
        binaryResult[resultSequence[j]] = 1;
        totalPrice += prices[resultSequence[j]];
    }

    for (int j = 0; j < n; j++)
    {
        printf("%d ", binaryResult[j]);
    }
    printf("\n");

    printf("%d\n", totalPrice);

    free(predecessors);
    free(lisEnd);
    free(resultSequence);
    free(binaryResult);
}

int main()
{
    int n;
    scanf("%d", &n);
    double *weights = (double *)malloc(n * sizeof(double));
    int *prices = (int *)malloc(n * sizeof(int));

    int priceInput, weightInput;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &priceInput, &weightInput);
        weights[i] = (double)weightInput / (double)priceInput;
        prices[i] = priceInput;
    }

    longestIncreasingSubsequence(weights, prices, n);

    free(weights);
    free(prices);
    return 0;
}
