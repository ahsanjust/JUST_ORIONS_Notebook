struct Line {
  double a, b, c;  // ax + by <= c
  double ang;
  Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {
    ang = atan2(b, a);
  }
  bool operator<(const Line &o) const {
    return ang < o.ang;
  }
};
pair<double, double> intersect(Line &p, Line &q) {
  double d = p.a * q.b - p.b * q.a;
  return {(p.c * q.b - q.c * p.b) / d, (p.a * q.c - q.a * p.c) / d};
}
bool ok(Line &a, Line &b, Line &c) {
  auto [x, y] = intersect(a, b);
  return c.a * x + c.b * y < c.c + 1e-9;
}
vector<pair<double, double>> halfPlaneIntersection(vector<Line> v) {
  sort(v.begin(), v.end());
  vector<Line> filtered;
  for (int i = 0; i < (int)v.size(); i++) {
    if (i > 0 && abs(v[i].ang - v[i - 1].ang) < 1e-9) {
      if (v[i].c < filtered.back().c)
        filtered.back() = v[i];
    } else
      filtered.push_back(v[i]);
  }
  v = filtered;
  deque<Line> dq;
  for (auto &l : v) {
    while (dq.size() >= 2 && !ok(dq[dq.size() - 2], dq.back(), l))
      dq.pop_back();
    while (dq.size() >= 2 && !ok(dq[0], dq[1], l))
      dq.pop_front();
    dq.push_back(l);
  }
  while (dq.size() >= 3 && !ok(dq[dq.size() - 2], dq.back(), dq[0]))
    dq.pop_back();
  while (dq.size() >= 3 && !ok(dq[0], dq[1], dq.back()))
    dq.pop_front();
  vector<pair<double, double>> res;
  for (int i = 0; i < (int)dq.size(); i++)
    res.push_back(intersect(dq[i], dq[(i + 1) % dq.size()]));
  return res;
}
