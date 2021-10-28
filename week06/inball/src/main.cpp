#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef vector<int> vint;

// Maximize r <=> Minimize -r
// Under (ai)j*xj + ||ai||*r <= bi (i<n)
// Variables are {xj} + r (D+1)

void solve(int n, int d) {
  vector<int> constraints(n);
  vector<vint> hyperplanes(n, vint(d));
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) cin >> hyperplanes[i][j];
    cin >> constraints[i];
  }
  
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  
  for (int i = 0; i < n; i++) {
    int norm2 = 0;
    for (int j = 0; j < d; j++) lp.set_a(j, i, hyperplanes[i][j]); // (ai)j*xj
    for (int j = 0; j < d; j++) norm2 += hyperplanes[i][j] * hyperplanes[i][j];
    int norm = (int) sqrt(norm2);
    lp.set_a(d, i, norm); // ||ai||*r
    lp.set_b(i, constraints[i]); // <= bi
  }
  
  lp.set_c(d, -1); // min (-r)
  lp.set_l(d, true, 0); // r >= 0
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_optimal()) cout << floor(CGAL::to_double(-s.objective_value())) << endl;
  else if (s.is_unbounded()) cout << "inf" << endl;
  else if (s.is_infeasible()) cout << "none" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n, d; cin >> n;
  while (n != 0) {
    cin >> d;
    solve(n, d);
    cin >> n;
  }
}