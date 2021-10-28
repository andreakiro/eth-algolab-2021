#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve_1(int a, int b) {
  // Define LP and index variables
  const int x = 0; const int y = 1;
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  
  // Set constraints equations coefficients
  lp.set_a(x, 0, 1); lp.set_a(y, 0, 1); lp.set_b(0, 4);
  lp.set_a(x, 1, 4); lp.set_a(y, 1, 2); lp.set_b(1, a*b);
  lp.set_a(x, 2,-1); lp.set_a(y, 2, 1); lp.set_b(2, 1);
  
  // Set objective function coefficients
  // Note we inverse the sign because we're maximizing 
  lp.set_c(x, a);
  lp.set_c(y, -b);
  
  // Solve the LP
  // Note we mult by (-1) cause min(x + y <= z) <=> max(-x -y >= -z)
  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_optimal()) cout << -1 * ceil(CGAL::to_double(s.objective_value())) << endl;
  else if (s.is_unbounded()) cout << "unbounded" << endl;
  else if (s.is_infeasible()) cout << "no" << endl;
}

void solve_2(int a, int b) {
  // Define LP and index variables
  const int x = 0, y = 1, z = 2;
  Program lp(CGAL::LARGER, false, 0, true, 0);
  
  // Set constraints equations coefficients
  lp.set_a(x, 0, 1); lp.set_a(y, 0, 1); lp.set_a(z, 0, 0); lp.set_b(0, -4);
  lp.set_a(x, 1, 4); lp.set_a(y, 1, 2); lp.set_a(z, 1, 1); lp.set_b(1, -a*b);
  lp.set_a(x, 2,-1); lp.set_a(y, 2, 1); lp.set_a(z, 0, 0); lp.set_b(2, -1);
  
  // Set objective function coefficients
  lp.set_c(x, a);
  lp.set_c(y, b);
  lp.set_c(z, 1);
  
  // Solve the LP
  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_optimal()) cout << ceil(CGAL::to_double(s.objective_value())) << endl;
  else if (s.is_unbounded()) cout << "unbounded" << endl;
  else if (s.is_infeasible()) cout << "no" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int p; cin >> p;
  while (p != 0) {
    int a, b;
    cin >> a >> b;
    if (p == 1) solve_1(a, b);
    else solve_2(a, b);
    cin >> p;
  }
}