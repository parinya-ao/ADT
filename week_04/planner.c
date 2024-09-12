// O(nlog n logm)
#pragma optimize("Ofast")
#include <stdio.h>
#include <stdbool.h>

// O(1)
int min(int n, int m)
{
    if (n < m)
    {
        return n;
    }
    return m;
}

// O(n)
int set_i(int n)
{
    for (int i = n; i>=0; i--)
    {
        if (i >= 0 && (i & (i-1)) == 0)
        {
            return i;
        }
    }
}

int find(int m, int n)
{
    // basecase 
    if (n == 1)
    {
        return m;
    }
    if (m == 1)
    {
        return n;
    }
    if (n <= 0 || m <= 0)
    {
        return 0;
    }
    //i คือ 0จำนวนยกกำลังที่ใกล้ ตัวนั้นแต่น้อยกว่า
    int i = 1;
    int mini = min(n, m);
    i = set_i(mini);

    return 1 + find(n-i, m) + find(i, m-i);
}

int main()
{
    int n, m;
    scanf("%i %i", &m, &n);

    printf("%i", find(m, n));
    return 0;
}