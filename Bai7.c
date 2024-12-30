#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int adjMatrix[MAX][MAX];
bool visited[MAX];

void dfs(int vertex, int V)
{
    visited[vertex] = true;
    for (int i = 0; i < V; i++)
    {
        if (adjMatrix[vertex][i] == 1 && !visited[i])
        {
            dfs(i, V);
        }
    }
}

bool isConnected(int V)
{
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    dfs(0, V);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int V, E;
    printf("Nhập số đỉnh: ");
    scanf("%d", &V);

    printf("Nhập số cạnh: ");
    scanf("%d", &E);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Nhập danh sách cạnh (u v):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    if (isConnected(V))
    {
        printf("Đồ thị liên thông\n");
    }
    else
    {
        printf("Đồ thị không liên thông\n");
    }

    return 0;
}