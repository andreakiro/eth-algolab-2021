#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property,
  boost::property<boost::edge_capacity_t, long,
  boost::property<boost::edge_residual_capacity_t, long,
  boost::property<boost::edge_reverse_t, traits::edge_descriptor,
  boost::property<boost::edge_weight_t, long>>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;
    w_map[rev_e] = -cost;
  }
};

void solve() {
  int n; cin >> n; // n buyers
  int m; cin >> m; // m props.
  int s; cin >> s; // s states

  graph G(n + m + s);
  edge_adder adder(G);
  
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  for (int i = 0; i < n; i++)
    adder.add_edge(source, i, 1, 0);
  
  for (int i = 0; i < s; i++) {
    int limit; cin >> limit;
    adder.add_edge(n + m + i, target, limit, 0);
  }
    
  for (int i = 0; i < m; i++) {
    int state; cin >> state;
    adder.add_edge(n + i, n + m + state - 1, 1, 0);
  }
  
  // Option 1: Negated weights. 4/5 testsets.
  
  /*for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int bid; cin >> bid;
      adder.add_edge(i, n + j, 1, -bid);
    }
  }
  
  int flow = boost::push_relabel_max_flow(G, source, target);
  boost::cycle_canceling(G);
  int profit = boost::find_flow_cost(G);
  
  cout << flow << " " << -profit << endl;*/
  
  // Option 2: Get rid of negated weights.
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int bid; cin >> bid;
      adder.add_edge(i, n + j, 1, -bid + 100);
    }
  }
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int profit = boost::find_flow_cost(G);
  
  int flow = 0;
  out_edge_it e, eend;
  for (boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e)
    flow += c_map[*e] - rc_map[*e];
  
  cout << flow << " " << 100*flow - profit << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}