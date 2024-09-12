#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;
typedef node_t queue_t;

// #define printf("%i\n",x) print()

int cal_size(queue_t *q)
{
    if (q == NULL)
    {
        return 0;
    }
    return 1 + cal_size(q->next);
}

void size(queue_t *q)
{
    printf("%i\n", cal_size(q));
}

void empty(queue_t *q)
{
    if (q == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue is not empty.\n");
}

void show(queue_t *q)
{
    if (q == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }
    queue_t *current = q;
    while (current != NULL)
    {
        printf("%i ", current->data);
        current = current->next;
    }
    printf("\n");
}

queue_t *dequeue(queue_t *q)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node = q;
    if (q == NULL)
    {
        printf("Queue is empty.\n");
        return q;
    }
    printf("%i\n", q->data);
    node_t *temp = (node_t *)malloc(sizeof(node_t)); // create node temp
    temp = q;
    q = q->next;
    free(temp);

    return q;
}

queue_t *enqueue(queue_t *q, int val)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = val;
    node->next = NULL; // !
    node_t *temp = q;
    if (q == NULL)
    {
        q = node;
        return q;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
    return q;
}

void free_queue(queue_t *q)
{
    while (q != NULL)
    {
        queue_t *temp = q;
        q = q->next;
        free(temp);
    }
}

int main(void)
{
    queue_t *q = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &value);
            q = enqueue(q, value);
            break;
        case 2:
            q = dequeue(q);
            break;
        case 3:
            show(q);
            break;
        case 4:
            empty(q);
            break;
        case 5:
            size(q);
            break;
        }
    }
    free_queue(q);
    return 0;
}
