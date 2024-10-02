#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int numVertices;
    int **adjMatrix;
} Graph;

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
    // graph->adjMatrix[dest][src] = 1; // non directed
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

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

int main()
{
    Graph *graph = createGraph(5);
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 4, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 1);

    visualize(graph);
    freeGraph(graph);
    return 0;
}
