#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t bst_t;

void print_tree_2(bst_t *t, int depth, char pre)
{
    if (t == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%c%d\n", pre, t->data);
    print_tree_2(t->left, depth + 1, 'L');
    print_tree_2(t->right, depth + 1, 'R');
}

void print_tree(bst_t *t)
{
    print_tree_2(t, 0, 'r');
}

node_t *createNode(int data)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int solve(bst_t *t, int k, int *cnt)
{
    if (t == NULL)
        return -1;
    int left = solve(t->left, k, cnt);
    if (left != -1)
        return left;
    (*cnt)++;
    if (*cnt == k)
        return t->data;
    return solve(t->right, k, cnt);
}

int find_k_th(bst_t *t, int index)
{
    int cnt = 0;
    return solve(t, index, &cnt);
}

bool find(bst_t *t, int target)
{
    if (t == NULL)
        return false;
    if (t->data == target)
        return true;
    return target < t->data ? find(t->left, target) : find(t->right, target);
}

int find_min(bst_t *t)
{
    if (t == NULL)
        return -1;
    while (t->left != NULL)
        t = t->left;
    return t->data;
}

int find_max(bst_t *t)
{
    if (t == NULL)
        return -1;
    while (t->right != NULL)
        t = t->right;
    return t->data;
}

bst_t *insert(bst_t *t, int target)
{
    if (t == NULL)
        return createNode(target);
    if (target < t->data)
        t->left = insert(t->left, target);
    else if (target > t->data)
        t->right = insert(t->right, target);
    return t;
}

bst_t *delete(bst_t *t, int target)
{
    if (t == NULL)
        return t;
    if (target < t->data)
        t->left = delete (t->left, target);
    else if (target > t->data)
        t->right = delete (t->right, target);
    else
    {
        if (t->left == NULL)
        {
            node_t *temp = t->right;
            free(t);
            return temp;
        }
        else if (t->right == NULL)
        {
            node_t *temp = t->left;
            free(t);
            return temp;
        }
        int min = find_min(t->right);
        t->data = min;
        t->right = delete (t->right, min);
    }
    return t;
}

int main(void)
{
    bst_t *t = NULL;
    int n, command, data, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &data);
            t = insert(t, data);
            break;
        case 2:
            scanf("%d", &data);
            t = delete (t, data);
            break;
        case 3:
            scanf("%d", &data);
            printf("%d\n", find(t, data));
            break;
        case 4:
            printf("%d\n", find_min(t));
            break;
        case 5:
            printf("%d\n", find_max(t));
            break;
        case 6:
            scanf("%d", &k);
            printf("%d\n", find_k_th(t, k));
            break;
        }
    }
    return 0;
}
