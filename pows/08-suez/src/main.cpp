#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve() {
  int n; cin >> n;
  int m; cin >> m; 
  int h; cin >> h;
  int w; cin >> w;
  
  vector<pair<int, int>> freenails(n);
  vector<pair<int, int>> oldnails(m);
  
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    freenails[i] = make_pair(x, y);
  }
  
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    oldnails[i] = make_pair(x, y);
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);

  int row = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      ET delta_x = abs(freenails[i].first - freenails[j].first);
      ET delta_y = abs(freenails[i].second - freenails[j].second);
      lp.set_a(i, row, 1);
      lp.set_a(j, row, 1);
      lp.set_b(row, max(delta_x*2/w, delta_y*2/h));
      row++;
    }
    
    ET largest_a = -1;
    for (int j = 0; j < m; j++) {
      ET delta_x = abs(freenails[i].first - oldnails[j].first);
      ET delta_y = abs(freenails[i].second - oldnails[j].second);
      ET coeff = max(delta_x*2/w - 1, delta_y*2/h - 1);
      if (largest_a == -1 || coeff < largest_a) largest_a = coeff;
    }
    
    if (m > 0) {
      lp.set_a(i, row, 1);
      lp.set_b(row, largest_a);
      row++;
    }
  }
  
  for (int i = 0; i < n; i++) 
    lp.set_c(i, -2*(h+w));
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  cout << fixed << setprecision(0) << ceil(CGAL::to_double(-s.objective_value())) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}