#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

void solve(int n) {
  vector<K::Point_2> points(n);
  for (int i = 0; i < n; i++) cin >> points[i];
  
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    K::Point_2 location; cin >> location;
    K::FT distance =  CGAL::squared_distance(location, t.nearest_vertex(location)->point());
    cout << fixed << setprecision(0) << distance << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while (n != 0) {
    solve(n);
    cin >> n;
  }
}