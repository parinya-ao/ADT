#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t, stack_t;

void empty(stack_t *s)
{
    if (s == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack is not empty.\n");
}

int cal_size(stack_t *s)
{
    if (s == NULL)
    {
        return 0;
    }
    return 1 + cal_size(s->next);
}

void size(stack_t *s)
{
    printf("%d\n", cal_size(s));
}

stack_t *pop(stack_t *s)
{
    if (s == NULL)
    {
        return s;
    }
    node_t *first_node = s;
    s = s->next;
    free(first_node);
    return s;
}

void top(stack_t *s)
{
    if (s == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("%d\n", s->data);
}

stack_t *push(stack_t *s, int val)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = val;
    node->next = s;

    return node;
}

int main(void)
{
    stack_t *s = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &value);
            s = push(s, value);
            break;
        case 2:
            top(s);
            break;
        case 3:
            s = pop(s);
            break;
        case 4:
            empty(s);
            break;
        case 5:
            size(s);
            break;
        }
    }
    return 0;
}
