#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

using namespace std;
typedef pair<int, int> pii;
bool sortpos(pii p1, pii p2) { return p1.second < p2.second; }

void solve() {
  int n; cin >> n;
  
  vector<pii> boats(n);
  for (int i = 0; i < n; i++) {
    int blength; cin >> blength;
    int ringpos; cin >> ringpos;
    boats[i] = make_pair(blength, ringpos);
  }
  
  sort(boats.begin(), boats.end(), sortpos);
  int total = 1, freepos = boats[0].second;
  boats.erase(boats.begin());
  
  while (boats.size() > 0) {
    int j = 0, next_ind = 0;
    int nextpos = max(freepos + boats[j].first, boats[j].second);
    
    while (++j < (int) boats.size() && boats[j].second < nextpos) {
      int np = max(freepos + boats[j].first, boats[j].second);
      if (np < nextpos) { nextpos = np; next_ind = j; }
    }
    
    next_ind += 1;
    while (next_ind < (int) boats.size() && boats[next_ind].second < nextpos) next_ind += 1;
    boats.erase(boats.begin(), boats.begin() + next_ind);
    freepos = nextpos;
    total += 1;
  }
  
  cout << total << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}