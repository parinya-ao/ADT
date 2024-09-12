#include <stdio.h>
#include <stdlib.h>
// You can define your own (one or more)
// structures here. However, we eventually
// need the data type "tree_t".
// For example:
typedef struct node
{
    int value;
    struct node *next_sibling;
    struct node *first_child;
} node_t;
typedef node_t tree_t;
// Write your code here
//------------------------------
void print_tree(node_t *t);
tree_t *movetoparent(tree_t *t, int v);
tree_t *searchForFuntions(tree_t *t, int v) // pass
{
    if (t == NULL || t->value == v)
    {
        return t;
    }
    tree_t *pos = searchForFuntions(t->first_child, v);
    if (pos != NULL)
    {
        return pos;
    }
    else
    {
        return searchForFuntions(t->next_sibling, v);
    }
}

int search(tree_t *t, int v) // pass
{
    tree_t *pos = searchForFuntions(t, v);
    if (pos == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

tree_t *attach(tree_t *t, int p, int c) // pass
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));
    node->value = c;
    node->first_child = NULL;
    node->next_sibling = NULL;

    if (t == NULL)
    {
        return node;
        // if (p == -1) //
        // {
        //     return node;
        // }
        // else
        // {
        //     free(node);
        //     return t;
        // }
    }

    tree_t *pos = searchForFuntions(t, p);
    if (pos == NULL)
    {
        free(node);
        return t;
    }

    if (pos->first_child == NULL)
    {
        pos->first_child = node;
    }
    else
    {
        pos = pos->first_child;
        while (pos->next_sibling != NULL)
        {
            pos = pos->next_sibling;
        }
        pos->next_sibling = node;
    }
    return t;
}

void free_subtree(tree_t *t) // pass
{
    if (t == NULL)
    {
        return;
    }
    free_subtree(t->first_child);
    free_subtree(t->next_sibling);
    free(t);
}

