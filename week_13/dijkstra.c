#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

typedef struct
{
    int numVertices;
    int **adjMatrix;
} Graph;

void dfshelp(Graph *graph, int vertex, bool *visited)
{
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; ++i)
    {
        if (graph->adjMatrix[vertex][i] != 0 && !visited[i])
        {
            dfshelp(graph, i, visited);
        }
    }
}

Graph *createGraph(int V)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = V;
    graph->adjMatrix = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        graph->adjMatrix[i] = (int *)calloc(V, sizeof(int));
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight; // non directed
}

void visualize(Graph *graph)
{
    printf("  ");
    for (int i = 0; i < graph->numVertices; ++i)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < graph->numVertices; ++i)
    {
        printf("%d ", i);
        for (int j = 0; j < graph->numVertices; ++j)
        {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int *Dijkstra(Graph *graph, int start)
{
    int *distance = (int *)malloc(graph->numVertices * sizeof(int));
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++)
    {
        distance[i] = INF;
        visited[i] = false;
    }

    distance[start] = 0;

    for (int count = 0; count < graph->numVertices - 1; ++count)
    {
        int minDistance = INF, u = -1;
        for (int v = 0; v < graph->numVertices; ++v)
        {
            if (!visited[v] && distance[v] < minDistance)
            {
                minDistance = distance[v];
                u = v;
            }
        }
        if (u == -1)
        {
            break;
        }
        visited[u] = true;
        for (int v = 0; v < graph->numVertices; ++v)
        {
            if (!visited[v] && graph->adjMatrix[u][v] != 0 && distance[u] != INF && distance[u] + graph->adjMatrix[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph->adjMatrix[u][v];
            }
        }
    }
    free(visited);
    return distance;
}

int main()
{
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    Graph *graph = createGraph(n);

    int start, end, weight;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d %d", &start, &end, &weight);
        addEdge(graph, start, end, weight);
    }
    int source, target;
    for (int i = 0; i < p; ++i)
    {
        scanf("%d %d", &source, &target);
        int *distances = Dijkstra(graph, source);
        if (distances[target] != INF)
        {
            printf("%d\n", distances[target]);
        }
        else
        {
            printf("-1\n");
        }
        free(distances);
    }

    for (int i = 0; i < n; i++)
    {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
