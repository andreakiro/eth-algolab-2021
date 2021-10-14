#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

void solve() {
  int n; cin >> n;
  int k; cin >> k;
  
  vector<int> vec;
  vector<vector<int>> matrix;
  
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    vec.push_back(x);
  }
  
  // populate the result matrix
  for (int i = 0; i < n; i++) {
    vector<int> v(n - i);
    matrix.push_back(v);
    int cur = vec[i];
    for (int j = 0; j <= i; j++) {
      int prev = 0;
      if (i - j > 0) prev = matrix[j][i - j - 1];
      int partial_sum = prev + cur;
      matrix[j][i - j] = partial_sum;
    }
  }
  
  // seek the best solution [a, b]
  // note : a = bj and b = bi + bj
  int bi = -1; int bj = -1;
  int best = numeric_limits<int>::max();
  
  for (int j = 0; j < (int) matrix.size(); j++) {
    for (int i = 0; i < (int) matrix[j].size(); i++) {
      int x = matrix[j][i];
      int diff = abs(x - k);
      if (diff < best) {
        best = diff;
        bi = i; bj = j;
      }
    }
  }
  
  // output result
  cout << bj << " " << bi + bj << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}