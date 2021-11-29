#include <iostream>
#include <vector>
#include <tuple>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

typedef std::tuple<K::Point_2, int, int> warehouse;
typedef std::tuple<K::Point_2, int, int> stadium;
typedef std::pair<K::Point_2, int> cline;

void solve() {
  int n; cin >> n;
  int m; cin >> m; 
  int c; cin >> c; 
  
  vector<warehouse> warehouses(n);
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    int s, a; cin >> s >> a;
    warehouses[i] = warehouse(K::Point_2(x,y), s, a);
  }
  
  vector<stadium> stadiums(m);
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    int d, u; cin >> d >> u;
    stadiums[i] = stadium(K::Point_2(x,y), d, u); 
  }
  
  vector<vector<double>> revenues(n, vector<double>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> revenues[i][j];
  
  vector<cline> clines(c);
  for (int i = 0; i < c; i++) {
    int x, y, r; cin >> x >> y >> r;
    clines[i] = cline(K::Point_2(x, y), r);
  } 
  
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  int row = 0;
  
  // for every warehouse : export <= supply(w)
  for (int i = 0; i < n; i++) {
    warehouse wh = warehouses[i];
    int supply = std::get<1>(wh);
    for (int j = 0; j < m; j++) lp.set_a(m*i + j, row, 1);
    lp.set_b(row, supply);
    row++;
  }
  
  // for every stadium : inport = demand(s)
  // for every stadium : alcohol <= upper(s)
    for (int j = 0; j < m; j++) {
    stadium st = stadiums[j];
    int demand = std::get<1>(st);
    int upperl = std::get<2>(st);
    for (int i = 0; i < n; i++) lp.set_a(m*i + j, row, 1);
    lp.set_b(row, demand);
    row++;
    for (int i = 0; i < n; i++) lp.set_a(m*i + j, row, -1);
    lp.set_b(row, -demand);
    row++;
    for (int i = 0; i < n; i++) {
      warehouse wh = warehouses[i];
      int alcohol = std::get<2>(wh);
      lp.set_a(m*i + j, row, alcohol);
    }
    lp.set_b(row, upperl*100);
    row++;
  }
  
  vector<K::Point_2> locations(n + m);
  for (int i = 0; i < n; i++) locations[i] = std::get<0>(warehouses[i]);
  for (int j = 0; j < m; j++) locations[j + n] = std::get<0>(stadiums[j]);
  
  Triangulation t;
  t.insert(locations.begin(), locations.end());
  
  for (int i = 0; i < c; i++) {
    K::Point_2 p = clines[i].first;
    long radius = clines[i].second;
    long sqradius = radius*radius;
    if (CGAL::squared_distance(t.nearest_vertex(p)->point(), p) <= sqradius) {
      for (int i = 0; i < n; i++) {
        bool sign1 = CGAL::squared_distance(p, locations[i]) <= sqradius;
        for (int j = 0; j < m; j++) {
          bool sign2 = CGAL::squared_distance(p, locations[j + n]) <= sqradius;
          if (sign1 != sign2) revenues[i][j] -= 0.01;
        }
      }
    }
  }
  
  // objective func: max Q(w,s)*R(w,s)
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      lp.set_c(m*i + j, -revenues[i][j]);
  
  Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
  
  if (s.is_infeasible()) {
    cout << "RIOT!" << endl; 
    return;
  }

  cout << std::fixed << std::setprecision(0) << floor(CGAL::to_double(-s.objective_value())) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for (int i = 0; i < t; i++) solve();
}