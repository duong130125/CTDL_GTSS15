#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Graph
{
    int V;
    int adj[MAX][MAX];
} Graph;

typedef struct Queue
{
    int items[MAX];
    int front, rear;
} Queue;

void initGraph(Graph *g, int vertices)
{
    g->V = vertices;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; i < vertices; j++)
        {
            g->adj[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int src, int dest)
{
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1;
}

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue *q)
{
    return q->rear == -1;
}

int enqueue(Queue *q, int value)
{
    if (q->rear == MAX - 1)
    {
        return;
    }
    q->items[++(q->rear)] = value;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }
    return q->items[(q->front)++];
}

void BFS(Graph *g, int start)
{
    int visited[MAX] = {0};
    Queue q;
    initQueue(&q);
    visited[start] = 1;
    enqueue(&q, start);
    while (!isEmpty(&q))
    {
        int current = dequeue(&q);
        printf("%d", current);
        for (int i = 0; i < g->V; i++)
        {
            if (g->adj[current][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
}

int main()
{
    Graph g;
    int vertices = 5;
    return 0;
}