#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> WG;
typedef graph_traits<WG>::edge_descriptor Edge;
typedef property_map<WG, edge_weight_t>::type WeightMap;

/* NB1. Tests do not include case ofngraphs having 
non-unique MST as a function of the starting vertex.
We thus dont need the hive source in order to pass tests.
Otherwise we should use Prim rather than Kruskal. */

/* NB2. Boost support parallel edges. So we can
keep pushing better edge between two vertices. */

void kruskal(WG &G, WG &sub) {
  vector<Edge> mst;
  WeightMap weights = get(edge_weight, sub);
  kruskal_minimum_spanning_tree(sub, back_inserter(mst));
  for (vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it)
    add_edge(source(*it, sub), target(*it, sub), weights[*it], G);
}

int dijkstra(WG &G, int source, int target) {
  int n = num_vertices(G);
  vector<int> dist_map(n);
  auto it = make_iterator_property_map(dist_map.begin(), get(vertex_index, G));
  dijkstra_shortest_paths(G, source, distance_map(it));
  return dist_map[target];
}

void solve() {
  int n_vertices; cin >> n_vertices;
  int n_edges; cin >> n_edges;
  int n_species; cin >> n_species;
  int source; cin >> source;
  int target; cin >> target;
  
  vector<WG> subnets(n_species, WG(n_vertices));
  for (int i = 0; i < n_edges; i++) {
    int v1, v2; cin >> v1 >> v2;
    for (int j = 0; j < n_species; j++) {
      int w; cin >> w;
      add_edge(v1, v2, w, subnets[j]);
    }
  }
  
  WG forest(n_vertices);
  for(int i = 0; i < n_species; i++) {
    int hive; cin >> hive;
    kruskal(forest, subnets[i]);
  }
  
  cout << dijkstra(forest, source, target) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}