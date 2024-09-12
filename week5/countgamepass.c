#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int k;
int n;

typedef struct node
{
    int data;
    int limit;
    struct node *next;
} node_t;

void show(node_t *node)
{
    node_t *temp = node;
    do
    {
        printf("%i value %i\n", temp->data, temp->limit);
        temp = temp->next;
    } while (temp != node);
}

bool check(int count)
{
    if (count % k == 0)
    {
        return true;
    }
    char str[100];
    sprintf(str, "%d", count);
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == k + '0')
        {
            return true;
        }
    }
    return false;
}

void calculated(node_t *node)
{
    node_t *current = node;
    node_t *prev = NULL;
    int live = n;
    unsigned long long count = 1;

    while (n > 1)
    {
        if (current->limit <= -1)
        {
            prev->next = prev->next->next;
            current->next = NULL;
            node_t *temp = current;
            current = prev->next;
            --n;
            free(temp);
            continue;
        }

        // printf("Count: %llu, Node %i, Limit before: %i\n", count, current->data, current->limit);
        if (check(count))
        {
            current->limit -= 1;
            // printf("Decrementing limit of Node %i, new limit: %i\n", current->data, current->limit);
        }

        prev = current;
        current = current->next;
        count++;
    }
    printf("%i", current->data);
    return;
}

int main()
{
    scanf("%i %i", &n, &k);

    node_t *head = NULL;
    node_t *prev = NULL;

    for (int i = 0; i < n; i++)
    {
        int val;
        scanf("%i", &val);

        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->data = (i + 1);
        new_node->limit = val;
        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
        }
        else
        {
            prev->next = new_node;
        }
        prev = new_node;
    }

    prev->next = head;

    calculated(head);

    return 0;
}
