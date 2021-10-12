#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
typedef vector<int> VINT;
typedef vector<VINT> VVINT;
typedef vector<VVINT> VVVINT;

int win_pos;

int move(VVVINT &memo, VVINT &trans, int r, int b, int turn) {
  // Who plays what
  int mod = turn % 4;
  
  // We might already know this setting outcome
  if (memo[r][b][mod] != -1) return memo[r][b][mod];
  
  if (mod == 0) {
    // Holmes moves red meeple
    if (r == win_pos) return memo[r][b][mod] = 0;
    // Possible paths and their outcome
    vector<int> poss = trans[r];
    vector<int> out(poss.size(), -1);
    for (int i = 0; i < (int) poss.size(); i++)
      out[i] = move(memo, trans, poss[i], b, turn + 1);
    // Holmes (0) takes any path to try winning the game
    int argmin = min_element(out.begin(), out.end()) - out.begin();
    return memo[r][b][mod] = out[argmin];
    
  } else if (mod == 1) {
    // Moriarty moves black meeple
    if (b == win_pos) return memo[r][b][mod] = 1;
    // Possible paths and their outcome
    vector<int> poss = trans[b];
    vector<int> out(poss.size(), -1);
    for (int i = 0; i < (int) poss.size(); i++)
      out[i] = move(memo, trans, r, poss[i], turn + 1);
    // Moriarty (1) takes any path to try winning the game
    int argmax = max_element(out.begin(), out.end()) - out.begin();
    return memo[r][b][mod] = out[argmax];
    
  } else if (mod == 2) {
    // Holmes moves black meeple
    if (b == win_pos) return memo[r][b][mod] = 1;
    vector<int> poss = trans[b];
    vector<int> out(poss.size(), -1);
    for (int i = 0; i < (int) poss.size(); i++)
      out[i] = move(memo, trans, r, poss[i], turn + 1);
    int argmin = min_element(out.begin(), out.end()) - out.begin();
    return memo[r][b][mod] = out[argmin];
    
  } else {
    // Moriarty moves red meeple
    if (r == win_pos) return memo[r][b][mod] = 0;
    vector<int> poss = trans[r];
    vector<int> out(poss.size(), -1);
    for (int i = 0; i < (int) poss.size(); i++)
      out[i] = move(memo, trans, poss[i], b, turn + 1);
    int argmax = max_element(out.begin(), out.end()) - out.begin();
    return memo[r][b][mod] = out[argmax];
  }
}

void testcase() {
  int n; cin >> n; // positions
  int m; cin >> m; // transitions
  int r; cin >> r; // RED starting index (1 < i < n)
  int b; cin >> b; // BLACK starting index (1 < i < n)
  
  win_pos = n - 2;
  vector<VINT> transitions(n - 1, VINT());
  vector<VVINT> memo(n - 1, VVINT(n - 1, VINT(4, -1)));
  
  for (int i = 0; i < m; i++) {
    int source; cin >> source;
    int target; cin >> target;
    transitions[source - 1].push_back(target - 1);
  }
  
  int winner = move(memo, transitions, r - 1, b - 1, 0);
  cout << winner << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for (int i = 0; i < t; i++) testcase();
}