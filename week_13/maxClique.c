#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int numVertices;
    int **adjacencyMatrix;
} Graph;

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjacencyMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacencyMatrix[i] = (int *)calloc(vertices, sizeof(int));
    }
    return graph;
}

void addEdge(Graph *graph, int vertex1, int vertex2)
{
    graph->adjacencyMatrix[vertex1][vertex2] = 1;
    graph->adjacencyMatrix[vertex2][vertex1] = 1;
}

void bronKerbosch(int *currentClique, int currentCliqueSize, int *potentialVertices, int potentialVerticesSize, int *excludedVertices, int excludedVerticesSize, Graph *graph, int **cliques, int *cliqueSizes, int *cliqueCount)
{
    if (potentialVerticesSize == 0 && excludedVerticesSize == 0)
    {
        cliques[*cliqueCount] = (int *)malloc(currentCliqueSize * sizeof(int));
        for (int i = 0; i < currentCliqueSize; i++)
        {
            cliques[*cliqueCount][i] = currentClique[i];
        }
        cliqueSizes[*cliqueCount] = currentCliqueSize;
        (*cliqueCount)++;
        return;
    }

    for (int i = 0; i < potentialVerticesSize; i++)
    {
        int vertex = potentialVertices[i];
        currentClique[currentCliqueSize] = vertex;
        currentCliqueSize++;

        int newPotentialVertices[graph->numVertices];
        int newPotentialVerticesSize = 0;
        int newExcludedVertices[graph->numVertices];
        int newExcludedVerticesSize = 0;

        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->adjacencyMatrix[vertex][j] == 1)
            {
                int foundInPotential = 0;
                for (int k = 0; k < potentialVerticesSize; k++)
                {
                    if (potentialVertices[k] == j)
                    {
                        foundInPotential = 1;
                        break;
                    }
                }
                if (foundInPotential)
                {
                    newPotentialVertices[newPotentialVerticesSize++] = j;
                }
                int foundInExcluded = 0;
                for (int k = 0; k < excludedVerticesSize; k++)
                {
                    if (excludedVertices[k] == j)
                    {
                        foundInExcluded = 1;
                        break;
                    }
                }
                if (foundInExcluded)
                {
                    newExcludedVertices[newExcludedVerticesSize++] = j;
                }
            }
        }

        bronKerbosch(currentClique, currentCliqueSize, newPotentialVertices, newPotentialVerticesSize, newExcludedVertices, newExcludedVerticesSize, graph, cliques, cliqueSizes, cliqueCount);

        currentCliqueSize--;
        excludedVertices[excludedVerticesSize++] = vertex;

        for (int j = i; j < potentialVerticesSize - 1; j++)
        {
            potentialVertices[j] = potentialVertices[j + 1];
        }
        potentialVerticesSize--;
        i--;
    }
}

int main()
{
    int numVertices, numEdges;
    scanf("%d %d", &numVertices, &numEdges);

    Graph *graph = createGraph(numVertices);
    for (int i = 0; i < numEdges; i++)
    {
        int vertex1, vertex2;
        scanf("%d %d", &vertex1, &vertex2);
        addEdge(graph, vertex1, vertex2);
    }

    int potentialVertices[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        potentialVertices[i] = i;
    }

    int currentClique[numVertices];
    int excludedVertices[numVertices];
    int *cliques[numVertices * numVertices];
    int cliqueSizes[numVertices * numVertices];
    int cliqueCount = 0;

    bronKerbosch(currentClique, 0, potentialVertices, numVertices, excludedVertices, 0, graph, cliques, cliqueSizes, &cliqueCount);

    int maxCliqueSize = 0;
    for (int i = 0; i < cliqueCount; i++)
    {
        if (cliqueSizes[i] > maxCliqueSize)
        {
            maxCliqueSize = cliqueSizes[i];
        }
    }

    printf("%d\n", maxCliqueSize);

    for (int i = 0; i < cliqueCount; i++)
    {
        free(cliques[i]);
    }

    for (int i = 0; i < numVertices; i++)
    {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph);

    return 0;
}
