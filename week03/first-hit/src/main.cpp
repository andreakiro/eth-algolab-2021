#include <iostream>
#include <vector>
#include <algorithm>
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
  long x1, y1; cin >> x1 >> y1;
  long x2, y2; cin >> x2 >> y2;
  
  Point source(x1, y1);
  Point target(x2, y2);
  Ray r(source, target);
  Segment r_seg;
  
  vector<Segment> segments;
  
  for (int i = 0; i < n; i++) {
    long w, x, y, z;
    cin >> w >> x >> y >> z;
    Point p1(w, x); Point p2(y ,z);
    Segment s(p1, p2);
    segments.push_back(s);
  }
  
  random_shuffle(segments.begin(), segments.end());
  
  bool intersected = false;
  K::FT best_distance = -1;
  
  for (int i = 0; i < n; i++) {
    Segment s = segments[i];
    bool intersect = false;
    if (intersected) intersect = CGAL::do_intersect(r_seg, s);
    else intersect = CGAL::do_intersect(r, s);
    if (intersect) {
      intersected = true;
      Point intersection;
      auto o = CGAL::intersection(r, s);
      if (const Point* op = boost::get<Point>(&*o)) intersection = *op;
      else if (const Segment* os = boost::get<Segment>(&*o)) {
        K::FT sqd1 = CGAL::squared_distance(source, os->source());
        K::FT sqd2 = CGAL::squared_distance(source, os->target());
        if (sqd1 < sqd2) intersection = os->source();
        else intersection = os->target();
      }
      
      K::FT cur_distance = CGAL::squared_distance(source, intersection);
      if (cur_distance < best_distance || best_distance == -1) {
        best_distance = cur_distance;
        Segment seg(source, intersection);
        r_seg = seg;
      } 
    }
  }

  if (!intersected) cout << "no" << endl;
  else {
    cout << setiosflags(ios::fixed) << setprecision(0);
    cout << floor_to_double(r_seg.target().x()) << " ";
    cout << floor_to_double(r_seg.target().y()) << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while (n != 0) {
    solve(n);
    cin >> n;
  }
}