#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> vint;

bool desc(int i1, int i2) { return i1 > i2; }

void printres(vector<int> &res) {
  for (int i = 0; i < (int) res.size(); i++) cout << res[i] << " ";
  cout << endl;
}

void pick(vint &moved_books, vint &friends, vint &books, int offset_f, int offset_b) {
  int nf = (int) friends.size();
  int nb = (int) books.size();
  
  int i = 0;
  while (i + offset_f < nf && i + offset_b < nb) {
    if (friends[i + offset_f] >= books[i + offset_b]) { 
      // We will move the book at index i+offset_b
      moved_books.push_back(i + offset_b); i += 1;
    } else {
      int j = i; // Reach first book that weaker friends can carry
      while (j + offset_b < nb && friends[i + offset_f] < books[j + offset_b]) j += 1;
      if (j + offset_b == nb) return; // No friend can carry remaining books
      else {
        moved_books.push_back(j + offset_b);
        pick(moved_books, friends, books, i + 1 + offset_f, j + 1 + offset_b);
      }
      return;
    }
  }
}

void solve() {
  int n; cin >> n;
  int m; cin >> m;
  
  vector<int> friends(n);
  vector<int> books(m);
  
  for (int i = 0; i < n; i++) cin >> friends[i];
  for (int i = 0; i < m; i++) cin >> books[i];
  
  sort(friends.begin(), friends.end(), desc);
  sort(books.begin(), books.end(), desc);
  
  if (friends[0] < books[0]) {
    cout << "impossible" << endl;
    return;
  }

  int ts = 0; // timestamp
  while (books.size() > 0) {
    vector<int> moved_books;
    pick(moved_books, friends, books, 0, 0);
    sort(moved_books.begin(), moved_books.end());
    for (int i = 0; i < (int) moved_books.size(); i++)
      books.erase(books.begin() + moved_books[i] - i);
    ts += 3;
  }
  
  cout << ts - 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) solve();
}