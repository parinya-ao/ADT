#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int first;
    int *second;
    int second_size;
} Pair;

void merge(Pair *arr, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pair *L = (Pair *)malloc(n1 * sizeof(Pair));
    Pair *R = (Pair *)malloc(n2 * sizeof(Pair));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].first >= R[j].first)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Pair *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    double *wight = (double *)malloc(n * sizeof(double));
    int *price = (int *)malloc(n * sizeof(int));

    int price1, w;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &price1, &w);
        wight[i] = (double)w / (double)price1;
        price[i] = price1;
    }

    Pair *LTS = (Pair *)malloc(n * sizeof(Pair));
    for (int i = 0; i < n; i++)
    {
        LTS[i].first = 1;
        LTS[i].second = (int *)malloc(n * sizeof(int));
        LTS[i].second_size = 0;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        LTS[i].second[LTS[i].second_size++] = i;
        for (int j = 1 + i; j < n; ++j)
        {
            if (wight[i] < wight[j])
            {
                if (LTS[i].first < LTS[j].first + 1)
                {
                    LTS[i].first = 1 + LTS[j].first;
                    for (int k = 0; k < LTS[j].second_size; k++)
                    {
                        LTS[i].second[k] = LTS[j].second[k];
                    }
                    LTS[i].second[LTS[j].second_size] = i;
                    LTS[i].second_size = LTS[j].second_size + 1;
                }
            }
        }
    }

    mergeSort(LTS, 0, n - 1);

    int *ans = (int *)calloc(n, sizeof(int));
    int sum = 0;
    for (int j = 0; j < LTS[0].second_size; j++)
    {
        ans[LTS[0].second[j]] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", ans[i]);
        if (ans[i] == 1)
        {
            sum += price[i];
        }
    }
    printf("\n");
    printf("%d\n", sum);

    free(wight);
    free(price);
    for (int i = 0; i < n; i++)
    {
        free(LTS[i].second);
    }
    free(LTS);
    free(ans);

    return 0;
}
