// Returns 1 if q is inside or on boundary of convex polygon p (CCW), 0 otherwise
int point_in_convex(P &q, vector<P> &p) {
  int n = p.size();
  int64_t cross_first = (p[1] - p[0]) * (q - p[0]);
  if (cross_first == 0) {
    return min(p[0].x, p[1].x) <= q.x && q.x <= max(p[0].x, p[1].x) && min(p[0].y, p[1].y) <= q.y &&
           q.y <= max(p[0].y, p[1].y);
  }
  if (cross_first < 0)
    return 0;
  int lo = 1, hi = n - 1;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    if ((p[mid] - p[0]) * (q - p[0]) >= 0)
      lo = mid;
    else
      hi = mid - 1;
  }
  int64_t cross_last = (p[(lo + 1) % n] - p[lo]) * (q - p[lo]);
  if (cross_last < 0)
    return 0;
  if (cross_last == 0) {
    P a = p[lo], b = p[(lo + 1) % n];
    return min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) && min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
  }
  return 1;
}
