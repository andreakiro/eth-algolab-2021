#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
  int vertices;
  vector<vector<int>> adj;
  
  // BFS related
  vector<int> distance;
  
  public:
  Graph(int v);
  void addEdge(int v1, int v2);
  void BFS(int s);
  void output();
};

Graph::Graph(int n) {
  vertices = n;
  for (int i = 0; i < n; i++) {
    vector<int> v;
    adj.push_back(v);
    distance.push_back(-1);
  }
}

void Graph::addEdge(int v1, int v2) {
  adj[v1].push_back(v2);
  adj[v2].push_back(v1);
}

void Graph::BFS(int s) {
  queue<int> q;
  q.push(s);
  distance[s] = 0;
  
  while (! q.empty()) {
    int cur = q.front();
    
    for (int v: adj[cur]) {
      if (distance[v] == -1) {
        distance[v] = distance[cur] + 1;
        q.push(v);
      }
    }
    
    q.pop();
  }
}

void Graph::output() {
  for (int i = 0; i < vertices; i++) cout << distance[i] << " ";
  cout << endl;
}

void testcase() {
  int n; cin >> n; // number vertices
  int m; cin >> m; // number edges
  int s; cin >> s; // starting vertex
  
  Graph g(n);
  
  for (int i = 0; i < m; i++) {
    int v1; cin >> v1;
    int v2; cin >> v2;
    g.addEdge(v1, v2);
  }
  
  g.BFS(s);
  g.output();
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase();
  return 0;
}