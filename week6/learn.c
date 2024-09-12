#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node_t;

typedef node_t stack_t;

void push(stack_t *s, int v)
{
    node_t *node = (node_t *) malloc(sizeof(node_t));
    node->val = v;
    node->next = NULL;

    node->next = s;
    s = node;
}

int main()
{
    stack_t *s = NULL;
    push(s, 1);
    push(s, 2);
    return 0;
}