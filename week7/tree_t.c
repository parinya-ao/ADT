#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.c"

int main()
{
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d %d", &parent, &child);
            t = attach(t, parent, child);
            break;
        case 2:
            scanf("%d", &node);
            t = detach(t, node);
            break;
        case 3: // pass
            scanf("%d", &node);
            printf("%d\n", search(t, node));
            break;
        case 4: // pass
            scanf("%d", &node);
            printf("%d\n", degree(t, node));
            break;
        case 5: // pass
            scanf("%d", &node);
            printf("%d\n", is_root(t, node));
            break;
        case 6: // pass
            scanf("%d", &node);
            printf("%d\n", is_leaf(t, node));
            break;
        case 7: // pass
            scanf("%d", &node);
            siblings(t, node);
            break;
        case 8: // passs
            scanf("%d", &node);
            printf("%d\n", depth(t, node));
            break;
        case 9: // pass
            scanf("%d %d", &start, &end);
            print_path(t, start, end);
            break;
        case 10: // pass
            scanf("%d %d", &start, &end);
            printf("%d\n",
                   path_length(t, start, end));
            break;
        case 11: // pass
            scanf("%d", &node);
            ancestor(t, node);
            break;
        case 12: // pass
            scanf("%d", &node);
            descendant(t, node);
            break;
        case 13: // pass
            bfs(t);
            printf("\n");
            break;
        case 14: // pass
            dfs(t);
            printf("\n");
            break;
        case 15: // pass
            print_tree(t);
            break;
        }
    }
    return 0;
}
