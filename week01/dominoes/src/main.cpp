#include <iostream>
#include <vector>

using namespace std;

void testcase() {
  int n; cin >> n;
  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x; cin >> x; 
    v.push_back(x - 1);
  }
  
  int count = 0; // falled dominoes
  int reach = 0; // index based
  
  for (int i = 0; i < (int) v.size(); i++) {
    count++;
    int cur = v[i];
    if (cur == 0 and reach == i) break;
    if (i + cur > reach) reach = i + cur;
  }
  
  cout << count << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase();
}