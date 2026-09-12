const ld EPS = 1e-9;
const ld PI = acos(-1.0);
// sign: -1/0/1 for negative/zero/positive
int sgn(ld x) {
  return (x > EPS) - (x < -EPS);
}
// 2D point with int64 coords: cross(*), dot(^),
// norm(sq), abs, rotation
struct P {
  using T = int64_t;
  T x, y;
  void read() { cin >> x >> y; }
  P operator-(const P &b) const { return P{x - b.x, y - b.y}; }
  P operator+(const P &b) const { return P{x + b.x, y + b.y}; }
  template <class U>
  P operator*(const U &c) const {
    return P{(T)(x * c), (T)(y * c)};
  }
  template <class U>
  P operator/(const U &c) const {
    return P{(T)(x / c), (T)(y / c)};
  }
  bool operator<(const P &b) const { return x == b.x ? y < b.y : x < b.x; }
  bool operator==(const P &b) const { return x == b.x && y == b.y; }
  T operator*(const P &b) const { return x * b.y - y * b.x; }
  T operator^(const P &b) const { return x * b.x + y * b.y; }
  T dot(P &a, P &b) const { return (a - *this) ^ (b - *this); }
  T cross(P &a, P &b) { return (a - *this) * (b - *this); }
  ld sq() const { return x * x + y * y; }
  ld abs() const { return sqrtl(sq()); }
  P rot() const { return P(-y, x); }  // 90 CCW
  P rot(ld a) const { return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};
// true if a, b, c lie on same line
bool collinear(P &a, P &b, P &c) {
  return (b - a) * (c - a) == 0;
}
// true if r lies on closed segment pq
bool on_segment(P &p, P &q, P &r) {
  return collinear(p, q, r) && r.x <= max(p.x, q.x) && r.x >= min(p.x, q.x) && r.y <= max(p.y, q.y) &&
         r.y >= min(p.y, q.y);
}
// Euclidean distance between a and b
ld dist_euclid(P a, P b) {
  return (a - b).abs();
}
// project c onto line ab (returns foot point)
P project(P a, P b, P c) {
  return a + (b - a) * (((c - a) ^ (b - a)) / (b - a).sq());
}
// reflect c across line ab
P reflect(P a, P b, P c) {
  return project(a, b, c) * 2 - c;
}
// perpendicular dist from c to line ab
ld dist_pt_line(P a, P b, P c) {
  return fabsl((b - a) * (c - a)) / (b - a).abs();
}
// shortest dist from c to segment ab
ld dist_pt_seg(P a, P b, P c) {
  if (((c - a) ^ (b - a)) <= 0) return (c - a).abs();
  if (((c - b) ^ (a - b)) <= 0) return (c - b).abs();
  return dist_pt_line(a, b, c);
}
// true if p lies on segment ab (EPS tolerance)
bool on_seg(P a, P b, P p) {
  return !sgn((b - a) * (p - a)) && ((p - a) ^ (p - b)) <= EPS;
}
// line-line intersection (ab x cd), stores in res,
// returns false if parallel
bool line_int(P a, P b, P c, P d, P &res) {
  ld cp = (b - a) * (d - c);
  if (!sgn(cp)) return false;
  res = a + (b - a) * (((c - a) * (d - c)) / cp);
  return true;
}
// true if segment ab intersects segment cd
bool seg_int(P a, P b, P c, P d) {
  auto cp = [&](P x, P y, P z) { return sgn((y - x) * (z - x)); };
  if (on_seg(a, b, c) || on_seg(a, b, d) || on_seg(c, d, a) || on_seg(c, d, b)) return true;
  return cp(a, b, c) != cp(a, b, d) && cp(c, d, a) != cp(c, d, b);
}
// area of polygon (shoelace), vertices in order (strict CCW or CW)
long double polygon_area(vector<P> &p) {
  int64_t area = 0, n = p.size();
  for (int i = 0; i < n; ++i) area += p[i] * p[(i + 1) % n];
  return (long double)abs(area) / 2.0L;
}
// convex hull vertices (CCW, monotone chain)
vector<P> convexHull(vector<P> p) {
  int n = p.size(), k = 0;
  if (n <= 2) return p;
  vector<P> h(2 * n);
  sort(p.begin(), p.end());
  for (int i = 0; i < n; h[k++] = p[i++])
    while (k >= 2 && h[k - 2].cross(h[k - 1], p[i]) <= 0) k--;
  for (int i = n - 2, t = k + 1; i >= 0; h[k++] = p[i--])
    while (k >= t && h[k - 2].cross(h[k - 1], p[i]) <= 0) k--;
  h.resize(k - 1);
  return h;
}
// point-in-polygon: 1=inside, 2=on boundary, 0=out
int is_point_in_polygon(const vector<P> &p, P q) {
  int c = 0;
  for (int i = 0, n = p.size(); i < n; ++i) {
    P a = p[i], b = p[(i + 1) % n];
    if ((b - a) * (q - a) == 0 && min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) && min(a.y, b.y) <= q.y &&
        q.y <= max(a.y, b.y))
      return 2;
    if ((a.y > q.y) != (b.y > q.y) && ((b - a) * (q - a) > 0) == (a.y < b.y)) c = !c;
  }
  return c;
}
