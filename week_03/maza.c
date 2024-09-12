#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define max 101

void showmaze(char maze[max][max], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", maze[i]);
    }
}

bool check(char maze[max][max], int n, int x, int y, bool visited[][max])
{
    if (x >= 0 && x < n && y >= 0 && y < n)
    {
        if (!visited[x][y] && maze[x][y] != '#')
        {
            return true;
        }
    }
    return false;
}

bool traverseMaze(char maze[max][max], int n, int x, int y, bool visited[][max])
{
    if (maze[x][y] == 'G')
    {
        return true;
    }

    if (check(maze, n, x, y, visited))
    {
        // printf("(%.i,%.i)\n", x+1, y+1);
        // เช็คว่าเดินไปแล้ว
        visited[x][y] = true;

        // ทิศเหนือ
        if (traverseMaze(maze, n, x, y + 1, visited))
        {
            return true;
        }
        // ทิศไต้
        if (traverseMaze(maze, n, x, y - 1, visited))
        {
            return true;
        }
        // ทิศออก
        if (traverseMaze(maze, n, x + 1, y, visited))
        {
            return true;
        }
        // ทิศคก
        if (traverseMaze(maze, n, x - 1, y, visited))
        {
            return true;
        }

        visited[x][y] = false;
    }
    return false;
}

void dfs(char maze[max][max], int n)
{
    bool visited[n][max];
    memset(visited, false, sizeof(visited));

    // check start
    int start_x = 0;
    int start_y = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (maze[i][j] == 'S')
            {
                start_x = i;
                start_y = j;
            }
        }
    }
    // printf("%i %i", start_x, start_y);
    if (traverseMaze(maze, n, start_x, start_y, visited))
    {

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (visited[i][j])
                {
                    maze[i][j] = '.';
                }
            }
        }
    }
    maze[start_x][start_y] = 'S';
    showmaze(maze, n);
}

int main()
{
    char maze[max][max];
    int n;
    scanf("%i", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        fgets(maze[i], 101, stdin);
        maze[i][strcspn(maze[i], "\n")] = '\0';
    }
    dfs(maze, n);
    // showmaze(maze, n);

    return 0;
}