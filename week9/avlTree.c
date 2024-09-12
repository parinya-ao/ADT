#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t tree_t;
typedef node_t avl_t;

void print_tree_2(avl_t *t, int depth, char pre)
{
    if (t == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%c%d\n", pre, t->data);
    print_tree_2(t->left, depth + 1, 'L');
    print_tree_2(t->right, depth + 1, 'R');
}

void print_tree(avl_t *t)
{
    print_tree_2(t, 0, 'r');
}

node_t *createNode(int data)
{
    node_t *tmp = (node_t *)malloc(sizeof(node_t));
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1; // Set height to 1 for new node
    return tmp;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(avl_t *t)
{
    return (t == NULL) ? 0 : t->height;
}

void update_h(avl_t *t)
{
    if (t != NULL)
    {
        t->height = 1 + max(height(t->left), height(t->right));
    }
}

avl_t *rotate_left(avl_t *t)
{
    avl_t *temp = t->right;
    t->right = temp->left;
    temp->left = t;
    update_h(t);
    update_h(temp);
    return temp;
}

avl_t *rotate_right(avl_t *t)
{
    avl_t *temp = t->left;
    t->left = temp->right;
    temp->right = t;
    update_h(t);
    update_h(temp);
    return temp;
}

int get_balance(avl_t *t)
{
    return (t == NULL) ? 0 : height(t->left) - height(t->right);
}

avl_t *rebalance(avl_t *t)
{
    if (t == NULL)
    {
        return t;
    }
    int balance = get_balance(t);
    if (balance > 1 && get_balance(t->left) >= 0)
    {
        return rotate_right(t);
    }
    if (balance > 1 && get_balance(t->left) < 0)
    {
        t->left = rotate_left(t->left);
        return rotate_right(t);
    }
    if (balance < -1 && get_balance(t->right) <= 0)
    {
        return rotate_left(t);
    }
    if (balance < -1 && get_balance(t->right) > 0)
    {
        t->right = rotate_right(t->right);
        return rotate_left(t);
    }
    return t;
}

avl_t *insert(avl_t *t, const int data)
{
    if (t == NULL)
    {
        return createNode(data);
    }

    if (data < t->data)
    {
        t->left = insert(t->left, data);
    }
    else if (data > t->data)
    {
        t->right = insert(t->right, data);
    }

    update_h(t);

    return rebalance(t);
}

int find_min(avl_t *t)
{
    if (t == NULL)
        return -1;
    if (t->left == NULL)
        return t->data;
    return find_min(t->left);
}

avl_t *delete(avl_t *t, const int data)
{
    if (t == NULL)
    {
        return t;
    }

    if (data < t->data)
    {
        t->left = delete (t->left, data);
    }
    else if (data > t->data)
    {
        t->right = delete (t->right, data);
    }
    else
    {
        if (t->left == NULL || t->right == NULL)
        {
            avl_t *temp = t->left ? t->left : t->right;
            if (temp == NULL)
            {
                temp = t;
                t = NULL;
            }
            else
            {
                *t = *temp;
            }
            free(temp);
        }
        else
        {
            int min = find_min(t->right);
            t->data = min;
            t->right = delete (t->right, min);
        }
    }

    if (t == NULL)
        return t;

    update_h(t);

    return rebalance(t);
}

int main(void)
{
    avl_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
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
            print_tree(t);
            break;
        }
    }
    return 0;
}
