#include <iostream>
#include <vector>

#pragma GCC optimize("Ofast")

#define INF 1e9 // ใช้ INF แทนค่าไม่สิ้นสุด

using namespace std;

class Graph
{
public:
    int num_vertices;
    vector<vector<int>> adjMatrix;

    Graph(int V) : num_vertices(V), adjMatrix(V, vector<int>(V, 0)) {}

    void add_edge(int u, int v)
    {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void find_articulation_points()
    {
        vector<int> discovery_time(num_vertices, 0);
        vector<int> low(num_vertices, 0);
        vector<bool> visited(num_vertices, false);
        vector<bool> is_ap(num_vertices, false);
        int time = 0;
        int parent = INF;

        for (int i = 0; i < num_vertices; ++i)
        {
            if (!visited[i])
            {
                dfs_articulation_points(i, visited, discovery_time, low, time, parent, is_ap);
            }
        }

        // แสดงผล articulation points
        for (int i = 0; i < num_vertices; ++i)
        {
            if (is_ap[i])
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }

private:
    void dfs_articulation_points(int u, vector<bool> &visited, vector<int> &discovery_time,
                                 vector<int> &low, int &time, int parent, vector<bool> &is_ap)
    {
        int children = 0;
        visited[u] = true;
        discovery_time[u] = low[u] = ++time;

        for (int v = 0; v < num_vertices; ++v)
        {
            if (adjMatrix[u][v] == 1)
            {
                if (!visited[v])
                {
                    children++;
                    dfs_articulation_points(v, visited, discovery_time, low, time, u, is_ap);

                    low[u] = min(low[u], low[v]);
                    if (parent != INF && low[v] >= discovery_time[u])
                    {
                        is_ap[u] = true;
                    }
                }
                else if (v != parent)
                {
                    low[u] = min(low[u], discovery_time[v]);
                }
            }
        }

        // ถ้า u เป็น root และมีลูกมากกว่า 1, u เป็น articulation point
        if (parent == INF && children > 1)
        {
            is_ap[u] = true;
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    g.find_articulation_points();
    return 0;
}
