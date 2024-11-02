// Find the min shortest path using DIjsktra Algorithm
#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX 10 // Maximum number of vertices

// A function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[], int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// A function to print the shortest path distances
void printSolution(int dist[], int V)
{
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[MAX][MAX], int src, int V)
{
    int dist[MAX];   // Array to store shortest distance from source to each vertex
    int sptSet[MAX]; // Array to keep track of vertices included in shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = 0; // Set all vertices as not yet included in shortest path tree
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the vertex with the minimum distance value
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist[] for adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
        {
            // Update dist[v] if it's not in the sptSet, there's an edge from u to v,
            // and total distance to v through u is less than current dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    // Print the calculated shortest distances
    printSolution(dist, V);
}

int main()
{
    int V;               // Number of vertices in the graph
    int graph[MAX][MAX]; // Adjacency matrix representation of the graph

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Input the graph (adjacency matrix)
    printf("Enter the adjacency matrix (use 0 for no edge between vertices):\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src, V);

    return 0;
}