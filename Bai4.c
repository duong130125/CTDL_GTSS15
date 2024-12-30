#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

Node *adjList[MAX];
bool visited[MAX];
bool recursionStack[MAX];

void addEdge(int u, int v)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

bool dfs(int vertex)
{
    visited[vertex] = true;
    recursionStack[vertex] = true;

    Node *temp = adjList[vertex];
    while (temp != NULL)
    {
        int adjacent = temp->vertex;

        if (!visited[adjacent])
        {
            if (dfs(adjacent))
            {
                return true;
            }
        }
        else if (recursionStack[adjacent])
        {
            return true;
        }

        temp = temp->next;
    }

    recursionStack[vertex] = false;
    return false;
}

bool isCyclic(int V)
{
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
        recursionStack[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            if (dfs(i))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int V, E;
    printf("Nhập số đỉnh: ");
    scanf("%d", &V);

    printf("Nhập số cạnh: ");
    scanf("%d", &E);

    // Khởi tạo danh sách kề
    for (int i = 0; i < V; i++)
    {
        adjList[i] = NULL;
    }

    printf("Nhập danh sách cạnh (u v):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    if (isCyclic(V))
    {
        printf("Đồ thị có chu trình\n");
    }
    else
    {
        printf("Đồ thị không có chu trình\n");
    }

    return 0;
}
