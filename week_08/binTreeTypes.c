#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __bin_tree__
#define __bin_tree__
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} tree_t;
#endif

tree_t *createNode(int data)
{
    tree_t *tmp;
    tmp = (tree_t *)malloc(sizeof(tree_t));
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

tree_t *searchNode(tree_t *root, int data)
{
    tree_t *result;

    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;

    result = searchNode(root->left, data);
    if (result != NULL)
        return result;

    return searchNode(root->right, data);
}

void add(tree_t *parent, tree_t *newNode, int branch)
{
    if (branch == 1)
        parent->left = newNode;
    else if (branch == 2)
        parent->right = newNode;
}

tree_t *attach(tree_t *root, int parentData, int childData, int branch)
{
    tree_t *tmpNode;

    if (parentData == -1)
    {
        return createNode(childData);
    }
    tmpNode = searchNode(root, parentData);
    add(tmpNode, createNode(childData), branch);
    return root;
}

bool is_full(tree_t *t) // test pass
{
    if (t == NULL)
    {
        return true;
    }

    if (t->left == NULL && t->right == NULL)
    {
        return true;
    }
    else if (t->left != NULL && t->right != NULL)
    {
        return is_full(t->left) && is_full(t->right);
    }
    else
    {
        return false;
    }
}

bool is_skewed_left(tree_t *t)
{
    if (t == NULL)
    {
        return true;
    }
    if (t->right != NULL)
    {
        return false;
    }
    is_skewed_left(t->left);
}
bool is_skewed_right(tree_t *t)
{
    if (t == NULL)
    {
        return true;
    }
    if (t->left != NULL)
    {
        return false;
    }
    is_skewed_right(t->right);
}

bool is_skewed(tree_t *t)
{
    return is_skewed_left(t) || is_skewed_right(t);
}

bool is_degenerate(tree_t *t) // test pass
{
    if (t == NULL || (t->left == NULL && t->right == NULL))
    {
        return true;
    }
    if (t->left != NULL && t->right != NULL)
    {
        return false;
    }
    else if (t->left != NULL)
    {
        return is_degenerate(t->left);
    }
    return is_degenerate(t->right);
}

int find_depth(tree_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    int right_depth = find_depth(t->right);
    int left_depth = find_depth(t->left);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

bool check(tree_t *t, int level, int depth) // tase und pass
{
    if (t == NULL)
    {
        return true;
    }
    if (t->left == NULL && t->right == NULL)
    {
        return (level + 1 == depth);
    }
    if (t->left == NULL || t->right == NULL)
    {
        return false;
    }
    return check(t->left, level + 1, depth) && check(t->right, level + 1, depth);
}

bool is_perfect(tree_t *t)
{
    if (t == NULL)
    {
        return true;
    }
    int depth = find_depth(t);
    check(t, 0, depth);
}

int count_node(tree_t *t)
{
    if (t == NULL) // base case
    {
        return 0;
    }
    // inductive step
    return count_node(t->left) + count_node(t->right) + 1;
}

bool find(tree_t *t, int index, int limit)
{
    if (t == NULL)
    {
        return true;
    }
    if (limit <= index)
    {
        return false;
    }
    bool L_complete = find(t->left, 2 * index + 1, limit);
    bool R_complete = find(t->right, 2 * index + 2, limit);
    return L_complete && R_complete;
}

bool is_complete(tree_t *t)
{
    if (t == NULL)
    {
        return true;
    }
    return find(t, 0, count_node(t));
}

int main(void)
{
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &parent, &child,
              &branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d %d %d %d %d\n", is_full(t),
           is_perfect(t), is_complete(t),
           is_degenerate(t), is_skewed(t));
    return 0;
}