#include <stdio.h>
#include <stdlib.h>
#include <week8.h>
#ifndef __bin_tree__
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;
#endif

void fun_print_preorder(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    printf("%i ", t->data);
    fun_print_preorder(t->left);
    fun_print_preorder(t->right);
}

void fun_print_postorder(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    fun_print_postorder(t->left);
    fun_print_postorder(t->right);
    printf("%i ", t->data);
}

void fun_print_inorder(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    fun_print_inorder(t->left);
    printf("%i ", t->data);
    fun_print_inorder(t->right);
}

void print_preorder(tree_t *t)
{
    fun_print_preorder(t);
    printf("\n");
}

void print_postorder(tree_t *t)
{
    fun_print_postorder(t);
    printf("\n");
}

void print_inorder(tree_t *t)
{
    fun_print_inorder(t);
    printf("\n");
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
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }
    print_preorder(t);
    print_postorder(t);
    print_inorder(t);
    return 0;
}
