#include <stdio.h>

void recursive(char *string, char *sub, int i, int m, int p, int n)
{
    if (i + p > m)
    {
        for (int a = i; a < m; a++)
        {
            printf("%c", string[i]);
        }
    }
    int cnt = 0;
    for (int a = i; a <= i+n; a++)
    {
        if (string[i] == sub[i])
    }

}

int main()
{
    int m=0, p=0, n=0;
    scanf("%i %i %i", &m, &p, &n);
    char string[m];
    char sub[p];
    scanf("%s", string);
    scanf("%s", sub);

    recursive(string, sub, 0, m, p, n);

    return 0;
}