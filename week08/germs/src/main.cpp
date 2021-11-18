#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void solve(int n) {
  int left, bottom; cin >> left >> bottom;
  int right, top; cin >> right >> top;
  
  vector<K::Point_2> bacteria(n);
  for (int i = 0; i < n; i++)
    cin >> bacteria[i];
  
  Triangulation t;
  t.insert(bacteria.begin(), bacteria.end());
  
  vector<int> deaths;
  
  for (auto v = t.vertices_begin(); v != t.vertices_end(); v++) {
    Triangulation::Edge_circulator c = t.incident_edges(v);
    Triangulation::Edge_circulator vc = c;
    
    K::FT sdist = -1;
    if (c != 0) do {
      if (!t.is_infinite(c)) {
        K::FT dist = sqrt(t.segment(c).squared_length()) / 2;
        if (sdist == -1 || dist < sdist) sdist = dist;
      }
    } while (++c != vc);
    
    K::FT x = v->point().x(), y = v->point().y();
    K::FT b = min({x - left, right - x, y - bottom, top - y});
    if (sdist == -1) sdist = b;
    else sdist = std::min(sdist, b);
    
    int death = ceil(sqrt(sdist - 0.5));
    deaths.push_back(death);
  }
  
  auto m = deaths.begin() + (deaths.size() / 2);
  std::nth_element(deaths.begin(), m, deaths.end());
  
  auto f = std::min_element(deaths.begin(), deaths.end());
  auto l = std::max_element(deaths.begin(), deaths.end());
  
  cout << *f << " " << *m << " " << *l << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while (n != 0) {
    solve(n);
    cin >> n;
  } 
}