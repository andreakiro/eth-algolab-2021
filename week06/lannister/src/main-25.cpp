#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

bool separable(vector<pair<int, int>> &v1, vector<pair<int, int>> &v2) {
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  const int a = 0, b = 1, c = 2; // line coefficients
  const int n = (int) v1.size(), m = (int) v2.size();
  
  for (int i = 0; i < n; i++) {
    lp.set_a(a, i, v1[i].first);
    lp.set_a(b, i, v1[i].second);
    lp.set_a(c, i, 1);
  }
  
  for (int i = 0; i < m; i++) {
    lp.set_a(a, m+i, -v2[i].first);
    lp.set_a(b, m+i, -v2[i].second);
    lp.set_a(c, m+i, -1);
  }
  
  // Seeking positive derivative line
  lp.set_l(b, true, 1);
  Solution s1 = CGAL::solve_linear_program(lp, ET());
  
  // Seeking negative derivative line
  lp.set_l(b, false, 0);
  lp.set_u(b, true, -1);
  Solution s2 = CGAL::solve_linear_program(lp, ET());
  
  return !s1.is_infeasible() || !s2.is_infeasible();
}

void solve() {
  int n, m, s;
  cin >> n >> m >> s;
  
  vector<pair<int, int>> nobles(n);
  vector<pair<int, int>> commons(m);
  
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    nobles[i] = make_pair(x, y);
  }
  
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    commons[i] = make_pair(x, y);
  }
  
  // LP: nobles/commons linear separation
  bool sep = separable(nobles, commons);
  
  if (sep) cout << "Bankrupt!" << endl;
  else cout << "Yuck!" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}