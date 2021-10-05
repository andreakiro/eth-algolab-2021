#include <iostream>

using namespace std;

void testcase() {
  int n; cin >> n;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    sum += x;
  }
  cout << sum << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase();
}