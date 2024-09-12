#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n, m, x, y, d;

void showtable(int table[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%i ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool top(int x, int y, int n)
{
    if (y >= 0 && y < m)
    {
        return true;
    }
    return false;
}

bool side(int x, int y, int n)
{
    if (x >= 0 && x < n)
    {
        return true;
    }
    return false;
}

int main()
{
    scanf("%i %i %i %i %i", &n, &m, &y, &x, &d);
    int table[m][n];
    memset(table, 0, sizeof(int) *m *n);
    int start_x = x;
    int start_y = y;

    if (d == 0 || d == 4)
    {
        printf("%i", m);
        return 0;
    }
    if (d == 2 || d == 6)
    {
        printf("%i", n);
        return 0;
    }

    int count = 3;

    while (count)
    {
        if (start_x == x && start_y == y)
        {
            --count;
        }
        
        
    }

    showtable(table);

    return 0;
}