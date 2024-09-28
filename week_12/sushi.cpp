#include <bits/stdc++.h>
using namespace std;

void longestIncreasingSubsequence(double *weights, int *prices, int n);

int main()
{
    int n;
    cin >> n;
    vector<double> weights(n);
    vector<int> prices(n);

    int priceInput, weightInput;
    for (int i = 0; i < n; i++)
    {
        cin >> priceInput >> weightInput;
        weights[i] = (double)weightInput / (double)priceInput;
        prices[i] = priceInput;
    }

    longestIncreasingSubsequence(weights.data(), prices.data(), n);

    return 0;
}

void longestIncreasingSubsequence(double *weights, int *prices, int n)
{
    vector<int> predecessors(n), lisEnd(n + 1, -1);
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

    vector<int> resultSequence(length);
    long k = lisEnd[length];

    for (long j = length - 1; j >= 0; j--)
    {
        resultSequence[j] = k;
        k = predecessors[k];
    }

    vector<int> binaryResult(n, 0);
    int totalPrice = 0; // เปลี่ยนจาก unsigned long เป็น int
    for (unsigned long j = 0; j < length; j++)
    {
        binaryResult[resultSequence[j]] = 1;
        totalPrice += prices[resultSequence[j]];
    }

    for (unsigned long j = 0; j < n; j++)
    {
        cout << binaryResult[j] << " ";
    }
    cout << endl;

    cout << totalPrice << endl;
}
