#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma GCC optimize("Ofast")

// ตามโจทย์
#define MAX_TREE_HEIGHT 100
#define MAX_WORD_LENGTH 16

// ตาม slide
typedef struct node
{
    char word[MAX_WORD_LENGTH];
    int frequency;
    struct node *left, *right;
} node_t;

// ข้อ 1 รับจบ
typedef struct min_heap
{
    node_t **data;
    int last_index;
} min_heap_t;

node_t *create_node(char *word, int frequency)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    strcpy(new_node->word, word);
    new_node->frequency = frequency;
    new_node->left = new_node->right = NULL;
    return new_node;
}

min_heap_t *init_heap(int capacity)
{
    min_heap_t *heap = (min_heap_t *)malloc(sizeof(min_heap_t));
    heap->data = (node_t **)malloc((capacity + 1) * sizeof(node_t *));
    heap->last_index = 0;
    return heap;
}

void swap_nodes(node_t **a, node_t **b)
{
    node_t *temp = *a;
    *a = *b;
    *b = temp;
}

void balance(min_heap_t *heap, int index)
{
    int left = index << 1;
    int right = (index << 1) + 1;
    int smallest = index;

    if (left <= heap->last_index && heap->data[left]->frequency < heap->data[smallest]->frequency)
    {
        smallest = left;
    }
    if (right <= heap->last_index && heap->data[right]->frequency < heap->data[smallest]->frequency)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        swap_nodes(&heap->data[smallest], &heap->data[index]);
        balance(heap, smallest);
    }
}

min_heap_t *insert(min_heap_t *heap, node_t *node)
{
    heap->last_index++;
    heap->data[heap->last_index] = node;

    int index = heap->last_index;
    while (index > 1)
    {
        int parent_index = index >> 1;
        if (heap->data[parent_index]->frequency > heap->data[index]->frequency)
        {
            swap_nodes(&heap->data[parent_index], &heap->data[index]);
            index = parent_index;
        }
        else
        {
            break;
        }
    }
    return heap;
}

// ข้อ 3
node_t *extract_min(min_heap_t *heap)
{
    if (heap->last_index == 0)
    {
        return NULL;
    }
    node_t *min_node = heap->data[1];
    heap->data[1] = heap->data[heap->last_index];
    heap->last_index--;
    balance(heap, 1);
    return min_node;
}

node_t *huffman(char words[][MAX_WORD_LENGTH], int frequencies[], int n)
{
    min_heap_t *min_heap = init_heap(n);
    for (int i = 0; i < n; i++)
    {
        insert(min_heap, create_node(words[i], frequencies[i]));
    }

    while (min_heap->last_index != 1)
    {
        node_t *left = extract_min(min_heap);
        node_t *right = extract_min(min_heap);
        node_t *top = create_node("", left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insert(min_heap, top);
    }

    return extract_min(min_heap);
}

void generate_huffman_codes(node_t *root, char *code, int depth)
{
    if (root->left != NULL)
    {
        code[depth] = '0';
        generate_huffman_codes(root->left, code, depth + 1);
    }
    if (root->right != NULL)
    {
        code[depth] = '1';
        generate_huffman_codes(root->right, code, depth + 1);
    }
    if (root->left == NULL && root->right == NULL)
    {
        code[depth] = '\0';
        printf("%s: %s\n", root->word, code);
    }
}

void free_heap(min_heap_t *heap)
{
    if (heap != NULL)
    {
        free(heap->data);
        free(heap);
    }
}

int main(void)
{
    int n;
    scanf("%d", &n);
    char words[n][MAX_WORD_LENGTH];
    int frequencies[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", words[i], &frequencies[i]);
    }

    node_t *root = huffman(words, frequencies, n);
    char code[MAX_TREE_HEIGHT];
    generate_huffman_codes(root, code, 0);

    free_heap(root);
    return 0;
}
