#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    Node **adjLists;
    bool *visited;
} Graph;

Node *createNode(int vertex)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(Graph *graph, int vertex)
{
    graph->visited[vertex] = true;

    Node *temp = graph->adjLists[vertex];
    while (temp)
    {
        int connectedVertex = temp->vertex;
        if (!graph->visited[connectedVertex])
        {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

bool isConnected(Graph *graph)
{
    DFS(graph, 0);

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (!graph->visited[i])
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

    Graph *graph = createGraph(V);

    printf("Nhập danh sách cạnh (u, v):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (isConnected(graph))
    {
        printf("\nĐồ thị liên thông\n");
    }
    else
    {
        printf("\nĐồ thị không liên thông\n");
    }

    for (int i = 0; i < V; i++)
    {
        Node *temp = graph->adjLists[i];
        while (temp)
        {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);

    return 0;
}
