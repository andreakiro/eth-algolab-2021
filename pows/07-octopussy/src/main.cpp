#include <iostream>
#include <vector>
#include <set>

using namespace std;
typedef vector<int> vint;

void solve() {
  int n; cin >> n;
  vint exptimes(n);
  for (int i = 0; i < n; i++) 
    cin >> exptimes[i];
  
  vint permutation;
  multiset<pair<int,int>, greater<pair<int,int>>> bombs;
  // The pair represents <explosion_time, bomb_index>
  
  permutation.push_back(0);
  if (1 < n) bombs.insert(make_pair(exptimes[1], 1));
  if (2 < n) bombs.insert(make_pair(exptimes[2], 2));
  
  while (! bombs.empty()) {
    auto it = bombs.begin();
    permutation.push_back((*it).second);
    bombs.erase(it);
    int i = (*it).second;
    int c1 = 2*i + 1, c2 = 2*i + 2;
    if (c1 < n) bombs.insert(make_pair(exptimes[c1], c1));
    if (c2 < n) bombs.insert(make_pair(exptimes[c2], c2));
  }
  
  bool valid = true;
  for (int i = 0; i < n; i++) {
    int bomb = permutation[n - i - 1];
    if (! (i < exptimes[bomb])) valid = false;
  }
  
  if (valid) cout << "yes" << endl;
  else cout << "no" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for (int i = 0; i < t; i++) solve();
}