#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int n, k;

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

void freemem(node_t *node)
{
    node_t *head = node;
    node_t *temp;
    do
    {
        temp = node;
        node = node->next;
        free(temp);
    } while (head != node);
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
    long long count = 1;
    while (live > 1)
    {
        printf("n = %d \n", live);
        if (current->limit < 0)
        {
            if (current == node)
            {
                node = node->next;
            }
            prev->next = current->next;
            node_t *temp = current;
            current = current->next;
            free(temp);
            live--;
        }
        else
        {
            if (check(count))
            {
                current->limit -= 1;
            }
            prev = current;
            current = current->next;
            count++;
        }
    }
    printf("%i", node->data);
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
            head->next = head; // Point to itself to form a circular list
        }
        else
        {
            new_node->next = head;
            prev->next = new_node;
        }
        prev = new_node;
    }

    calculated(head);

    freemem(head);
    return 0;
}
