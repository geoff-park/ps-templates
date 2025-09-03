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

typedef vector<vector2> polygon;

// Rotating Calipers: 볼록 다각형의 지름을 구한다.

double diameter(const polygon& p) {
  int n = p.size();  // 다각형 p의 꼭짓점 개수

  // 우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다.
  int left = min_element(p.begin(), p.end()) - p.begin();   // 두 이터레이터의 차이 = 인덱스
  int right = max_element(p.begin(), p.end()) - p.begin();  // 두 이터레이터의 차이 = 인덱스
  // left: 가장 왼쪽 점의 index
  // right: 가장 오른쪽 점의 index

  // p[left]와 p[right]에 각각 수직선을 붙인다.
  // 두 수직선은 서로 정반대 방향을 가리키므로, A의 방향만을 표현하면 된다.
  vector2 calipersA(0, 1);
  double ret = (p[right] - p[left]).norm();

  // toNext[i] = p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
  vector<vector2> toNext(n);
  for (int i = 0; i < n; ++i) {
    toNext[i] = (p[(i + 1) % n] - p[i]).normalize();
  }
  // a와 b는 각각 두 선분이 어디로 붙은 채로 회전하고 있는지를 나타낸다.
  int a = left, b = right;

  // 반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다.
  while (a != right || b != left) {
    // a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
    double cosThetaA = calipersA.dot(toNext[a]);
    double cosThetaB = (calipersA * (-1)).dot(toNext[b]);

    if (cosThetaA > cosThetaB) {  // thetaA < thetaB
      calipersA = toNext[a];
      a = (a + 1) % n;
    } else {
      calipersA = toNext[b] * (-1);
      b = (b + 1) % n;
    }

    ret = max(ret, (p[a] - p[b]).norm());
  }

  return ret;
}