tree_t *detach(tree_t *t, int p) // ?
{
    if (t == NULL)
    {
        return t;
    }

    if (p == -1)
    {
        tree_t *temp = t;
        t = t->next_sibling;
        free(temp);
        return t;
    }

    tree_t *getout = searchForFuntions(t, p);
    if (getout == NULL)
    {
        return t;
    }
    getout->first_child = NULL;
    tree_t *parent = movetoparent(t, p);
    if (parent == NULL)
    {
        return t;
    }
    tree_t *child = parent->first_child;
    while (child->next_sibling != NULL)
    {
        if (child->next_sibling->value == p)
        {
            child->next_sibling = child->next_sibling->next_sibling;
            break;
        }
        child = child->next_sibling;
    }

    return t;
}
int degree(node_t *t, int node)
{
    tree_t *pos = searchForFuntions(t, node); // หา Pos
    int count = 0;                            // นับ = 0
    if (pos == NULL)                          // pass
    {
        return 0;
    }
    else
    {
        tree_t *child = pos->first_child;
        while (child != NULL)
        {
            count += 1;
            child = child->next_sibling;
        }
    }
    return count;
}
int is_root(node_t *t, int node)
{
    if (t == NULL)
    {
        return 0;
    }
    tree_t *pos = searchForFuntions(t, node);
    if (t->value == pos->value && t->first_child == pos->first_child && t->next_sibling == pos->next_sibling)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

int is_leaf(node_t *t, int node)
{
    if (t == NULL)
    {
        return 0;
    }
    tree_t *pos = searchForFuntions(t, node);
    if (pos->first_child == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

tree_t *movetoparent(tree_t *t, int v)
{
    if (t == NULL)
    {
        return NULL;
    }

    if (t->first_child != NULL)
    {
        tree_t *child = t->first_child;
        while (child != NULL)
        {
            if (child->value == v)
            {
                return t;
            }
            child = child->next_sibling;
        }
    }

    tree_t *parent = movetoparent(t->first_child, v);
    if (parent != NULL)
    {
        return parent;
    }

    return movetoparent(t->next_sibling, v);
}

void siblings(node_t *t, int node)
{
    if (t == NULL)
    {
        printf("0\n");
        return;
    }

    tree_t *findparent = movetoparent(t, node);
    if (findparent == NULL)
    {
        printf("\n");
        return;
    }

    tree_t *pos = findparent->first_child;
    if (pos == NULL)
    {
        printf("\n");
        return;
    }

    while (pos != NULL)
    {
        if (pos->value != node)
        {
            printf("%d ", pos->value);
        }
        pos = pos->next_sibling;
    }
    printf("\n");
}

int depth(node_t *t, int node)
{
    if (t == NULL)
    {
        return 0;
    }

    tree_t *pos = searchForFuntions(t, node);
    if (pos == NULL)
    {
        return 0;
    }

    int count = 0;
    while (pos != NULL)
    {
        count++;

        pos = movetoparent(t, pos->value);
    }
    return count - 1;
}

int print_path(node_t *t, int start, int end)
{
    if (t == NULL)
    {
        return 0;
    }
    tree_t *pos = searchForFuntions(t, end);
    if (pos == NULL)
    {
        return 0;
    }
    int stepback[100000];
    int index = 0;
    while (pos != NULL)
    {

        // printf("%d ", pos->value);
        stepback[index] = pos->value;
        index += 1;

        if (pos->value == start)
        {
            break;
        }

        pos = movetoparent(t, pos->value);
    }
    // int countrow = 0;
    for (int i = index - 1; i >= 0; i--)
    {
        printf("%d ", stepback[i]);
        // countrow += 1;
        // if (countrow == 4 && i != 0)
        // {
        //     printf("\n");
        //     countrow = 0;
        // }
    }
    printf("\n");
    return 0;
}

int path_length(node_t *t, int start, int end)
{
    if (t == NULL)
    {
        return 0;
    }
    tree_t *pos = searchForFuntions(t, end);
    if (pos == NULL)
    {
        return 0;
    }
    int count = 0;
    while (pos != NULL)
    {

        // printf("%d ", pos->value);
        count += 1;

        if (pos->value == start)
        {
            break;
        }

        pos = movetoparent(t, pos->value);
    }

    // printf("\n");
    return count;
}
int ancestor(node_t *t, int node)
{
    if (t == NULL)
    {
        return 0;
    }
    tree_t *pos = searchForFuntions(t, node);
    if (pos == NULL)
    {
        return 0;
    }
    int stepback[100000];
    int index = 0;
    while (pos != NULL)
    {

        // printf("%d ", pos->value);
        stepback[index] = pos->value;
        index += 1;
        pos = movetoparent(t, pos->value);
    }
    for (int i = index - 1; i >= 0; i--)
    {
        printf("%d ", stepback[i]);
    }
    printf("\n");
    return 0;
}

int get_de(node_t *t, int result[][2], int *index, int n)
{
    if (t == NULL)
    {
        return 0;
    }

    result[*index][0] = t->value;
    result[*index][1] = n;
    (*index)++;

    n += 1;

    get_de(t->first_child, result, index, n);

    get_de(t->next_sibling, result, index, n - 1);

    return 0;
}
void descendant(node_t *t, int node)
{
    int result[5000][2];
    int index = 0;
    node_t *pos = searchForFuntions(t, node);
    if (pos == NULL)
    {
        return;
    }
    printf("%d ", pos->value);
    get_de(pos->first_child, result, &index, 0);

    int shouldIprint = 1;
    int DidIprint = 0;
    int j = 0;
    // print_tree(pos);

    while (shouldIprint == 1)
    {
        for (int i = 0; i < index; i++)
        {
            if (result[i][1] == j)
            {
                printf("%d ", result[i][0]);
                DidIprint = 1;
            }
        }
        j += 1;
        if (DidIprint == 0)
        {
            break;
        }
        DidIprint = 0;
    }

    printf("\n");

    return;
}

void bfs(node_t *t)
{
    int node = t->value;
    descendant(t, node);
    return;
}

node_t *dfs(node_t *t)
{
    if (t == NULL)
    {
        return t;
    }
    printf("%d ", t->value);

    tree_t *pos = dfs(t->first_child);
    if (pos != NULL)
    {
        return pos;
    }
    else
    {
        return dfs(t->next_sibling);
    }
}

node_t *real_print_tree(node_t *t, int n)
{
    if (t == NULL)
    {
        return t;
    }
    printf("%*d\n", n, t->value);
    n += 4;

    tree_t *pos = real_print_tree(t->first_child, n);
    if (pos != NULL)
    {
        return pos;
    }
    else
    {
        n -= 4;
        return real_print_tree(t->next_sibling, n);
    }
}
void print_tree(node_t *t)
{
    real_print_tree(t, 0);
}
//-------------------------------
// ...
int main(void)
{
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d %d", &parent, &child);
            t = attach(t, parent, child);
            break;
        case 2:
            scanf("%d", &node);
            t = detach(t, node);
            break;
        case 3:
            scanf("%d", &node);
            printf("%d\n", search(t, node));
            break;
        case 4:
            scanf("%d", &node);
            printf("%d\n", degree(t, node));
            break;
        case 5:
            scanf("%d", &node);
            printf("%d\n", is_root(t, node));
            break;
        case 6:
            scanf("%d", &node);
            printf("%d\n", is_leaf(t, node));
            break;
        case 7:
            scanf("%d", &node);
            siblings(t, node);
            break;
        case 8:
            scanf("%d", &node);
            printf("%d\n", depth(t, node));
            break;
        case 9:
            scanf("%d %d", &start, &end);
            print_path(t, start, end);
            break;
        case 10:
            scanf("%d %d", &start, &end);
            printf("%d\n",
                   path_length(t, start, end));
            break;
        case 11:
            scanf("%d", &node);
            ancestor(t, node);
            break;
        case 12:
            scanf("%d", &node);
            descendant(t, node);
            break;
        case 13:
            bfs(t);
            break;
        case 14:
            dfs(t);
            break;
        case 15:
            print_tree(t);
            break;
        }
    }
    return 0;
}