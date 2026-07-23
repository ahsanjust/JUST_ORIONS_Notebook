struct PointD {
  ld x, y;
  PointD(ld x = 0, ld y = 0) : x(x), y(y) {}
  PointD(P p) : x(p.x), y(p.y) {}
  PointD operator+(PointD p) const {
    return {x + p.x, y + p.y};
  }
  PointD operator-(PointD p) const {
    return {x - p.x, y - p.y};
  }
  PointD operator*(ld c) const {
    return {x * c, y * c};
  }
  PointD operator/(ld c) const {
    return {x / c, y / c};
  }
  ld cross(PointD p) const {
    return x * p.y - y * p.x;
  }
  ld sq() const {
    return x * x + y * y;
  }
  ld abs() const {
    return sqrtl(sq());
  }
};
struct Circle {
  PointD c;
  ld r;
};
Circle welzl(vector<P> &pts) {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  vector<PointD> p(pts.begin(), pts.end());
  shuffle(p.begin(), p.end(), rng);
  auto circum = [](PointD a, PointD b, PointD c) {
    PointD ab = b - a, ac = c - a;
    ld d = 2 * ab.cross(ac);
    PointD o(a.x + (ab.sq() * ac.y - ac.sq() * ab.y) / d, a.y + (ac.sq() * ab.x - ab.sq() * ac.x) / d);
    return Circle{o, (o - a).abs()};
  };
  function<Circle(int, vector<PointD> &)> f = [&](int i, vector<PointD> &b) -> Circle {
    if (i == (int)p.size() || b.size() == 3) {
      if (b.empty())
        return {{0, 0}, 0};
      if (b.size() == 1)
        return {b[0], 0};
      if (b.size() == 2)
        return {(b[0] + b[1]) / 2, (b[0] - b[1]).abs() / 2};
      return circum(b[0], b[1], b[2]);
    }
    Circle c = f(i + 1, b);
    if ((c.c - p[i]).abs() > c.r + 1e-9) {
      b.push_back(p[i]);
      c = f(i + 1, b);
      b.pop_back();
    }
    return c;
  };
  vector<PointD> b;
  return f(0, b);
}
// welzl(p).r is the radius of the minimum enclosing circle
