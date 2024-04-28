#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node{
    int data;
    vector<int> adjList;
    Node(int data_): data(data_){}
};

class Graph{
private:
    vector<Node> vertexList;
public:
    Graph(int numVertices){
        vertexList.resize(numVertices, Node(-1));
    }

    void addEdge(int src, int dest){
        vertexList[src].adjList.push_back(dest);
        vertexList[dest].adjList.push_back(src);
    }

    void BFS(int startVertex){
        vector<bool> visited(vertexList.size(), false);
        queue<int> queue;

        queue.push(startVertex);
        visited[startVertex]=true;

        while(!queue.empty()){
            int currentVertex = queue.front();
            queue.pop();
            
            // Print the current vertex
            cout << currentVertex << " ";

            // Visit all adjacent vertices, when finished
            // Go unvisited one and start exploring its adjacents...
            for(int i=0; i<vertexList[currentVertex].adjList.size(); i++){
                // If current node is not visited and not visited already
                // push it to the front of the queue
                int adjNode = vertexList[currentVertex].adjList[i];
                bool x = visited[adjNode];
                // if(!visited[adjNode] && !isExistQueue(adjNode, queue)){
                if(!visited[adjNode]){
                    queue.push(adjNode);
                    visited[adjNode] = true;
                }
            }
        }
    }

    bool isExistQueue(int vertex, queue<int> myQueue){
        while(!myQueue.empty()){
            int current = myQueue.back();
            if (current==vertex) return true;
            myQueue.pop();
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

    graph.BFS(0);
    return 0;
}
