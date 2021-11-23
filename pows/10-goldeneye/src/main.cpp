#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> VB;
typedef CGAL::Triangulation_face_base_2<K> FB;
typedef CGAL::Triangulation_data_structure_2<VB, FB> TDS;
typedef CGAL::Delaunay_triangulation_2<K, TDS> Triangulation;
typedef boost::disjoint_sets_with_storage<> UnionFind;
typedef pair<K::Point_2, int> PointID;

struct Edge {
  Edge(int v1, int v2, K::FT sql): v1(v1), v2(v2), sql(sql) {}
  int v1, v2;
  K::FT sql;
};

inline bool operator<(const Edge& e, const Edge& f) {
  return e.sql < f.sql;
}

void solve() {
  int n; cin >> n; 
  int m; cin >> m;
  double p; cin >> p;
  
  vector<PointID> jammers(n);
  for (int i = 0; i < n; i++) {
    K::Point_2 p; cin >> p;
    jammers[i] = PointID(p, i);
  }
  
  Triangulation t;
  t.insert(jammers.begin(), jammers.end());
  
  vector<Edge> edges;
  for (auto ei = t.finite_edges_begin(); ei != t.finite_edges_end(); ++ei) {
    int v1 = ei->first->vertex((ei->second+1)%3)->info();
    int v2 = ei->first->vertex((ei->second+2)%3)->info();
    K::FT sql = t.segment(ei).squared_length();
    edges.push_back(Edge(v1, v2, sql));
  }
  
  sort(edges.begin(), edges.end());
  
  UnionFind ufp(n);
  for (auto ei = edges.begin(); ei != edges.end() && ei->sql <= p; ++ei)
    ufp.union_set(ei->v1, ei->v2);
    
  UnionFind ufa(n); auto ai = edges.begin(); K::FT smallest_p_all = 0;
  UnionFind ufb(n); auto bi = edges.begin(); K::FT smallest_p_ufp = 0;
  
  for (int i = 0; i < m; i++) {
    K::Point_2 source; cin >> source;
    K::Point_2 target; cin >> target;
    Triangulation::Vertex_handle s_nearest = t.nearest_vertex(source);
    Triangulation::Vertex_handle t_nearest = t.nearest_vertex(target);
    K::FT d1 = CGAL::squared_distance(source, s_nearest->point());
    K::FT d2 = CGAL::squared_distance(target, t_nearest->point());
    K::FT d = 4 * std::max(d1, d2);
    
    if (d <= p && ufp.find_set(s_nearest->info()) == ufp.find_set(t_nearest->info())) {
      if (d > smallest_p_ufp) smallest_p_ufp = d;
      for (; bi != edges.end() && ufb.find_set(s_nearest->info()) != ufb.find_set(t_nearest->info()); ++bi)
        ufb.union_set(bi->v1, bi->v2);
      cout << 'y';
    } else cout << 'n';
    
    if (d > smallest_p_all) smallest_p_all = d;
    for (; ai != edges.end() && ufa.find_set(s_nearest->info()) != ufa.find_set(t_nearest->info()); ++ai)
      ufa.union_set(ai->v1, ai->v2);
  }
  
  if (ai != edges.begin() && (ai-1)->sql > smallest_p_all) smallest_p_all = (ai-1)->sql;
  if (bi != edges.begin() && (bi-1)->sql > smallest_p_ufp) smallest_p_ufp = (bi-1)->sql;
  
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::cout << endl << smallest_p_all << endl << smallest_p_ufp << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}
