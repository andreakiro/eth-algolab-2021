#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> MinCircle;
typedef K::Point_2 Point;

double ceil_to_double(const K::FT& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void solve(int n) {
  vector<Point> points(n);
  for(int i = 0; i < n; i++) {
    long x, y; cin >> x >> y;
    points[i] = Point(x, y);
  }

  MinCircle mc(points.begin(), points.end(), true);
  K::FT sqradius = mc.circle().squared_radius();
  double radius = ceil_to_double(sqrt(sqradius));
  
  cout << fixed << setprecision(0);
  cout << radius << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while(n != 0) {
    solve(n);
    cin >> n;
  }
}