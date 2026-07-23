// Circumcircle of three points, returns {center, radius}
pair<PointD, ld> circumcircle(P a, P b, P c) {
  PointD A(a), B(b), C(c);
  PointD ab = B - A, ac = C - A;
  ld d = 2 * ab.cross(ac);
  PointD o(A.x + (ab.sq() * ac.y - ac.sq() * ab.y) / d, A.y + (ac.sq() * ab.x - ab.sq() * ac.x) / d);
  return {o, (o - A).abs()};
}
// Circle-Line: returns number of intersection points
int circle_line(PointD c, ld r, P a, P b, vector<PointD> &res) {
  PointD A(a), B(b), ab = B - A;
  PointD p = A + ab * (((c - A).x * ab.x + (c - A).y * ab.y) / ab.sq());
  ld d = (p - c).abs();
  if (d > r + 1e-9)
    return 0;
  if (fabsl(d - r) < 1e-9) {
    res = {p};
    return 1;
  }
  ld t = sqrtl(r * r - d * d);
  PointD dir = ab / ab.abs() * t;
  res = {p - dir, p + dir};
  return 2;
}
// Circle-Circle: returns number of intersection points
int circle_circle(PointD c1, ld r1, PointD c2, ld r2, vector<PointD> &res) {
  ld d = (c1 - c2).abs();
  if (d > r1 + r2 + 1e-9 || d < fabsl(r1 - r2) - 1e-9)
    return 0;
  if (d < 1e-9 && fabsl(r1 - r2) < 1e-9)
    return -1;
  ld a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  ld h = sqrtl(r1 * r1 - a * a);
  PointD m = c1 + (c2 - c1) * (a / d);
  PointD perp(-(c2 - c1).y * h / d, (c2 - c1).x * h / d);
  res = {m + perp, m - perp};
  return 2;
}
