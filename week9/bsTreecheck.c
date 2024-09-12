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

void update_height(node_t *node)
{
    if (node != NULL)
    {
        node->height = height(node);
    }
}

void print_tree_2(avl_t *t, int depth, char pre)
{
    int i;

    if (t == NULL)
        return;
    for (i = 0; i < depth; i++)
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
    return tmp;
}

node_t *searchNode(tree_t *root, int data)
{
    node_t *result;

    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;

    result = searchNode(root->left, data);
    if (result != NULL)
        return result;

    return searchNode(root->right, data);
}

void add(tree_t *parent, node_t *newNode, int branch)
{
    if (branch == 1)
        parent->left = newNode;
    else if (branch == 2)
        parent->right = newNode;
}

tree_t *attach(tree_t *root, int parentData, int childData, int branch)
{
    node_t *tmpNode;

    if (parentData == -1)
        return createNode(childData);

    tmpNode = searchNode(root, parentData);
    add(tmpNode, createNode(childData), branch);

    return root;
}

int max(int a, int b)
{
    if (a < b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int height(tree_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    int left = height(t->left);
    int right = height(t->right);
    return max(left, right) + 1;
}

bool is_bst_solve(tree_t *t, int min, int max)
{
    if (t == NULL)
        return true;
    if (t->data < min || t->data > max)
        return false;
    return is_bst_solve(t->left, min, t->data) && is_bst_solve(t->right, t->data, max);
}

bool is_bst(tree_t *t)
{
    return is_bst_solve(t, -100000000, 100000000);
}

bool is_avl(tree_t *t)
{
    if (t == NULL)
    {
        return true;
    }
    if (is_bst(t) == false)
    {
        return false;
    }
    int left = height(t->left);
    int right = height(t->right);

    if (abs(left - right) > 1)
    {
        return false;
    }
    return is_avl(t->left) && is_avl(t->right);
}

int main(void)
{
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &parent, &child,
              &branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d %d\n", is_bst(t), is_avl(t));
    return 0;
}