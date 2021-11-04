#include <iostream>
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
  int n; cin >> n; // # players
  int m; cin >> m; // # rounds
  
  // [0 - m-1] Round vertices
  // [m - n-1] Player vertices
  
  graph G(m + n);
  edge_adder adder(G);
  
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  for (int i = 0; i < m; i++) {
    int p1, p2, outcome;
    cin >> p1 >> p2 >> outcome;
    adder.add_edge(source, i, 1);
    switch (outcome) {
      case 0:
        adder.add_edge(i, m + p1, 1);
        adder.add_edge(i, m + p2, 1);
        break;
      case 1:
        adder.add_edge(i, m + p1, 1);
        break;
      case 2:
        adder.add_edge(i, m + p2, 1);
        break;
    }
  }
  
  int score = 0;
  for (int i = 0; i < n; i++) {
    int s; cin >> s; score += s;
    adder.add_edge(m + i, target, s);
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  
  if (flow == score && flow == m) cout << "yes" << endl;
  else cout << "no" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}
