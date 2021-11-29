#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
  int vertices;
  vector<vector<int>> adj;
  
  // DFS related
  int timestamp;
  vector<bool> visited;
  vector<int> discovered;
  vector<int> finished;
  
  public:
  Graph(int v);
  void addEdge(int v1, int v2);
  void sortadj();
  void DFS(int s);
  void output();
};

Graph::Graph(int n) {
  vertices = n;
  timestamp = -1;
  for (int i = 0; i < n; i++) {
    vector<int> v;
    adj.push_back(v);
    visited.push_back(false);
    discovered.push_back(-1);
    finished.push_back(-1);
  }
}

void Graph::addEdge(int v1, int v2) {
  adj[v1].push_back(v2);
  adj[v2].push_back(v1);
}

void Graph::sortadj() {
  for (int i = 0; i < vertices; i++)
    sort(adj[i].begin(), adj[i].end());
}

void Graph::DFS(int s) {
  timestamp += 1;
  discovered[s] = timestamp;
  visited[s] = true;
  for (int v: adj[s])
    if (! visited[v]) DFS(v);
  timestamp += 1;
  finished[s] = timestamp;
}

void Graph::output() {
  for (int i = 0; i < vertices; i++) cout << discovered[i] << " ";
  cout << endl;
  for (int i = 0; i < vertices; i++) cout << finished[i] << " ";
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
  
  g.sortadj();
  g.DFS(s);
  g.output();
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase();
  return 0;
}