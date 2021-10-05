#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void insert_pos(vector<int> &locations, float x) {
  int x_floor = floor(x);
  int x_ceil = ceil(x);
  if (abs(x - x_floor) > 0) {
    locations.push_back(x_floor);
    locations.push_back(x_ceil);
  } else locations.push_back(x);
}

void testcase() {
  int n; cin >> n;
  
  vector<int> ps_coords(n); // parasols coords
  for (int i = 0; i < n; i++) cin >> ps_coords[i];
  sort(ps_coords.begin(), ps_coords.end());
  
  vector<int> locations; // best positions
  int i = 0, best_dist = 0, best_clients = 1;
  locations.push_back(i);
  
  for (int j = 1; j < n; j++) {
    while (i < j && ps_coords[j] - ps_coords[i] > 200) i++;
    float bar_coord =  (float) (ps_coords[i] + ps_coords[j]) / 2.f;
    int d1 = abs(ps_coords[i] - ceil(bar_coord));
    int d2 = abs(ps_coords[j] - ceil(bar_coord));
    int max_dist = std::max(d1, d2);
    int clients = j - i + 1;
    
    if (clients == best_clients && best_dist == max_dist) insert_pos(locations, bar_coord);
    else if ((clients > best_clients) || (clients == best_clients && best_dist > max_dist)) {
      locations.clear();
      best_clients = clients;
      best_dist = max_dist;
      insert_pos(locations, bar_coord);    
    }
  }
  
  cout << best_clients << " " << best_dist << "\n";
  for (int pos : locations) cout << pos << " ";
  cout << endl;
}

int main(int argc, char const *argv[]) {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; i++) testcase();
}