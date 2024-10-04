#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
public:
    int numVertices;
    vector<vector<int>> adjacencyMatrix;

    Graph(int vertices) : numVertices(vertices)
    {
        adjacencyMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    void addEdge(int vertex1, int vertex2)
    {
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1;
    }
};

void bronKerbosch(vector<int> &currentClique, vector<int> &potentialVertices, vector<int> &excludedVertices, const Graph &graph, vector<vector<int>> &cliques)
{
    if (potentialVertices.empty() && excludedVertices.empty())
    {
        cliques.push_back(currentClique);
        return;
    }

    vector<int> potentialVerticesCopy = potentialVertices;
    for (int vertex : potentialVerticesCopy)
    {
        vector<int> newClique = currentClique;
        newClique.push_back(vertex);

        vector<int> newPotentialVertices, newExcludedVertices;
        for (int i = 0; i < graph.numVertices; i++)
        {
            if (graph.adjacencyMatrix[vertex][i] == 1)
            {
                if (find(potentialVertices.begin(), potentialVertices.end(), i) != potentialVertices.end())
                {
                    newPotentialVertices.push_back(i);
                }
                if (find(excludedVertices.begin(), excludedVertices.end(), i) != excludedVertices.end())
                {
                    newExcludedVertices.push_back(i);
                }
            }
        }

        bronKerbosch(newClique, newPotentialVertices, newExcludedVertices, graph, cliques);

        potentialVertices.erase(remove(potentialVertices.begin(), potentialVertices.end(), vertex), potentialVertices.end());
        excludedVertices.push_back(vertex);
    }
}

int main()
{
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    Graph graph(numVertices);
    for (int i = 0; i < numEdges; i++)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        graph.addEdge(vertex1, vertex2);
    }

    vector<int> potentialVertices(numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        potentialVertices[i] = i;
    }

    vector<int> currentClique, excludedVertices;
    vector<vector<int>> cliques;

    bronKerbosch(currentClique, potentialVertices, excludedVertices, graph, cliques);

    int maxCliqueSize = 0;
    for (const auto &clique : cliques)
    {
        maxCliqueSize = max(maxCliqueSize, static_cast<int>(clique.size()));
    }

    cout << maxCliqueSize << endl;

    return 0;
}
