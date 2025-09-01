#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0);

struct vector2 {
  double x, y;
  explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
  bool operator==(const vector2& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator<(const vector2& rhs) const { return x != rhs.x ? x < rhs.x : y < rhs.y; }
  vector2 operator+(const vector2& rhs) const { return vector2(x + rhs.x, y + rhs.y); }
  vector2 operator-(const vector2& rhs) const { return vector2(x - rhs.x, y - rhs.y); }
  vector2 operator*(double rhs) const { return vector2(x * rhs, y * rhs); }
  double norm() const { return hypot(x, y); }
  vector2 normalize() const { return vector2(x / norm(), y / norm()); }
  double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }
  double dot(const vector2& rhs) const { return x * rhs.x + y * rhs.y; }
  double cross(const vector2& rhs) const { return x * rhs.y - rhs.x * y; }
  vector2 project(const vector2& rhs) const {
    vector2 r = rhs.normalize();
    return r * r.dot(*this);
  }
};

double ccw(vector2 a, vector2 b) { return a.cross(b); }
double ccw(vector2 p, vector2 a, vector2 b) { return ccw(a - p, b - p); }

/* 코드 15.13 볼록 껍질을 찾는 선물 포장 알고리즘의 구현 */

typedef vector<vector2> polygon;

// points에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
polygon giftWrap(const vector<vector2>& points) {
  int n = points.size();
  polygon hull;

  // 가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
  vector2 pivot = *min_element(points.begin(), points.end());
  hull.push_back(pivot);

  while (true) {
    // ph에서 시작하는 벡터가 가장 왼쪽인 점 next를 찾는다.
    // 평행인 점이 여러 개 있으면 가장 먼 것을 선택한다.

    vector2 ph = hull.back(), next = points[0];
    // ph(previous hull): 현재까지 구한 볼록껍질의 마지막 점
    // next: "다음에 갈 후보 점"의 초기값

    // for문 역할: next 후보를 갱신해 가면서 가장 바깥쪽 점 하나를 확정
    for (int i = 1; i < n; ++i) {
      double cross = ccw(ph, next, points[i]);
      // ph->next 와 ph->points[i] 두 벡터의 상대 각도를 본다.
      // cross > 0 이면 points[i]가 next보다 더 왼쪽 (바깥쪽)

      double dist = (next - ph).norm() - (points[i] - ph).norm();  // 거리 미리 계산 (일직선 경우 대비)

      if (cross > 0 || (cross == 0 && dist < 0)) next = points[i];
      // 왼쪽으로 더 꺽이는 점이 나오면 무조건 교체
      // 일직선(cross == 0)이면 더 먼점으로 교체
    }

    if (next == pivot) break;  // 시작점으로 돌아왔으면 종료한다.
    hull.push_back(next);      // next를 볼록 껍질에 포함시킨다.
  }

  return hull;
}

/* 시간 복잡도 분석

- while문은 볼록 껍질에 점이 하나 추가될 때마다 반복 수행
- 그 안에서는 O(N) 시간의 반복문 수행
- 볼록 껍질에 포함된 점의 수가 H라고 할 때, 전체 시간 복잡도는 O(NH)
- 최악의 경우: O(N^2) (N개의 점이 모두 볼록 껍질에 포함되는 경우)

*/