#include <iostream>
#include <vector>
#include <set>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> VB;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> FB;
typedef CGAL::Triangulation_data_structure_2<VB, FB> TDS;
typedef CGAL::Delaunay_triangulation_2<K, TDS> Triangulation;
typedef pair<Triangulation::Face_handle, double> tpair;

struct csort {
  bool operator() (const tpair &p1, const tpair &p2) {
    return p1.second > p2.second;
  }
};

void solve(int n) {
  vector<K::Point_2> infected(n);
  for (int i = 0; i < n; i++)
    cin >> infected[i];
  
  Triangulation t;
  t.insert(infected.begin(), infected.end());
  multiset<pair<Triangulation::Face_handle, double>, csort> builder;
  
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) {
    if (t.is_infinite(f)) builder.insert({f, std::numeric_limits<double>::max()});
    f->info() = 0;
  }
  
  while (! builder.empty()) {
    auto it = builder.begin();
    auto f = (*it).first;
    double dist = (*it).second;
    builder.erase(it);
    if (f->info() >= dist) continue;
    f->info() = dist;
    for (int i = 0; i < 3; i++) {
      auto neighbor = f->neighbor(i);
      if (t.is_infinite(neighbor)) continue;
      if (neighbor->info() != 0) continue;
      auto v1 = f->vertex((i+1)%3)->point();
      auto v2 = f->vertex((i+2)%3)->point();
      double min_dist = std::min(CGAL::squared_distance(v1, v2), dist);
      builder.insert({neighbor, min_dist});
    }
  }
  
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    K::Point_2 p; cin >> p;
    double d; cin >> d;
    auto nearest = t.nearest_vertex(p);
    
    if (CGAL::squared_distance(nearest->point(), p) < d) {
      cout << 'n';
      continue;
    }
    
    double bottleneck = t.locate(p)->info(); 
    if (bottleneck < 4*d) cout << 'n';
    else cout << 'y';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while (n != 0) {
    solve(n);
    cout << endl;
    cin >> n;
  }
}