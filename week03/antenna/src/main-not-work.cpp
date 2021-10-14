///1
#include <iostream>
#include <vector>
#include <climits>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return a;
}

void solve(int n) {
  int best_high = INT_MIN;
  int best_left = INT_MAX;
  int best_low = INT_MAX;
  int best_right = INT_MIN;
  
  vector<Point> points;
  
  for (int i = 0; i < n; i++) {
    int x, y;cin >> x >> y;
    Point p(x, y); bool addP = false;
    if (x >= best_right) { best_right = x; addP = true; } 
    if (x <= best_left)  { best_left  = x; addP = true; }
    if (y >= best_high)  { best_high  = y; addP = true; }
    if (y <= best_low)   { best_low   = y; addP = true; }
    if (addP) points.push_back(p);
  }
  
  Point MidP_High  ((best_right + best_left) / 2, best_high);
  Point MidP_Low   ((best_right + best_left) / 2, best_low);
  Point MidP_Right (best_right, (best_high + best_low) / 2);
  Point MidP_Left  (best_left, (best_high + best_low) / 2);
  
  Segment vertical(MidP_High, MidP_Low);
  Segment horizontal(MidP_Right, MidP_Left);
  
  Point center;
  auto o = CGAL::intersection(vertical, horizontal);
  if (const Point* op = boost::get<Point>(&*o)) center = *op;
  else {
    Point a (0,0); center = a;
  }
  /*else cout << "unexcepted errror" << endl;*/
  
  double sqradius = -1.0;
  for (Point p: points) {
    K::FT ft_sqdist = CGAL::squared_distance(center, p);
    double sqdist = floor_to_double(ft_sqdist);
    if (sqdist > sqradius) sqradius = sqdist;
  }
  
  cout << ceil(sqrt(sqradius)) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while (n != 0) {
    solve(n);
    cin >> n;
  }
}