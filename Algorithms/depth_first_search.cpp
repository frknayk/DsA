#include<iostream>
using namespace std;

const int MAX_NODES = 6;

/*
DFS Algorithm
- Step 1: Insert the root node or starting node of a tree or a graph in the stack.
- Step 2: Pop the top item from the stack and add it to the visited list.
- Step 3: Find all the adjacent nodes of the node marked visited and 
add the ones that are not yet visited, to the stack.
- Step 4: Repeat steps 2 and 3 until the stack is empty.
*/


// class DFS{



// };


// Structure to represent a stack
struct Stack {
    int items[MAX_NODES];
    int top;

    Stack() {
        top = -1;
    }

    void push(int item) {
        if (top == MAX_NODES - 1) {
            std::cout << "Stack Overflow!\n";
            return;
        }
        items[++top] = item;
    }

    int pop() {
        if (top == -1) {
            std::cout << "Stack Underflow!\n";
            return -1; // Return an invalid value
        }
        return items[top--];
    }

    bool isEmpty() {
        return (top == -1);
    }
};

struct Edge{
    int source;
    int destination;
};

// Implementation of DFS without Stack() since recursion already using the 'stack' 
void depthFirstSearch(
    int graph[MAX_NODES][MAX_NODES], int start_node, bool visited[MAX_NODES], int num_nodes) {
    // Make first node visited
    visited[start_node] = true;
    std::cout << start_node << " ";
    // Visit all adjacent nodes of the current node
    for(int i=0; i<num_nodes;i++){
        if (!visited[i] && graph[start_node][i]){
            depthFirstSearch(graph, i, visited, num_nodes);
        }
    }
};


int main() {
    // Define the graph as pairs of nodes (edges)
    Edge edges[] = {
        {0, 1}, {0, 2},
        {1, 0}, {1, 3}, {1, 4},
        {2, 0}, {2, 4},
        {3, 1}, {3, 4}, {3, 5},
        {4, 1}, {4, 2}, {4, 5},
        {5, 3}, {5, 4}
    };
    // Initialize adjacency matrix with zeros
    int graph[MAX_NODES][MAX_NODES] = {};
    // Populate the adjacency matrix based on the edges
    for (const auto& edge: edges){
        graph[edge.source][edge.destination] = 1;
        graph[edge.destination][edge.source] = 1;
    }
    // Array to track visited nodes during DFS
    bool visited[MAX_NODES] = {false};
    // Start DFS
    std::cout<<"Depth First Search starting from node 0: ";
    depthFirstSearch(graph, 0, visited, MAX_NODES);
    return 0;
}
