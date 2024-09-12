#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

node_t *enqueue(node_t *q, int val)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = val;
    node->next = NULL;
    if (q == NULL)
    {
        return node;
    }
    node_t *temp = q;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
    return q;
}

node_t *dequeue(node_t *q)
{
    if (q == NULL)
    {
        return q;
    }
    node_t *temp = q;
    q = q->next;
    free(temp);
    return q;
}

void free_queue(node_t *q)
{
    while (q != NULL)
    {
        node_t *temp = q;
        q = q->next;
        free(temp);
    }
}

int main(void)
{
    int sz = 0;
    scanf("%d", &sz);
    sz *= 100;
    int n;
    scanf("%d", &n);

    node_t *L = NULL;
    node_t *R = NULL;

    for (int i = 0; i < n; i++)
    {
        int len;
        char d;
        scanf("%d %c", &len, &d);
        if (d == 'L')
        {
            L = enqueue(L, len);
        }
        else if (d == 'R')
        {
            R = enqueue(R, len);
        }
    }

    bool side = 1;
    long long int trips = 0;

#pragma GCC unroll 4
    while (L != NULL || R != NULL)
    {
        int load = 0;
        if (side)
        {
            node_t *tempL = L;
#pragma GCC unroll 4
            while (tempL != NULL && load + tempL->data <= sz)
            {
                load += tempL->data;
                tempL = tempL->next;
                L = dequeue(L);
            }
        }
        else
        {
            node_t *tempR = R;
#pragma GCC unroll 4
            while (tempR != NULL && load + tempR->data <= sz)
            {
                load += tempR->data;
                tempR = tempR->next;
                R = dequeue(R);
            }
        }
        side = !side;
        trips++;
    }

    printf("%lld\n", trips);

    free_queue(L);
    free_queue(R);

    return 0;
}
