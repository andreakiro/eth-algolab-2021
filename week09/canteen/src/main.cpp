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
  boost::property <boost::edge_weight_t, long>>>>> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef traits::vertex_descriptor vertex_desc;

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
  int n; cin >> n;
  int students = 0;
  
  graph G(n);
  edge_adder adder(G);
  
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  for (int i = 0; i < n; i++) {
    int cap_menu; cin >> cap_menu;
    int cost_menu; cin >> cost_menu;
    adder.add_edge(source, i, cap_menu, 20 + cost_menu);
  }
  
  for (int i = 0; i < n; i++) {
    int n_students; cin >> n_students;
    int menu_price; cin >> menu_price;
    students += n_students;
    adder.add_edge(i, target, n_students, 20 - menu_price);
  }
  
  for (int i = 0; i < n - 1; i++) {
    int cap_storage; cin >> cap_storage;
    int cost_storage; cin >> cost_storage;
    adder.add_edge(i, i + 1, cap_storage, cost_storage);
  }
  
  /*int flow = boost::push_relabel_max_flow(G, source, target);
  boost::cycle_canceling(G);
  int cost = boost::find_flow_cost(G);*/
  
  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);
  int flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source, G), G); e != eend; ++e)
      flow += c_map[*e] - rc_map[*e];
  cost -= 40*flow;
  
  if (flow < students) cout << "impossible ";
  else cout << "possible ";
  
  cout << flow << " " << - cost << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}