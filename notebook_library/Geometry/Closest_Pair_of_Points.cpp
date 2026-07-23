struct Res {
  int64_t d;
  P a, b;
};
int64_t sq(int64_t x) {
  return x * x;
}
int64_t dist_sq(P& a, P& b) {
  return sq(a.x - b.x) + sq(a.y - b.y);
}
Res closest_pair(vector<P>& p, vector<P>& py, vector<P>& tmp, int l, int r) {
  int n = r - l + 1;
  if (n <= 1)
    return {LLONG_MAX, {}, {}};
  if (n == 2) {
    if (py[l].y > py[l + 1].y)
      swap(py[l], py[l + 1]);
    return {dist_sq(p[l], p[l + 1]), p[l], p[l + 1]};
  }
  int m = (l + r) >> 1, midx = p[m].x;
  Res res_l = closest_pair(p, py, tmp, l, m);
  Res res_r = closest_pair(p, py, tmp, m + 1, r);
  Res res = (res_l.d < res_r.d ? res_l : res_r);
  for (int i = l, j = m + 1, k = l; k <= r; k++) {
    if (j > r || (i <= m && py[i].y < py[j].y))
      tmp[k] = py[i++];
    else
      tmp[k] = py[j++];
  }
  for (int i = l; i <= r; i++)
    py[i] = tmp[i];
  vector<P> stripe;
  for (int i = l; i <= r; i++)
    if (sq(py[i].x - midx) < res.d)
      stripe.push_back(py[i]);
  for (int i = 0; i < (int)stripe.size(); i++) {
    for (int j = i + 1; j < (int)stripe.size(); j++) {
      if (sq(stripe[i].y - stripe[j].y) >= res.d)
        break;
      int64_t d = dist_sq(stripe[i], stripe[j]);
      if (d < res.d)
        res = {d, stripe[i], stripe[j]};
    }
  }
  return res;
}
