#include <iostream>
#include <vector>
#include <tuple>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef vector<int> vint;
typedef std::tuple<pair<int, int>, int, int> warehouse;
typedef std::tuple<pair<int, int>, int, int> stadium;
typedef std::tuple<pair<int, int>, int> cline;

void solve() {
  int n; cin >> n;
  int m; cin >> m; 
  int c; cin >> c; 
  
  vector<warehouse> warehouses(n);
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    int s, a; cin >> s >> a;
    warehouses[i] = warehouse(make_pair(x,y), s, a);
  }
  
  vector<stadium> stadiums(m);
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    int d, u; cin >> d >> u;
    stadiums[i] = stadium(make_pair(x,y), d, u); 
  }
  
  vector<vint> revenues(n, vint(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> revenues[i][j];
  
  vector<cline> clines(c);
  for (int i = 0; i < c; i++) {
    int x, y, r; cin >> x >> y >> r;
    clines[i] = cline(make_pair(x, y), r);
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
  
  vector<vector<double>> penalties(n, vector<double>(m, 0));
  for (int i = 0; i < n; i++) {
    warehouse wh = warehouses[i];
    int wh_x = std::get<0>(wh).first;
    int wh_y = std::get<0>(wh).second;
    for (int j = 0; j < m; j++) {
      stadium st = stadiums[j];
      int st_x = std::get<0>(st).first;
      int st_y = std::get<0>(st).second;
      int a = st_y - wh_y;
      int b = st_x - wh_x;
      int cl = 2*wh_x*wh_y - wh_x*st_y - st_x*wh_y;
      for (int l = 0; l < c; l++) {
        cline cli = clines[l];
        double d = std::abs(a*std::get<0>(cli).first + b*std::get<0>(cli).second + cl);
        d /= std::sqrt(a*a + b*b);
        if (d <= std::get<1>(cli)) penalties[i][j] += 0.01;
      }
    }
  }
  
  // objective func: max Q(w,s)*R(w,s)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (penalties[i][j] == 0) lp.set_c(m*i + j, -revenues[i][j]);
      else lp.set_c(n*i + m*j, -revenues[i][j] + penalties[i][j]);
    }
  }
      
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