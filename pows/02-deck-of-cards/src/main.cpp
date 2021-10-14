#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void solve() {
  int n; cin >> n;
  int k; cin >> k;
  
  vector<int> deck(n);
  for (int i = 0; i < n; i++) cin >> deck[i];
  
  int i = 0, j = 0, bi = 0, bj = 0;
  int ps = deck[0], bps = INT_MAX;
  
  while (j < n) {
    if (i > j) {
      j = i; ps = deck[i];
      if (abs(ps - k) < abs(bps - k)) { bi = i; bj = j; bps = ps; }
    } else if (ps < k) {
      j += 1; ps += deck[j];
      if (abs(ps - k) < abs(bps - k)) { bi = i; bj = j; bps = ps; }
    } else if (ps > k) {
      ps -= deck[i]; i += 1;
      if (abs(ps - k) < abs(bps - k)) { bi = i; bj = j; bps = ps; }
    } else if (ps == k) {
      bi = i; bj = j;
      break; 
    }
  }
  
  cout << bi << " " << bj << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}