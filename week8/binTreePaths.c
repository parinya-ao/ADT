#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#define null NULL

#ifndef __bin_tree__
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int solve(tree_t *t, int target)
{
    // basecase
    if (t == null)
    {
        return 0;
    }
    int count = 0;
    if (t->data == target)
    {
        ++count;
    }
    int n_target = target - t->data;
    count += solve(t->right, n_target);
    count += solve(t->left, n_target);
    return count;
}

int countPathsWithSum(tree_t *t, int target)
{
    if (t == null)
    {
        return 0;
    }
    int current = solve(t, target);
    int left = countPathsWithSum(t->right, target);
    int right = countPathsWithSum(t->left, target);
    return current + left + right;
}

int main(void)
{
    tree_t *t = NULL;
    int n, s, i;
    int parent, child;
    int branch;
    scanf("%d %d", &n, &s);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &parent, &child,
              &branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d\n", countPathsWithSum(t, s));
    return 0;
}