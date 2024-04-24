#include <iostream>

using namespace std;

// Define a structure for a node in the adjacency list
struct Node {
    int data;
    Node* next;
};

// Define a structure for the adjacency list
struct Graph {
    int V;          // Number of vertices
    Node** adjList; // Array of adjacency lists
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = new Graph();
    graph->V = V;
    graph->adjList = new Node*[V];
    for (int i = 0; i < V; ++i)
        graph->adjList[i] = nullptr;
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Depth First Search
void DFSUtil(Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    Node* temp = graph->adjList[v];
    while (temp != nullptr) {
        int adjVertex = temp->data;
        if (!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// Depth First Search traversal
void DFS(Graph* graph, int startVertex) {
    // Mark all vertices as not visited
    bool* visited = new bool[graph->V];
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;

    // Call the recursive helper function to print DFS traversal
    DFSUtil(graph, startVertex, visited);

    delete[] visited;
}

int main() {
    // Create a graph
    int V = 5;
    Graph* graph = createGraph(V);

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    cout << "Depth First Traversal (starting from vertex 0): ";
    DFS(graph, 0);
    cout << endl;

    return 0;
}
