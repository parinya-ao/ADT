#include <stdio.h>
#include <stdlib.h>
#pragma GCC optimize("Ofast")

typedef struct
{
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int n)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (int *)malloc((n + 1) * sizeof(int));
    heap->last_index = 0;
    return heap;
}

void free_heap(heap_t *heap)
{
    free(heap->data);
    free(heap);
}

void insert_min_heap(heap_t *heap, int target)
{
    heap->last_index++;
    heap->data[heap->last_index] = target;

    int index = heap->last_index;
    while (index > 1)
    {
        int parent_index = index >> 1;
        if (heap->data[parent_index] > heap->data[index])
        {
            int temp = heap->data[parent_index];
            heap->data[parent_index] = heap->data[index];
            heap->data[index] = temp;
            index = parent_index;
        }
        else
        {
            break;
        }
    }
}

void insert_max_heap(heap_t *heap, int target)
{
    heap->last_index++;
    heap->data[heap->last_index] = target;

    int index = heap->last_index;
    while (index > 1)
    {
        int parent_index = index >> 1;
        if (heap->data[parent_index] < heap->data[index])
        {
            int temp = heap->data[parent_index];
            heap->data[parent_index] = heap->data[index];
            heap->data[index] = temp;
            index = parent_index;
        }
        else
        {
            break;
        }
    }
}

int extract_min(heap_t *heap)
{
    if (heap->last_index == 0)
        return -1;

    int min = heap->data[1];
    heap->data[1] = heap->data[heap->last_index];
    heap->last_index--;

    int index = 1;
    while (index * 2 <= heap->last_index)
    {
        int left_child = index * 2;
        int right_child = index * 2 + 1;
        int smallest = index;

        if (left_child <= heap->last_index && heap->data[left_child] < heap->data[smallest])
        {
            smallest = left_child;
        }
        if (right_child <= heap->last_index && heap->data[right_child] < heap->data[smallest])
        {
            smallest = right_child;
        }
        if (smallest != index)
        {
            int temp = heap->data[index];
            heap->data[index] = heap->data[smallest];
            heap->data[smallest] = temp;
            index = smallest;
        }
        else
        {
            break;
        }
    }

    return min;
}

int extract_max(heap_t *heap)
{
    if (heap->last_index == 0)
        return -1;

    int max = heap->data[1];
    heap->data[1] = heap->data[heap->last_index];
    heap->last_index--;

    int index = 1;
    while (index * 2 <= heap->last_index)
    {
        int left_child = index * 2;
        int right_child = index * 2 + 1;
        int largest = index;

        if (left_child <= heap->last_index && heap->data[left_child] > heap->data[largest])
        {
            largest = left_child;
        }
        if (right_child <= heap->last_index && heap->data[right_child] > heap->data[largest])
        {
            largest = right_child;
        }
        if (largest != index)
        {
            int temp = heap->data[index];
            heap->data[index] = heap->data[largest];
            heap->data[largest] = temp;
            index = largest;
        }
        else
        {
            break;
        }
    }

    return max;
}

void balance_heaps(heap_t *min_heap, heap_t *max_heap)
{
    if (max_heap->last_index > min_heap->last_index + 1)
    {
        int root = extract_max(max_heap);
        insert_min_heap(min_heap, root);
    }
    else if (min_heap->last_index > max_heap->last_index)
    {
        int root = extract_min(min_heap);
        insert_max_heap(max_heap, root);
    }
}

int find_max_or_min(heap_t *heap)
{
    if (heap->last_index == 0)
        return -1;
    return heap->data[1];
}

int main()
{
    int n;
    scanf("%i", &n);

    heap_t *min_heap = init_heap(n);
    heap_t *max_heap = init_heap(n);

    int num;
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &num);

        if (max_heap->last_index == 0 || num <= max_heap->data[1])
        {
            insert_max_heap(max_heap, num);
        }
        else
        {
            insert_min_heap(min_heap, num);
        }

        balance_heaps(min_heap, max_heap);

        double median;
        if (max_heap->last_index > min_heap->last_index)
        {
            median = max_heap->data[1];
        }
        else
        {
            median = (max_heap->data[1] + min_heap->data[1]) / 2.0;
        }

        printf("%.1f\n", median);
    }

    free_heap(min_heap);
    free_heap(max_heap);

    return 0;
}
