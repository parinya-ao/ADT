#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char data;
    struct node_t *next;
} node_t;

node_t *push(node_t *top, char val)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = val;
    node->next = top;
    return node;
}

node_t *pop(node_t *top)
{
    if (top == NULL)
    {
        return NULL;
    }
    node_t *temp = top;
    top = top->next;
    free(temp);
    return top;
}

char top(node_t *top)
{
    if (top == NULL)
    {
        return '\0';
    }
    return top->data;
}

int isEmpty(node_t *top)
{
    return top == NULL;
}

int main()
{
    char str[1000];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    node_t *stack = NULL;
    int status = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (status == 0)
        {
            if (str[i] == 'x')
            {
                status = 1;
            }
            else
            {
                stack = push(stack, str[i]);
            }
        }
        else if (status == 1)
        {
            if (!isEmpty(stack) && str[i] == top(stack))
            {
                stack = pop(stack);
                continue;
            }
            if (str[i] == 'y')
            {
                break;
            }
            else
            {
                printf("0\n");
                return 0;
            }
        }
    }
    if (status == 1 && isEmpty(stack))
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}
