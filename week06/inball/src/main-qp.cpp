// This solution does not work !

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef vector<int> vint;

// Maximize the radius of a D-sphere in a polyhedral
// Under the constraints of the N hyperplans equations

// min sum{i<d} (2*xi*xi' - xi^2 - xi'^2) (2D variables)
// Under 2n constraints sum{i<d} (aji*{xi, xi'} <= bj) (j<n)

void solve(int n, int d) {
  vector<int> constraints(n);
  vector<vint> hyperplans(n, vint(d));
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) cin >> hyperplans[i][j];
    cin >> constraints[i];
  }
  
  Program qp(CGAL::SMALLER, false, 0, false, 0);
  
  for (int i = 0; i < n; i++) {
    qp.set_b(i,   constraints[i]);
    qp.set_b(n+i, constraints[i]);
    for (int j = 0; j < d; j++) { 
      qp.set_a(j,   i, hyperplans[i][j]); // for points xi
      qp.set_a(j, n+i, hyperplans[i][j]); // for centers xi'
    }
  }
  
  for (int i = 0; i < d; i++) {
    qp.set_d(i, n+i, 4);    // 2*xi*xi'
    qp.set_d(i, i, -2);     // - xi^2
    qp.set_d(n+i, n+i, -2); // - xi'^2
  }
  
  Solution s = CGAL::solve_linear_program(qp, ET());
  if (s.is_optimal()) cout << floor(sqrt(CGAL::to_double(s.objective_value()))) << endl;
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