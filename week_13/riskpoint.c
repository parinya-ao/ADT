#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000000000

typedef struct
{
    int num_vertices;
    int **adjMatrix;
} Graph;

Graph *create_graph(int V)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->num_vertices = V;
    g->adjMatrix = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        g->adjMatrix[i] = (int *)calloc(V, sizeof(int));
    }
    return g;
}

void add_edge(Graph *g, int u, int v)
{
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}

void dfs_articulation_points(Graph *g, int u, bool *visited, int *discovery_time,
                             int *low, int *time, int parent, bool *is_ap)
{
    int children = 0;
    visited[u] = true;
    discovery_time[u] = low[u] = ++(*time);

    for (int v = 0; v < g->num_vertices; ++v)
    {
        if (g->adjMatrix[u][v] == 1)
        {
            if (!visited[v])
            {
                children++;
                dfs_articulation_points(g, v, visited, discovery_time, low, time, u, is_ap);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];
                if (parent != INF && low[v] >= discovery_time[u])
                {
                    is_ap[u] = true;
                }
            }
            else if (v != parent)
            {
                low[u] = (low[u] < discovery_time[v]) ? low[u] : discovery_time[v];
            }
        }
    }

    if (parent == INF && children > 1)
    {
        is_ap[u] = true;
    }
}

void find_articulation_points(Graph *g)
{
    int *discovery_time = (int *)calloc(g->num_vertices, sizeof(int));
    int *low = (int *)calloc(g->num_vertices, sizeof(int));
    bool *visited = (bool *)calloc(g->num_vertices, sizeof(bool));
    bool *is_ap = (bool *)calloc(g->num_vertices, sizeof(bool));
    int time = 0;
    int parent = INF;

    for (int i = 0; i < g->num_vertices; ++i)
    {
        if (!visited[i])
        {
            dfs_articulation_points(g, i, visited, discovery_time, low, &time, parent, is_ap);
        }
    }

    // แสดงผล articulation points
    for (int i = 0; i < g->num_vertices; ++i)
    {
        if (is_ap[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(discovery_time);
    free(low);
    free(visited);
    free(is_ap);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Graph *g = create_graph(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(g, u, v);
    }

    find_articulation_points(g);

    for (int i = 0; i < n; i++)
    {
        free(g->adjMatrix[i]);
    }
    free(g->adjMatrix);
    free(g);

    return 0;
}
