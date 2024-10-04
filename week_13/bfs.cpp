#include <bits/stdc++.h>

using namespace std;

#define inf INFINITY

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
        adjMatrix[dest][src] = 1; // non directed
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
    void bfs(int startNode)
    {
        vector<bool> visited(num_vertices, false);
        queue<int> q;

        visited[startNode] = true; // Mark start node as visited
        q.push(startNode);         // Push start node to queue

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            cout << current << " ";
            for (int i = 0; i < num_vertices; ++i)
            {
                if (adjMatrix[current][i] != 0 && !visited[i])
                {
                    visited[i] = true; // Mark as visited
                    q.push(i);         // Add to queue
                }
            }
        }
        cout << endl;
    }

    void dfs(int startNode)
    {
        vector<bool> visited(num_vertices, false);
        dfshelp(startNode, visited);
    }

    int Dijkstra(int start, int end)
    {
    }
};

int main()
{
    int n, m, p;
    // n คือจำนวน node
    // m คือ จำนวนเส้นเชื่อม
    // p คือ จำนวนคู่ของ node
    cin >> n >> m >> p;
    Grpah graph(n);

    int start, end, wight;
    for (int i = 0; i < m; ++i)
    {
        cin >> start >> end >> wight;
        graph.addEdge(start, end, wight);
    }

    graph.visalize();
    // graph.dfs(startNode);
    return 0;
}