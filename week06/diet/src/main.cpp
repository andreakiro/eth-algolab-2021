#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

// xi are food units with price pi (i<m)
// cij nutriments per food unit (i<m, j<n)

// min (p1*x1 + p2*x2 + ... + pm*xm) 
// under n constraints (min_j <= sum{i<m} xi*cij <= max_j)

void solve(int n, int m) {
  // Collect input data
  vector<pair<int, int>> nutriments(n);
  vector<pair<int, vector<int>>> food(m);
  
  for (int j = 0; j < n; j++) {
    int min, max; cin >> min >> max;
    nutriments[j] = make_pair(min, max);
  }
  
  for (int i = 0; i < m; i++) {
    int price; cin >> price;
    vector<int> nuts(n);
    for (int j = 0; j < n; j++) cin >> nuts[j];
    food[i] = make_pair(price, nuts);
  }
  
  // Define our LP Program
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  
  // Set constraints equation coefficients
  for (int j = 0; j < n; j++) {
    int min = nutriments[j].first;
    int max = nutriments[j].second;
    for (int i = 0; i < m; i++) {
      int cij = food[i].second[j];
      lp.set_a(i, j,   cij); lp.set_b(j,   max); // sum{i<m} xi*cij <= max_j
      lp.set_a(i, n+j,-cij); lp.set_b(n+j,-min); // min_j <= sum{i<m} xi*cij
    }
  }
  
  // Set objective function coefficients
  for (int i = 0; i < m; i++) lp.set_c(i, food[i].first);
  
  // Solve the LP
  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_optimal()) cout << floor(CGAL::to_double(s.objective_value())) << endl;
  else if (s.is_infeasible()) cout << "No such diet." << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n, m; cin >> n >> m;
  while (n != 0 || m != 0) {
    solve(n, m);
    cin >> n >> m;
  }
}