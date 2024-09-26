#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMB 10000
#define MAX_NUM 10000

typedef struct
{
    int data[MAX_COMB][3];
    int size;
} Set;

void initSet(Set *set)
{
    set->size = 0;
}

int contains(Set *set, int *comb)
{
    for (int i = 0; i < set->size; i++)
    {
        if (set->data[i][0] == comb[0] && set->data[i][1] == comb[1] && set->data[i][2] == comb[2])
        {
            return 1;
        }
    }
    return 0;
}

void addCombination(Set *set, int *comb)
{
    if (!contains(set, comb))
    {
        memcpy(set->data[set->size], comb, 3 * sizeof(int));
        set->size++;
    }
}

void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

void combination(Set *result, int *num, int start, int n, int *current_comb, int depth)
{
    if (depth == 3)
    {
        addCombination(result, current_comb);
        return;
    }

    for (int i = start; i < n; ++i)
    {
        current_comb[depth] = num[i];
        combination(result, num, i + 1, n, current_comb, depth + 1);
    }
}

int main()
{
    int n, target;
    int vec[MAX_NUM];

    scanf("%d %d", &n, &target);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &vec[i]);
    }

    quickSort(vec, 0, n - 1);

    Set result;
    initSet(&result);
    int comb[3] = {-1, -1, -1};

    combination(&result, vec, 0, n, comb, 0);

    for (int i = 0; i < result.size; i++)
    {
        int sum = result.data[i][0] + result.data[i][1] + result.data[i][2];
        if (sum == target)
        {
            printf("%d %d %d\n", result.data[i][0], result.data[i][1], result.data[i][2]);
        }
    }

    return 0;
}
