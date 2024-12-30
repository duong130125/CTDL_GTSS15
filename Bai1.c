#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Cấu trúc cho danh sách kề
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    Node **adjLists;
    int *visited;
} Graph;

// Hàng đợi
typedef struct Queue
{
    int items[MAX];
    int front;
    int rear;
} Queue;

// Hàm tạo node mới
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Hàm tạo đồ thị
Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Hàm thêm cạnh vào đồ thị
void addEdge(Graph *graph, int src, int dest)
{
    // Thêm cạnh từ src đến dest
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Thêm cạnh từ dest đến src (vì đồ thị vô hướng)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Hàm tạo hàng đợi
Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Kiểm tra hàng đợi có rỗng không
int isEmpty(Queue *q)
{
    return q->rear == -1;
}

// Thêm phần tử vào hàng đợi
void enqueue(Queue *q, int value)
{
    if (q->rear == MAX - 1)
        printf("\nHàng đợi đầy\n");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Xóa phần tử khỏi hàng đợi
int dequeue(Queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("\nHàng đợi rỗng\n");
        return -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            q->front = q->rear = -1;
        }
        return item;
    }
}

// Hàm duyệt BFS
void bfs(Graph *graph, int startVertex)
{
    Queue *q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("Thứ tự duyệt BFS: ");
    while (!isEmpty(q))
    {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node *temp = graph->adjLists[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main()
{
    int V, E, start;
    printf("Nhập số đỉnh: ");
    scanf("%d", &V);
    printf("Nhập số cạnh: ");
    scanf("%d", &E);

    Graph *graph = createGraph(V);

    printf("Nhập danh sách các cạnh (dạng u v):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    printf("Nhập đỉnh bắt đầu: ");
    scanf("%d", &start);

    bfs(graph, start);

    return 0;
}
