#include <iostream>
#include <vector>

using namespace std;

/* memo[i,j] is your maximal profit
on the coin sequence [i,j] given that
player (n + i + j - 1)%2 starts */

typedef vector<int> VI;

int profit(VI &coins, vector<VI> &memo, int i, int j, bool myturn) {
  if (i > j) return 0;
  if (memo[i][j] != -1) return memo[i][j];
  
  int p1 = profit(coins, memo, i + 1, j, !myturn);
  int p2 = profit(coins, memo, i, j - 1, !myturn);
  
  if (myturn) memo[i][j] = max(coins[i] + p1, coins[j] + p2);
  else memo[i][j] = min(p1, p2);
  
  return memo[i][j];
}

void testcase() {
  int n; cin >> n;
  vector<int> coins(n);
  vector<VI> memo(n, VI(n, -1));
  for (int i = 0; i < n; i++) cin >> coins[i];
  cout << profit(coins, memo, 0, n - 1, true) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase();
}