#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

using namespace std;
typedef pair<int, int> pii;
typedef vector<map<int, int>> dp;

bool sortpos(pii p1, pii p2) { return p1.second < p2.second; }

int organize(dp &memo, vector<pii> &boats, int i, int fp) {
  if (i == (int) boats.size()) return 0;
  if (memo[i].find(fp) != memo[i].end()) return memo[i].at(fp);
  
  int freepos;
  int blength = boats[i].first;
  int ringpos = boats[i].second;
  
  if (ringpos >= fp) {
    int buffer = ringpos - fp;
    if (fp == 0) freepos = ringpos;
    else if (buffer >= blength) freepos = ringpos;
    else freepos = ringpos + blength - buffer;
    int total = max(organize(memo, boats, i + 1, freepos) + 1, organize(memo, boats, i + 1, fp));
    memo[i].insert(make_pair(fp, total));
    return total;
  } else {
    int total = organize(memo, boats, i + 1, fp);
    memo[i].insert(make_pair(fp, total));
    return total;
  }
}

void solve() {
  int n; cin >> n;
  
  vector<pii> boats(n);
  for (int i = 0; i < n; i++) {
    int blength; cin >> blength;
    int ringpos; cin >> ringpos;
    boats[i] = make_pair(blength, ringpos);
  }
  
  // Sort according to the ring positions
  sort(boats.begin(), boats.end(), sortpos);
  
  // Create memo table
  dp memo(n, map<int, int>());
  
  cout << organize(memo, boats, 0, 0) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}