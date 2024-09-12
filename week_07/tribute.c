#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 100

typedef struct tree
{
    int val;
    int cnt;
    int cost;
    struct tree *prev;
    struct tree *depth;
    struct tree *next;
    bool visited;
} tree_t;

tree_t *nodes[MAX_NODES];
int node_cnt = 0;

tree_t *find_or_create(int val)
{
    if (nodes[val] == NULL)
    {
        nodes[val] = (tree_t *)malloc(sizeof(tree_t));
        nodes[val]->val = val;
        nodes[val]->cost = 0;
        nodes[val]->depth = NULL;
        nodes[val]->next = NULL;
        nodes[val]->visited = false;
        nodes[val]->cnt = 0;
        nodes[val]->prev = NULL;
    }
    return nodes[val];
}

tree_t *attach(tree_t *t, int parent, int child, int cost)
{
    tree_t *parent_node = find_or_create(parent);
    tree_t *child_node = find_or_create(child);

    child_node->cost = cost;
    child_node->cnt = parent_node->cnt - cost;

    if (parent_node->depth == NULL)
    {
        child_node->prev = parent_node;
        parent_node->depth = child_node;
    }
    else
    {
        tree_t *sibling = parent_node->depth;
        while (sibling->next != NULL)
        {
            sibling = sibling->next;
        }
        sibling->next = child_node;
        child_node->prev = parent_node;
    }
    return t;
}

int solve(tree_t *t)
{
    if (t == NULL)
    {
        return 0;
    }

    int cnt = (t->cnt < 0) ? 0 : 1;

    cnt += solve(t->depth);
    cnt += solve(t->next);

    return cnt;
}

int main()
{
    memset(nodes, 0, sizeof(nodes));

    tree_t *t = find_or_create(0);
    t->cnt = 0;
    t->visited = true;

    int n, money;
    scanf("%i %i", &n, &money);
    t->cnt = money;

    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        scanf("%i %i %i", &a, &b, &c);
        t = attach(t, a, b, c);
    }

    printf("%i\n", solve(t) - 1);

    return 0;
}
