#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
    int data;
    vector<int> adjacentList;
    Node(int data_): data(data_){}
};


class Graph{
private:
    vector<Node> vertexList;

public:
    Graph(int num_vertices){
        vertexList.resize(num_vertices, Node(-1));
    }

    void addEdge(int src, int dest){
        vertexList[src].adjacentList.push_back(dest);
        vertexList[dest].adjacentList.push_back(src);
    }

    void DFS(int start_vertex){
        // Record visited nodes(vertices)
        vector<bool> visited(vertexList.size(), false);
        
        // Use stack data-structure for DFS
        stack<int> stack;

        // Start with starter vertex
        stack.push(start_vertex);
        // printStack(stack);

        // DFS Traversal
        while(!stack.empty()){
            // Get most recent vertex
            int currentVertex = stack.top();
            stack.pop();

            if(!visited[currentVertex]){
                cout<< "\n\n===========vertex: " << currentVertex<<"  ===========\n";
            
                // Make unvisited current vertex as 'visited'
                visited[currentVertex] = true;

                // Add all adjacent nodes to stack
                int numAdjacents = vertexList[currentVertex].adjacentList.size(); 
                for(int adj=0; adj<numAdjacents; adj++){
                    int adjacentNode = vertexList[currentVertex].adjacentList[adj];

                    if(!visited[adjacentNode] and !isExistStack(adjacentNode, stack)){
                        stack.push(adjacentNode);
                        cout<<"\n++ pushing ("<<adjacentNode<<") to the stack.";
                    }
                }
                printStack(stack);
            }
        }
    }

    // Function to print the adjacency list representation of the graph
    void printGraph() {
        for (size_t i = 0; i < vertexList.size(); ++i) {
            cout << "Adjacency list of vertex " << i << ":\n";
            for (int nodeIndex : vertexList[i].adjacentList) {
                cout << "-> " << nodeIndex << " ";
            }
            cout << endl;
        }
    }
    
    void printStack(stack<int> myStack){
        cout<<"\nStack:(";
        while(!myStack.empty())
        {
            cout << " ";
            int w = myStack.top();
            cout << w;
            myStack.pop();
        }
        cout<<" ) ";
    }

    bool isExistStack(int var, stack<int> myStack){
        for(int i=0; i<myStack.size(); i++){
            int ele = myStack.top();
            if (ele==var) return true;
            myStack.pop();
        }
        return false;
    }

    
};



int main(){
    Graph graph(5);
    // Add some edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.DFS(0);
    return 0;
}
