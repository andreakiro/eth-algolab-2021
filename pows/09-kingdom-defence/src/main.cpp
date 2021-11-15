#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property,
  boost::property<boost::edge_capacity_t, long,
  boost::property<boost::edge_residual_capacity_t, long,
  boost::property<boost::edge_reverse_t, edge_desc>>>> graph;
  
class edge_adder {
  graph &G;
  
  public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void solve() {
  int l; cin >> l; // # locations
  int p; cin >> p; // # paths
  
  int expected = 0;
  
  graph G(l);
  edge_adder adder(G);
  
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  for (int i = 0; i < l; i++) {
    int supply, demand; cin >> supply >> demand;
    adder.add_edge(source, i, supply);
    adder.add_edge(i, target, demand);
    expected += demand;
  }
  
  for (int i = 0; i < p; i++) {
    int from, to; cin >> from >> to;
    int min, max; cin >> min >> max;
    if (max - min > 0) adder.add_edge(from, to, max - min);
    if (min > 0) {
      expected += min;
      adder.add_edge(source, to, min);
      adder.add_edge(from, target, min);
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  
  if (flow != expected) cout << "no" << endl;
  else cout << "yes" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}