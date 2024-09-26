#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<float> numbers;
    float num;

    while (n--)
    {
        cin >> num;
        numbers.push_back(num);
        sort(numbers.begin(), numbers.end());

        double median;
        int size = numbers.size();
        if (size % 2 == 0)
        {
            median = (numbers[size / 2 - 1] + numbers[size / 2]) / 2.0;
        }
        else
        {
            median = numbers[size / 2];
        }

        printf("%.1f\n", median);
    }

    return 0;
}
