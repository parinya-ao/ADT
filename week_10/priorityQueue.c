#include <stdio.h>
#include <stdlib.h>
#pragma GCC optimize("Ofast")

typedef struct heap
{
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int m)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));

    heap->data = (int *)malloc((m + 1) * sizeof(int));
    heap->last_index = 0;
    return heap;
}

heap_t *insert(heap_t *heap, int target)
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
    return heap;
}

int find_max(heap_t *heap)
{
    if (heap->last_index == 0)
    {
        return -1;
    }
    else
    {
        return heap->data[1];
    }
}

heap_t *delete_max(heap_t *heap)
{
    if (heap->last_index == 0)
    {
        return heap;
    }
    heap->data[1] = heap->data[heap->last_index];
    heap->last_index--;

    int index = 1;
    while (index << 1 <= heap->last_index)
    {
        int left = index << 1;
        int right = index << 1 + 1;
        int temp = left; // กำหนดให้ซ้ายมากกว่าขวา

        if (right <= heap->last_index && heap->data[right] > heap->data[left])
        {
            temp = right;
        }

        // check swap
        if (heap->data[index] < heap->data[temp])
        {
            int hold = heap->data[index];
            heap->data[index] = heap->data[temp];
            heap->data[temp] = hold;
            index = temp;
        }
        else
        {
            break;
        }
    }
    return heap;
}

void free_heap(heap_t *heap)
{
    if (heap != NULL)
    {
        free(heap->data);
        free(heap);
    }
}

void update_key(heap_t *heap, int old_key, int new_key)
{
    int index_oldkey = 1;
    while (index_oldkey <= heap->last_index)
    {
        if (heap->data[index_oldkey] == old_key)
        {
            break;
        }
        index_oldkey++;
    }

    heap->data[index_oldkey] = new_key;
    if (new_key > old_key) // เลื่อนขึ้น
    {
        while (index_oldkey > 1)
        {
            int parent_index = index_oldkey >> 1;
            if (heap->data[parent_index] < heap->data[index_oldkey])
            {
                int temp = heap->data[parent_index];
                heap->data[parent_index] = heap->data[index_oldkey];
                heap->data[index_oldkey] = temp;
                index_oldkey = parent_index;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        while (index_oldkey << 1 <= heap->last_index)
        {
            int left = index_oldkey << 1;
            int right = index_oldkey << 1 + 1;
            int max = left;

            if (left <= heap->last_index && heap->data[left] > heap->data[max])
            {
                max = left;
            }
            if (right <= heap->last_index && heap->data[right] > heap->data[max])
            {
                max = right;
            }

            if (max != index_oldkey)
            {
                int temp = heap->data[index_oldkey];
                heap->data[index_oldkey] = heap->data[max];
                heap->data[max] = temp;
                index_oldkey = max;
            }
            else
            {
                break;
            }
        }
    }
    return;
}

void bfs(heap_t *heap)
{
    for (int i = 1; i <= heap->last_index; i++)
    {
        printf("%i ", heap->data[i]);
    }
    printf("\n");
}

int main(void)
{
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &data);
            insert(max_heap, data);
            break;
        case 2:
            delete_max(max_heap);
            break;
        case 3:
            printf("%d\n", find_max(max_heap));
            // printf("%i", max_heap->last_index);
            break;
        case 4:
            scanf("%d %d", &old_key, &new_key);
            update_key(max_heap, old_key,
                       new_key);
            break;
        case 5:
            bfs(max_heap);
            break;
        }
    }
    free_heap(max_heap);
    return 0;
}