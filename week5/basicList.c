#pragma GCC optimize("Ofast")
#include <stdio.h>

#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

void show(node_t *node)
{
    node_t *view = node;
    while (view != NULL)
    {
        printf("%i ", view->data);
        view = view->next;
    }
    printf("\n");
}

node_t *append(node_t *node)
{
    int val;
    scanf("%i", &val);

    node_t *n_node = (node_t *)malloc(sizeof(node_t));
    n_node->data = val;
    n_node->next = NULL;

    if (node == NULL)
    {
        return n_node;
    }
    node_t *view = node;
    while (view->next != NULL)
    {
        view = view->next;
    }
    view->next = n_node;
    return node;
}

void get(node_t *node)
{
    int index = 0;
    scanf("%i", &index);
    node_t *view = node;
    for (int i = 0; i < index; i++)
    {
        view = view->next;
    }
    printf("%i\n", view->data);
    return;
}

node_t *reverse(node_t *node)
{
    if (node == NULL || node->next == NULL)
    {
        return node;
    }
    node_t *r_node = reverse(node->next);

    node->next->next = node;
    node->next = NULL;
    return r_node;
}

node_t *cut(node_t *node)
{
    int a, b;
    scanf("%i %i", &a, &b);

    node_t *prev = NULL, *current = node;
    int index = 0;

    while (index < a)
    {
        prev = current;
        current = current->next;
        index++;
    }

    if (current == NULL)
    {
        return node;
    }

    node_t *cut_start = current;

    node_t *cut_end = current;
    while (index < b)
    {
        cut_end = cut_end->next;
        index++;
    }

    if (cut_end != NULL)
    {
        current = cut_end->next;
        cut_end->next = NULL;
    }

    if (prev != NULL)
    {
        prev->next = current;
    }
    else
    {
        node = current;
    }

    return cut_start;
}

int main(void)
{
    node_t *startNode;
    int n, i;
    char command;
    startNode = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf(" %c", &command);
        switch (command)
        {
        case 'A':
            startNode = append(startNode);
            break;
        case 'G':
            get(startNode);
            break;
        case 'S':
            show(startNode);
            break;
        case 'R':
            startNode = reverse(startNode);
            break;
        case 'C':
            startNode = cut(startNode);
            break;
        default:
            break;
        }
    }
    return 0;
}