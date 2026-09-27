// Returns 1 if q is inside or on boundary of convex polygon p (CCW), 0 otherwise
int point_in_convex(P &q, vector<P> &p) {
  int n = p.size();
  auto in_box = [&](P a, P b) {
    return min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) && min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
  };
  int64_t cross_first = (p[1] - p[0]) * (q - p[0]);
  if (cross_first == 0) return in_box(p[0], p[1]);
  if (cross_first < 0) return 0;
  int lo = 1, hi = n - 1;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    if ((p[mid] - p[0]) * (q - p[0]) >= 0) lo = mid;
    else hi = mid - 1;
  }
  int64_t cross_last = (p[(lo + 1) % n] - p[lo]) * (q - p[lo]);
  if (cross_last < 0) return 0;
  if (cross_last == 0) return in_box(p[lo], p[(lo + 1) % n]);
  return 1;
}
