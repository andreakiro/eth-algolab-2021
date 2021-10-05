#include <iostream>
#include <vector>

using namespace std;

void testcase_quad() {
  int n; cin >> n;
  vector<int> vec;
  vector<int> ps;

  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    vec.push_back(x);
  }
  
  ps.push_back(vec[0]);
  for (int i = 1; i < n; i++)
    ps.push_back(ps[i - 1] + vec[i]);
  
  int count = 0;
  
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      int sum = ps[i] - ps[j] + vec[i];
      if (sum % 2 == 0) count += 1;
    }
  }
  
  cout << count << endl;
}

void testcase_linear() {
  int n; cin >> n;
  vector<int> vec;
  vector<int> ps;

  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    vec.push_back(x);
  }
  
  ps.push_back(vec[0]);
  for (int i = 1; i < n; i++)
    ps.push_back(ps[i - 1] + vec[i]);
  
  int count = 0;
  int even = 0;
  
  for (int i = 0; i < n; i++)
    if (ps[i] % 2 == 0) even += 1;
  
  count += even;
  count += even * (even - 1) / 2;
  count += (n - even) * (n - even - 1) / 2;
  
  cout << count << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase_linear();
}