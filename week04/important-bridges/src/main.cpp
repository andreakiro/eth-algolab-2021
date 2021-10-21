#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;

struct edge_component_t {
  enum { num = 555 };
  typedef edge_property_tag kind;
} edge_component;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_component_t, size_t>> Graph;
typedef graph_traits<Graph>::vertex_descriptor vertex_desc;

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  
  Graph city(n);
  
  for (int i = 0; i < m; i++) {
    int e1; cin >> e1;
    int e2; cin >> e2;
    add_edge(e1, e2, city);
  }
  
  // Get biconnected components
  property_map<Graph, edge_component_t>::type components = get(edge_component, city);
  size_t num_comps = biconnected_components(city, components);
  
  // Helpers
  vector<pair<int,int>> result;
  vector<int> num_edges(num_comps);
  graph_traits<Graph>::edge_iterator ei, ei_end;
  
  // Count edges per components
  for (boost::tie(ei, ei_end) = edges(city); ei != ei_end; ++ei)
    num_edges[components[*ei]] += 1;
  
  // Retrieve results if edge is a bridge
  for (boost::tie(ei, ei_end) = edges(city); ei != ei_end; ++ei) {
    if (num_edges[components[*ei]] == 1) {
      int src = source(*ei, city);
      int tar = target(*ei, city);
      if (src < tar) result.push_back(make_pair(src, tar));
      else result.push_back(make_pair(tar, src));
    } 
  }
  
  // Sort in lexicographical order
  sort(result.begin(), result.end());
  cout << result.size() << endl;
  for (int i = 0; i < (int) result.size(); i++)
    cout << result[i].first << " " << result[i].second << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}