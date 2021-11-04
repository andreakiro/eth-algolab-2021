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
  int m, n, k, c;
  cin >> m >> n >> k >> c;
  
  // [0 - m*n-1] Incoming flows
  // [m*n - m*n*2-1] Outgoing flows
  
  graph G(m*n*2);
  edge_adder adder(G);
  
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  for (int i = 0; i < m*n; i++) {
    // adding vertex capacity constraint
    adder.add_edge(i, m*n + i, c);
    
    // adding issues to the target sink
    if (i % m == 0) adder.add_edge(m*n + i, target, 1);
    if (i % m == m - 1) adder.add_edge(m*n + i, target, 1);
    if (i < m) adder.add_edge(m*n + i, target, 1);
    if (i >= m*n - m) adder.add_edge(m*n + i, target, 1);
    
    // adding internal segment hallway (row-wise)
    if (i % m != 0) {
      int from = i; int to = i - 1;
      adder.add_edge(m*n + from, to, 1);
      adder.add_edge(m*n + to, from, 1);
    }
    
    // adding internal segment hallway (column-wise)
    if (m <= i) {
      int from = i; int to = i - m;
      adder.add_edge(m*n + from, to, 1);
      adder.add_edge(m*n + to, from, 1);
    }
  }
  
  for (int i = 0; i < k; i++) {
    int x, y; cin >> x >> y;
    int knight = x + m*y;
    adder.add_edge(source, knight, 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, source, target);
  cout << flow << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}