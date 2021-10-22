#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
typedef pair<int, int> pii;

bool sortlen(pii p1, pii p2) { return p1.first < p2.first; }
bool sortpos(pii p1, pii p2) { return p1.second < p2.second; }

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
  
  int total = 0; // total number of boats
  int freepos = 0; // index of first free space 
  
  for (int i = 0; i < n; i++) {
    int blength = boats[i].first;
    int ringpos = boats[i].second;
    
    // We might need to skip a position with DP later on ?
    if (ringpos >= freepos) {
      total += 1;
      int buffer = ringpos - freepos;
      if (freepos == 0) freepos = ringpos;
      else if (buffer >= blength) freepos = ringpos;
      else freepos = ringpos + blength - buffer;
    }
  }
  
  cout << total << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}