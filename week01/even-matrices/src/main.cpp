#include <iostream>
#include <vector>

using namespace std;

typedef std::vector<int> vint;
typedef std::vector<vint> mint;

void solve() {
  int n; cin >> n;
  
  mint M = mint(n + 1, vint(n + 1));
  mint pM = mint(n + 1, vint(n + 1));
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> M[i][j];
  
  for (int i = 0; i <= n; i++) {
    pM[0][i] = 0;
    pM[i][0] = 0;
  }
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      pM[i][j] = pM[i - 1][j] + pM[i][j - 1] - pM[i - 1][j - 1] + M[i][j];
  
  int solution = 0;
  
  for (int i1 = 1; i1 <= n; i1++) {
    for (int i2 = i1; i2 <= n; i2++) {
      
      vint S(201);
      vint pS(201);
      pS[0] = 0;
      
      for (int k = 1; k <= n; k++) {
        S[k] = pM[i2][k] - pM[i2][k - 1] - pM[i1 - 1][k] + pM[i1 - 1][k - 1];
        pS[k] = pS[k - 1] + S[k];
      }
      
      // Even Pairs O(n)
      int even = 0, odd = 0;
      for (int j = 1; j <= n; j++) {
        if (pS[j] % 2 == 0) even += 1;
        else odd += 1;
      }
      
      solution += even * (even - 1) / 2;
      solution += odd * (odd - 1) / 2;
      solution += even;
    }
  }
  
  std::cout << solution << std::endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
}