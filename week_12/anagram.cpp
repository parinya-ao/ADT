#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 51
#define MAX_VECS 9999

typedef struct
{
    char key[MAX_STR_LEN];
    // แก้ mav_vec ขนาดของ hash linear ให้เป็น dynamic โดยใช้ malloc
    char **values;
    int count;
} MapEntry;

MapEntry map[MAX_VECS];
int mapSize = 0;

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

void sortString(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (str[i] > str[j])
            {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main()
{
    int n, a;
    scanf("%d %d", &n, &a);
    char input[MAX_STR_LEN];
    char copy[MAX_STR_LEN];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", input);
        strcpy(copy, input);
        sortString(copy);

        int index = findEntry(copy);
        if (index != -1)
        {
            strcpy(map[index].values[map[index].count++], input);
        }
        else
        {
            strcpy(map[mapSize].key, copy);
            strcpy(map[mapSize].values[0], input);
            map[mapSize].count = 1;
            mapSize++;
        }
    }

    char com[MAX_STR_LEN];
    for (int i = 0; i < a; ++i)
    {
        scanf("%s", com);
        sortString(com);

        int index = findEntry(com);
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

    return 0;
}
