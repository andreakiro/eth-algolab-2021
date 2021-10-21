#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

typedef vector<string> vs;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor vertex_desc;

int intersection(int c, vs &chars1, vs &chars2) {
  int common = 0, i = 0, j = 0;
  while (i < c && j < c) {
    if (chars1[i].compare(chars2[j]) < 0) i++;
    else if (chars1[i].compare(chars2[j]) > 0) j++;
    else { common++; i++; j++; }
  }
  return common;
}

void solve() {
  int n; cin >> n; 
  int c; cin >> c;
  int f; cin >> f;
  
  vector<vs> characteristics(n, vs(c));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < c; j++) cin >> characteristics[i][j];
    sort(characteristics[i].begin(), characteristics[i].end());
  }
  
  Graph classroom(n);

  // Add edge if (shared > f)
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      vs chars1 = characteristics[i];
      vs chars2 = characteristics[j];
      int common = intersection(c, chars1, chars2);
      if (common > f) add_edge(i, j, classroom);
    }
  }
  
  // Run Maximum Cardinality Matching
  vector<vertex_desc> mate(n);
  checked_edmonds_maximum_cardinality_matching(classroom, make_iterator_property_map(mate.begin(), get(vertex_index, classroom)));
  int ms = matching_size(classroom, make_iterator_property_map(mate.begin(), get(vertex_index, classroom)));
  
  if (ms == n/2) cout << "not optimal" << endl;
  else cout << "optimal" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}