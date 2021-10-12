#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;

void drain(int i, int n) {
  while (i < n) {
    long w, x, y, z;
    cin >> w >> x >> y >> z;
    i += 1;
  }
}

void solve(int n) {
  long x1, y1; cin >> x1 >> y1;
  long x2, y2; cin >> x2 >> y2;
  
  Point source(x1, y1);
  Point target(x2, y2);
  Ray r(source, target);

  bool intersect = false;
  
  for (int i = 0; i < n; i++) {
    Point p1, p2; cin >> p1 >> p2;
    Segment s(p1, p2);
    if (CGAL::do_intersect(r, s)) {
      intersect = true;
      drain(i + 1, n);
      break;
    }
  }

  if (intersect) cout << "yes" << endl;
  else cout << "no" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while (n != 0) {
    solve(n);
    cin >> n;
  }
}