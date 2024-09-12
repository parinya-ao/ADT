#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree
{
    int val;
    int hight;
    struct tree *prev; // prev
    struct tree *next;
    struct tree *depth;
} tree_t;

typedef struct node
{
    void *data; // Changed to 'void *data'
    struct node *next;
} node_t;

typedef node_t queue_t;

typedef struct stack_node
{
    int data;
    struct stack_node *next;
} stack_node_t, stack_t;

// Stack Implementation
bool empty(stack_t *s)
{
    if (s == NULL)
    {
        return true;
    }
    return false;
}

int cal_stack_size(stack_t *s)
{
    if (s == NULL)
    {
        return 0;
    }
    return 1 + cal_stack_size(s->next);
}

void stack_size(stack_t *s)
{
    printf("%d\n", cal_stack_size(s));
}

stack_t *pop(stack_t *s)
{
    if (s == NULL)
    {
        return s;
    }
    stack_node_t *first_node = s;
    s = s->next;
    free(first_node);
    return s;
}

void stack_top(stack_t *s)
{
    if (s == NULL)
    {
        printf("no value\n");
        return;
    }
    printf("%d ", s->data);
}

stack_t *push(stack_t *s, int val)
{
    stack_node_t *node = (stack_node_t *)malloc(sizeof(stack_node_t));
    node->data = val;
    node->next = s;
    return node;
}

void free_stack(stack_t *s)
{
    while (s != NULL)
    {
        stack_t *temp = s;
        s = s->next;
        free(temp);
    }
}

int cal_size(queue_t *q)
{
    if (q == NULL)
    {
        return 0;
    }
    return 1 + cal_size(q->next);
}

int size(queue_t *q)
{
    return cal_size(q);
}

bool isEmpty(queue_t *q)
{
    return (q == NULL);
}

void show(queue_t *q)
{
    if (q == NULL)
    {
        return;
    }
    queue_t *current = q;
    while (current != NULL)
    {
        printf("%i ", *(int *)current->data); // Print the value pointed by 'data'
        current = current->next;
    }
    printf("\n");
}

tree_t *front(queue_t *q)
{
    if (q != NULL)
    {
        return (tree_t *)q->data;
    }
    return NULL;
}

queue_t *dequeue(queue_t *q)
{
    if (q == NULL)
    {
        return NULL;
    }
    queue_t *temp = q;
    q = q->next;
    free(temp);
    return q;
}

queue_t *enqueue(queue_t *q, tree_t *val)
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

void free_queue(queue_t *q)
{
    while (q != NULL)
    {
        queue_t *temp = q;
        q = q->next;
        free(temp);
    }
}

void dfs(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    printf("%i ", t->val);
    dfs(t->depth);
    dfs(t->next);
}

void bfs(tree_t *root)
{
    if (root == NULL)
    {
        return;
    }

    queue_t *q = NULL; // Initialize the queue

    q = enqueue(q, root);

    while (!isEmpty(q))
    {
        tree_t *current = front(q);
        q = dequeue(q);
        printf("%i ", current->val);
        tree_t *child = current->depth;
        while (child != NULL)
        {
            q = enqueue(q, child);
            child = child->next;
        }
    }
    free_queue(q);
}

tree_t *find_address(tree_t *t, int value)
{
    if (t == NULL || t->val == value)
    {
        return t;
    }
    tree_t *pos = find_address(t->depth, value);
    if (pos != NULL)
    {
        return pos;
    }
    else
    {
        return find_address(t->next, value);
    }
}

tree_t *attach(tree_t *tree, int parent, int child)
{
    // Create Node
    tree_t *temp = (tree_t *)malloc(sizeof(tree_t));
    temp->depth = NULL;
    temp->next = NULL;
    temp->val = child;
    if (tree == NULL)
    {
        temp->prev = NULL;
        temp->hight = 0;
        return temp;
    }

    tree_t *position = find_address(tree, parent); // find_address and give address
    // If parent has no child
    if (position->depth == NULL)
    {
        temp->prev = position;
        position->depth = temp;
        temp->hight = position->hight + 1;
    }
    // If parent has a child
    else
    {
        tree_t *view = position->depth;
        temp->hight = view->hight;
        temp->prev = find_address(tree, parent);
        while (view->next != NULL)
        {
            view = view->next;
        }
        view->next = temp;
    }
    return tree;
}

int depth(tree_t *tree, int node)
{
    tree_t *position = find_address(tree, node);
    return position->hight;
}

int search(tree_t *tree, int val)
{
    tree_t *node = find_address(tree, val);
    if (node == NULL)
    {
        return 0;
    }
    return 1;
}

void print_tree(tree_t *tree)
{
    if (tree == NULL)
    {
        return;
    }
    for (int i = 0; i < tree->hight; i++)
    {
        printf("    ");
    }
    printf("%i\n", tree->val);
    print_tree(tree->depth);
    print_tree(tree->next);
}

int degree(tree_t *tree, int val)
{
    tree_t *node = find_address(tree, val);
    node = node->depth;
    int cnt = 0;
    while (node != NULL)
    {
        cnt++;
        node = node->next;
    }
    return cnt;
}

tree_t *detach(tree_t *t, int node)
{
    // find layer of node
    tree_t *temp = find_address(t, node);
    if (temp == NULL)
    {
        return t;
    }
    tree_t *upper_node = temp->prev;
    if (upper_node == NULL)
    {
        free(temp);
        return NULL;
    }
    // If parent has no other children
    if (upper_node->depth == temp)
    {
        upper_node->depth = temp->next;
    }
    // Not the first child
    else
    {
        tree_t *current = upper_node->depth;
        while (current->next != temp)
        {
            current = current->next;
        }
        current->next = temp->next;
    }
    free(temp);
    return t;
}

bool is_root(tree_t *t, int node)
{
    return (t->val) == node;
}

bool is_leaf(tree_t *t, int val)
{
    return (find_address(t, val) != NULL) && (find_address(t, val)->depth == NULL);
}

void siblings(tree_t *t, int val)
{
    tree_t *parent = find_address(t, val)->prev;
    if (parent == NULL)
    {
        printf("\n");
        return;
    }
    tree_t *current = parent->depth;
    while (current != NULL)
    {
        if (current->val == val)
        {
            current = current->next;
            continue;
        }
        printf("%i ", current->val);
        current = current->next;
    }
    printf("\n");
    return;
}

void print_path(tree_t *t, int target, int current)
{
    stack_t *s = NULL;
    tree_t *node_current = find_address(t, current);

    while (node_current != NULL)
    {
        // printf("%i ", node_current->val);
        s = push(s, (int)(node_current->val));
        if (node_current->val == target)
        {
            break;
        }
        node_current = node_current->prev;
    }

    while (!empty(s))
    {
        stack_top(s);
        s = pop(s);
    }
    printf("\n");
}

int path_length(tree_t *t, int target, int current)
{
    if (current == target)
    {
        return 1;
    }
    tree_t *node = find_address(t, current);
    if (node == NULL || node->prev == NULL)
    {
        return 0;
    }
    int i = path_length(t, target, node->prev->val);
    if (i > 0)
    {
        return ++i;
    }
    return 0;
}

void ancestor(tree_t *t, int val)
{
    print_path(t, t->val, val);
}

void descendant(tree_t *t, int val)
{
    // use dfs
    tree_t *node = find_address(t, val);
    bfs(node);
    printf("\n");
}
