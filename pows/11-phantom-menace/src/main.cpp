#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property,
  boost::property<boost::edge_capacity_t, long,
  boost::property<boost::edge_residual_capacity_t, long,
  boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef traits::vertex_descriptor vertex_desc;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};


void solve() {
  int n, m; cin >> n >> m; 
  int s, d; cin >> s >> d;
  
  vector<pair<int, int>> paths(m);
  for (int i = 0; i < m; i++) {
    int v1, v2; cin >> v1 >> v2;
    paths[i] = make_pair(v1, v2);
  }
  
  vector<int> sources(s);
  vector<int> destinations(d);
  for (int i = 0; i < s; i++) cin >> sources[i];
  for (int i = 0; i < d; i++) cin >> destinations[i];
  
  graph G(2*n);
  edge_adder adder(G);
  
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  for (int i = 0; i < s; i++) adder.add_edge(source, sources[i], INT_MAX);
  for (int i = 0; i < d; i++) adder.add_edge(n + destinations[i], target, INT_MAX);
  for (int i = 0; i < m; i++) adder.add_edge(n + paths[i].first, paths[i].second, INT_MAX);
  for (int i = 0; i < n; i++) adder.add_edge(i, n + i, 1);
  
  cout << boost::push_relabel_max_flow(G, source, target) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}