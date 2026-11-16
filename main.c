
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int u, v, w;
} Edge;

int FindMinCost(int vertices, int minCost[vertices], bool included[vertices]) {
    int minimum = INT_MAX;
    int minVertex = -1;

    for(int i = 0; i < vertices; i++) {
        if(included[i] == false && minCost[i] < minimum) {
            minimum = minCost[i];
            minVertex = i;
        }
    }

    return minVertex;
}

int FindParent(int parent[], int vertex) {
    if(parent[vertex] == vertex) {
        return vertex;
    }

    return FindParent(parent, parent[vertex]);
}

bool FindTreePath(int vertices, int tree[vertices][vertices],
                  int source, int destination, int path[], int *cost) {

    int queue[vertices];
    int parent[vertices];
    bool visited[vertices];

    for(int i = 0; i < vertices; i++) {
        parent[i] = -1;
        visited[i] = false;
    }

    int front = 0, rear = 0;

    queue[rear++] = source;
    visited[source] = true;

    while(front < rear) {
        int current = queue[front++];

        if(current == destination) {
            break;
        }

        for(int j = 0; j < vertices; j++) {
            if(tree[current][j] != 0 && visited[j] == false) {
                visited[j] = true;
                parent[j] = current;
                queue[rear++] = j;
            }
        }
    }

    if(visited[destination] == false) {
        return false;
    }

    int temp[vertices];
    int count = 0;
    int current = destination;

    while(current != -1) {
        temp[count++] = current;
        current = parent[current];
    }

    for(int i = 0; i < count; i++) {
        path[i] = temp[count - 1 - i];
    }

    *cost = 0;

    for(int i = 0; i < count - 1; i++) {
        *cost += tree[path[i]][path[i + 1]];
    }

    return true;
}

void PrintPath(int vertices, int path[], int destination, int cost) {
    int count = 0;

    while(count < vertices && path[count] != destination) {
        count++;
    }

    count++;

    for(int i = 0; i < count; i++) {
        printf("%d", path[i]);

        if(i < count - 1) {
            printf(" -> ");
        }
    }

    printf(" (Cost: %d)\n", cost);
}

void Dijkstra(int vertices, int graph[vertices][vertices],
              int source, int destination) {

    int distance[vertices];
    int parent[vertices];
    bool included[vertices];

    for(int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        included[i] = false;
    }

    distance[source] = 0;

    for(int i = 0; i < vertices; i++) {

        int minimum = INT_MAX;
        int currentVertex = -1;

        for(int j = 0; j < vertices; j++) {
            if(included[j] == false && distance[j] < minimum) {
                minimum = distance[j];
                currentVertex = j;
            }
        }

        if(currentVertex == -1) {
            break;
        }

        included[currentVertex] = true;

        for(int j = 0; j < vertices; j++) {
            if(graph[currentVertex][j] != 0 &&
               included[j] == false &&
               distance[currentVertex] != INT_MAX &&
               distance[currentVertex] + graph[currentVertex][j] < distance[j]) {

                distance[j] = distance[currentVertex] + graph[currentVertex][j];
                parent[j] = currentVertex;
            }
        }
    }

    if(distance[destination] == INT_MAX) {
        printf("Not Possible\n");
        return;
    }

    int temp[vertices];
    int path[vertices];
    int count = 0;
    int current = destination;

    while(current != -1) {
        temp[count++] = current;
        current = parent[current];
    }

    for(int i = 0; i < count; i++) {
        path[i] = temp[count - 1 - i];
    }

    PrintPath(vertices, path, destination, distance[destination]);
}

