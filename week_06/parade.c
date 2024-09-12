#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t, stack_t;

int isEmpty(stack_t *s)
{
    return s == NULL;
}

stack_t *push(stack_t *s, int val)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = val;
    node->next = s;
    return node;
}

// เอาตัวบนสุดออก
stack_t *pop(stack_t *s)
{
    if (isEmpty(s))
    {
        return s;
    }
    node_t *first_node = s;
    s = s->next;
    free(first_node);
    return s;
}

// find top of stack
int top(stack_t *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty.\n");
        return -1;
    }
    return s->data;
}

int main()
{
    stack_t *s1 = NULL;
    stack_t *s2 = NULL;

    int n;
    scanf("%d", &n);
    int count = 1;

    for (int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);

        if (num == count)
        {
            count++;
            s1 = push(s1, num);
        }
        else
        {
            s2 = push(s2, num);
        }

        while (!isEmpty(s2) && top(s2) == count)
        {
            s1 = push(s1, top(s2));
            s2 = pop(s2);
            count++;
        }
    }

    while (!isEmpty(s2))
    {
        if (!isEmpty(s1) && top(s1) == top(s2) - 1)
        {
            s1 = push(s1, top(s2));
            s2 = pop(s2);
        }
        else
        {
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}
