#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100000

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

void findThreeSum(int *nums, int n, int target)
{
    quickSort(nums, 0, n - 1);

    for (int i = 0; i < n - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = n - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == target)
            {
                printf("%d %d %d\n", nums[i], nums[left], nums[right]);
                while (left < right && nums[left] == nums[left + 1])
                    left++;
                while (left < right && nums[right] == nums[right - 1])
                    right--;
                left++;
                right--;
            }
            else if (sum < target)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
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

    findThreeSum(vec, n, target);

    return 0;
}