bool KruskalMST(int vertices, Edge edges[], int edgeCount,
                int tree[vertices][vertices]) {

    int parent[vertices];

    for(int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    for(int i = 0; i < edgeCount - 1; i++) {
        for(int j = 0; j < edgeCount - i - 1; j++) {
            if(edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int count = 0;

    for(int i = 0; i < edgeCount; i++) {

        int parentU = FindParent(parent, edges[i].u);
        int parentV = FindParent(parent, edges[i].v);

        if(parentU != parentV) {

            tree[edges[i].u][edges[i].v] = edges[i].w;
            tree[edges[i].v][edges[i].u] = edges[i].w;

            parent[parentU] = parentV;

            count++;

            if(count == vertices - 1) {
                break;
            }
        }
    }

    return count == vertices - 1;
}

bool PrimMST(int vertices, int graph[vertices][vertices],
             int tree[vertices][vertices]) {

    int parents[vertices];
    int minCost[vertices];
    bool included[vertices];

    for(int i = 0; i < vertices; i++) {
        parents[i] = -1;
        minCost[i] = INT_MAX;
        included[i] = false;
    }

    minCost[0] = 0;

    for(int i = 0; i < vertices; i++) {

        int CurrentVertex = FindMinCost(vertices, minCost, included);

        if(CurrentVertex == -1) {
            return false;
        }

        included[CurrentVertex] = true;

        for(int j = 0; j < vertices; j++) {
            if(graph[CurrentVertex][j] != 0 &&
               included[j] == false &&
               graph[CurrentVertex][j] < minCost[j]) {

                minCost[j] = graph[CurrentVertex][j];
                parents[j] = CurrentVertex;
            }
        }
    }

    for(int i = 1; i < vertices; i++) {
        if(parents[i] == -1) {
            return false;
        }

        tree[parents[i]][i] = graph[parents[i]][i];
        tree[i][parents[i]] = graph[i][parents[i]];
    }

    return true;
}

void ShowKruskal(int vertices, Edge edges[], int edgeCount,
                 int source, int destination) {

    int tree[vertices][vertices];
    int path[vertices];
    int cost;

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            tree[i][j] = 0;
        }
    }

    if(KruskalMST(vertices, edges, edgeCount, tree)) {
        if(FindTreePath(vertices, tree, source, destination, path, &cost)) {
            PrintPath(vertices, path, destination, cost);
        }
        else {
            printf("Not Possible\n");
        }
    }
    else {
        printf("Not Possible\n");
    }
}

void ShowPrim(int vertices, int graph[vertices][vertices],
              int source, int destination) {

    int tree[vertices][vertices];
    int path[vertices];
    int cost;

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            tree[i][j] = 0;
        }
    }

    if(PrimMST(vertices, graph, tree)) {
        if(FindTreePath(vertices, tree, source, destination, path, &cost)) {
            PrintPath(vertices, path, destination, cost);
        }
        else {
            printf("Not Possible\n");
        }
    }
    else {
        printf("Not Possible\n");
    }
}

int main() {

    FILE *file = fopen("input.txt", "r");

    if(file == NULL) {
        printf("File not found!\n");
        return 1;
    }

    int vertices, edgeCount;

    fscanf(file, "%d %d", &vertices, &edgeCount);

    Edge edges[edgeCount];
    int graph[vertices][vertices];

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    for(int i = 0; i < edgeCount; i++) {
        fscanf(file, "%d %d %d",
               &edges[i].u, &edges[i].v, &edges[i].w);

        graph[edges[i].u][edges[i].v] = edges[i].w;
        graph[edges[i].v][edges[i].u] = edges[i].w;
    }

    int source, destination;
    int removeU, removeV;

    fscanf(file, "%d %d", &source, &destination);
    fscanf(file, "%d %d", &removeU, &removeV);

    fclose(file);

    printf("Shortest Path: ");
    Dijkstra(vertices, graph, source, destination);

    Edge kruskalEdges[edgeCount];

    for(int i = 0; i < edgeCount; i++) {
        kruskalEdges[i] = edges[i];
    }

    printf("Kruskal Path:   ");
    ShowKruskal(vertices, kruskalEdges, edgeCount, source, destination);

    printf("Prim Path:      ");
    ShowPrim(vertices, graph, source, destination);

    printf("After Removing Edge (%d,%d):\n", removeU, removeV);

    int newEdgeCount = 0;
    Edge newEdges[edgeCount];
    int newGraph[vertices][vertices];

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            newGraph[i][j] = 0;
        }
    }

    for(int i = 0; i < edgeCount; i++) {

        if(!((edges[i].u == removeU && edges[i].v == removeV) ||
             (edges[i].u == removeV && edges[i].v == removeU))) {

            newEdges[newEdgeCount] = edges[i];

            newGraph[edges[i].u][edges[i].v] = edges[i].w;
            newGraph[edges[i].v][edges[i].u] = edges[i].w;

            newEdgeCount++;
        }
    }
    printf("Updated Shortest Path: ");
    Dijkstra(vertices, newGraph, source, destination);

    printf("Updated Kruskal Path:  ");
    ShowKruskal(vertices, newEdges, newEdgeCount, source, destination);

    printf("Updated Prim Path:     ");
    ShowPrim(vertices, newGraph, source, destination);
    return 0;
}
