#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 51
#define MAX_VECS 10000

typedef struct
{
    char key[MAX_STR_LEN];
    char *values[MAX_VECS];
    int count;
} MapEntry;

MapEntry map[MAX_VECS];
int mapSize = 0;

void sortString(char *str)
{
    int count[26] = {0};
    for (int i = 0; str[i]; i++)
    {
        count[str[i] - 'a']++;
    }
    int index = 0;
    for (int i = 0; i < 26; i++)
    {
        while (count[i]--)
        {
            str[index++] = 'a' + i;
        }
    }
    str[index] = '\0';
}

int findEntry(const char *key)
{
    for (int i = 0; i < mapSize; i++)
    {
        if (strcmp(map[i].key, key) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    char input[MAX_STR_LEN];
    char sortedKey[MAX_STR_LEN];

    for (int i = 0; i < m; i++)
    {
        scanf("%s", input);
        strcpy(sortedKey, input);
        sortString(sortedKey);

        int index = findEntry(sortedKey);
        if (index != -1)
        {
            map[index].values[map[index].count] = strdup(input);
            map[index].count++;
        }
        else
        {
            strcpy(map[mapSize].key, sortedKey);
            map[mapSize].values[0] = strdup(input);
            map[mapSize].count = 1;
            mapSize++;
        }
    }

    char query[MAX_STR_LEN];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", query);
        sortString(query);

        int index = findEntry(query);
        if (index != -1)
        {
            for (int j = 0; j < map[index].count; j++)
            {
                printf("%s ", map[index].values[j]);
            }
            printf("\n");
        }
        else
        {
            printf("\n");
        }
    }

    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < map[i].count; j++)
        {
            free(map[i].values[j]);
        }
    }

    return 0;
}
