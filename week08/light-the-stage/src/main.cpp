#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void solve() {
  int m; cin >> m;
  int n; cin >> n;
  
  vector<pair<K::Point_2, int>> players(m);
  vector<K::Point_2> lights(n);
  
  for (int i = 0; i < m; i++) {
    K::Point_2 p; cin >> p;
    int rad; cin >> rad;
    players[i] = make_pair(p, rad);
  }
  
  int h; cin >> h;
  for (int i = 0; i < n; i++) 
    cin >> lights[i];
  
  Triangulation t;
  t.insert(lights.begin(), lights.end());
  
  int winner_ind = -1;
  vector<int> result(m);
  
  for (int i = 0; i < m; i++) {
    auto player = players[i].first;
    auto nearest = t.nearest_vertex(player);
    double threshold = pow(players[i].second + h, 2);
    
    if (CGAL::squared_distance(nearest->point(), player) >= threshold) {
      winner_ind = INT32_MAX;
      result[i] = INT32_MAX;
    } else {
      int first_hit = -1;
      
      for (int j = 0; j < n; j++) {
        if (CGAL::squared_distance(lights[j], player) < threshold) {
          first_hit = j;
          break;
        }
      }
      
      winner_ind = max(winner_ind, first_hit);
      result[i] = first_hit;
    }
  }
  
  for (int i = 0; i < m; i++) {
    if (result[i] == winner_ind)
      cout << i << " ";
  }
  
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}
