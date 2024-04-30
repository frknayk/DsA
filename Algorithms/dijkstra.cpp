#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>

using namespace std;

const int INF = numeric_limits<int>::max();

void connectEdges(vector<unordered_map<int,int>> &graph, int src, int dest, int weight){
    graph[src][dest]=weight;
    graph[dest][src]=weight;
}

void DijkstraEz(){
    int n=5;
    vector<unordered_map<int,int>> graph(n);
    connectEdges(graph,0,1,4);
    connectEdges(graph,0,2,1);
    connectEdges(graph,1,2,2);
    connectEdges(graph,1,3,1);
    connectEdges(graph,2,3,5);
    connectEdges(graph,3,4,3);

    int vertex = 0;

    vector<bool> visited(n,false);
    vector<int> distances(n, INF);

    distances[vertex] = 0;
    visited[vertex]=true;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, vertex});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(const auto& pair: graph[u]){
            int adj = pair.first;
            int weight = pair.second;
            if (distances[u] != INF && distances[u] + weight < distances[adj]){
                distances[adj] = distances[u] + weight;
                pq.push({distances[adj],adj});
            }
        }
        
    }
    cout << "Shortest distances from source vertex " << vertex << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": " << distances[i] << '\n';
    }


}

int main(){
    DijkstraEz();

    return 0;
}