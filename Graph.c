#include <stdio.h>
#include <stdlib.h>
// Maximum number of vertices and edges
#define MAX 100
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct queue
{
    Node *front;
    Node *rear;
} queue;

void enqueue(queue *q, int x)
{
    Node *t;
    t = malloc(sizeof(Node));
    if (t == NULL)
        printf("Queue is FUll\n");
    else
    {
        t->data = x;
        t->next = NULL;
        if (q->front == NULL)
            q->front = q->rear = t;
        else
        {
            q->rear->next = t;
            q->rear = t;
        }
    }
}

int dequeue(queue *q)
{
    int x = -1;
    Node *t;

    if (q->front == NULL)
        printf("Queue is Empty\n");
    else
    {
        x = q->front->data;
        t = q->front;
        q->front = q->front->next;
        free(t);
    }
    return x;
}

int isEmpty(queue *q)
{
    return q->front == NULL;
}
// Function to create Adjacency Matrix
void createAdjMatrix(int Adj[][MAX], int v, int arr[][2], int e)
{
    // Initialise all values in Adjacency Matrix to zero
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            Adj[i][j] = 0;
        }
    }
    // Traverse the array of edges
    for (int i = 0; i < e; i++)
    {
        int x = arr[i][0];
        int y = arr[i][1];

        // Update the value to 1 to represent the edge connection
        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}
// Function to print the created Adjacency Matrix
void printAdjMatrix(int Adj[][MAX], int v)
{
    // Traverse the Adjacency Matrix
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            printf("%d ", Adj[i][j]);
        }
        printf("\n");
    }
}

void BFS(int Adj[][MAX], int start, int n)
{
    queue *q = malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    int i = start, j;
    int visited[MAX] = {0};
    printf("%d ", i);
    visited[i] = 1;
    enqueue(q, i);
    while (!isEmpty(q))
    {
        i = dequeue(q);
        for (j = 1; j <= n; j++)
        {
            if (Adj[i][j] == 1 && visited[j] == 0)
            {
                printf("%d ", j);
                visited[j] = 1;
                enqueue(q, j);
            }
        }
    }
}

void DFS(int Adj[][MAX], int start, int n)
{
    static int visited[MAX] = {0};
    int j;
    if (visited[start] == 0)
    {
        printf("%d ", start);
        visited[start] = 1;
        for (j = 1; j <= n; j++)
        {
            if (Adj[start][j] == 1 && visited[j] == 0)
                DFS(Adj, j, n);
        }
    }
}

int Degree(int Adj[][MAX], int v, int n)
{
    int degree = 0;
    int i;
    for (i = 1; i <= v; i++)
    {
        if (Adj[n][i] == 1)
        {
            degree++;
        }
    }
    return degree;
}

int main()
{
    Node *front = NULL, *rear = NULL;
    int v, e, n;
    int choice;
    int start;
    int degree = 0;
    int Adj[MAX][MAX];
    while (1)
    {
        printf("******MAIN MENU*******");
        printf("\n1.Adjacency Matrix");
        printf("\n2.BFS");
        printf("\n3.DFS");
        printf("\n4.Degree");
        printf("\n5.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the number of vertices: ");
            scanf("%d", &v);
            printf("Enter the number of edges: ");
            scanf("%d", &e);
            // Edge connections
            int arr[MAX][2];
            printf("Enter the edge connections:\n");
            for (int i = 0; i < e; i++)
            {
                scanf("%d%d", &arr[i][0], &arr[i][1]);
            }
            // Function call to create Adjacency Matrix
            createAdjMatrix(Adj, v, arr, e);
            // Print Adjacency Matrix
            printf("Adjacency Matrix:\n");
            printAdjMatrix(Adj, v);
            break;
        case 2:
            printf("Enter the starting node: ");
            scanf("%d", &start);
            BFS(Adj, start, v);
            printf("\n");
            break;
        case 3:
            printf("Enter the starting node: ");
            scanf("%d", &start);
            DFS(Adj, start, v);
            printf("\n");
            break;
        case 4:
            printf("Enter vertex: ");
            scanf("%d", &n);
            degree = Degree(Adj, v, n);
            printf("%d", degree);
            printf("\n");
            break;
        case 5:
            exit(1);
            break;
        default:
            printf("\nWrong choice,enter different choice\n");
            break;
        }
    }
    return 0;
}
