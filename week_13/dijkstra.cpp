#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX

class Grpah
{
private:
    int num_vertices;
    vector<vector<int>> adjMatrix;

    void dfshelp(int vertex, vector<bool> &visited)
    {
        visited[vertex] = true;
        cout << vertex << " ";

        for (int i = 0; i < num_vertices; ++i)
        {
            if (adjMatrix[vertex][i] != 0 && !visited[i])
            {
                dfshelp(i, visited);
            }
        }
    }

public:
    Grpah(int V) : num_vertices(V), adjMatrix(V, vector<int>(V, 0)) {}

    void addEdge(int src, int dest, int wight)
    {
        adjMatrix[src][dest] = wight;
        adjMatrix[dest][src] = wight; // non directed
    }
    void visalize()
    {
        cout << "  ";
        for (int i = 0; i < num_vertices; ++i)
        {
            cout << i << " ";
        }
        cout << endl;
        for (auto i = 0; i < num_vertices; ++i)
        {
            cout << i << " ";
            for (auto j = 0; j < num_vertices; ++j)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<int> Dijkstra(int start)
    {
        vector<int> distance(num_vertices, INF);
        vector<bool> visited(num_vertices, false);

        distance[start] = 0;

        for (int count = 0; count < num_vertices - 1; ++count)
        {
            int minDistance = INF, u = -1;
            for (int v = 0; v < num_vertices; ++v)
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
            for (int v = 0; v < num_vertices; ++v)
            {
                if (!visited[v] && adjMatrix[u][v] != 0 && distance[u] != INF && distance[u] + adjMatrix[u][v] < distance[v])
                {
                    distance[v] = distance[u] + adjMatrix[u][v];
                }
            }
        }
        return distance;
    }
};

int main()
{
    int n, m, p;
    cin >> n >> m >> p;
    Grpah graph(n);

    int start, end, wight;
    for (int i = 0; i < m; ++i)
    {
        cin >> start >> end >> wight;
        graph.addEdge(start, end, wight);
    }
    int source, target;
    for (int i = 0; i < p; ++i)
    {

        cin >> source >> target;
        vector<int> distances = graph.Dijkstra(source);
        if (distances[target] != INF)
        {
            cout << distances[target] << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}