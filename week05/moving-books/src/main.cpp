#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  
  vector<int> friends(n);
  vector<int> books(m);
  
  for (int i = 0; i < n; i++) cin >> friends[i];
  for (int i = 0; i < m; i++) cin >> books[i];
  
  sort(friends.begin(), friends.end(), greater<int>());
  sort(books.begin(), books.end(), greater<int>());
  
  if (friends[0] < books[0]) {
    cout << "impossible" << endl;
    return;
  }
  
  int ts = 0; // timestamp
  multiset<int, greater<int>> boxes(books.begin(), books.end());
  
  while (! boxes.empty()) {
    ts += 3;
    for (int i = 0; i < n; i++) {
      auto lb = boxes.lower_bound(friends[i]);
      if (lb == boxes.end()) break;
      else boxes.erase(lb);
    }
  }
  
  cout << ts - 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}