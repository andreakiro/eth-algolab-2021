#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> WG;
typedef graph_traits<WG>::edge_descriptor Edge;
typedef graph_traits<WG>::vertex_descriptor Vertex;
typedef property_map<WG, edge_weight_t>::type WeightMap;

int kruskal(WG &wg) {
  int sum = 0;
  vector<Edge> mst;
  WeightMap weights = get(edge_weight, wg);
  kruskal_minimum_spanning_tree(wg, back_inserter(mst));
  for (vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it)
    sum += weights[*it];
  return sum;
}

int dijkstra(WG &wg, int source) {
  int max_dist = -1;
  int n = num_vertices(wg);
  vector<int> dist_map(n);
  auto it_prop = make_iterator_property_map(dist_map.begin(), get(vertex_index, wg));
  dijkstra_shortest_paths(wg, source, distance_map(it_prop));
  for (int i = 0; i < n; i++)
    max_dist = max(max_dist, dist_map[i]);
  return max_dist;
}

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  
  WG wg(n);
  for (int i = 0; i < m; i++) {
    int v1, v2, w;
    cin >> v1 >> v2 >> w;
    add_edge(v1, v2, w, wg);
  }
  
  cout << kruskal(wg) << " " << dijkstra(wg, 0) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}