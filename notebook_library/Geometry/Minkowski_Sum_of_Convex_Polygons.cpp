vector<P> minkowski_sum(vector<P> &a, vector<P> &b) {
  auto reorder = [](vector<P> &p) {
    int n = p.size(), idx = 0;
    for (int i = 1; i < n; i++)
      if (p[i].y < p[idx].y || (p[i].y == p[idx].y && p[i].x < p[idx].x)) idx = i;
    rotate(p.begin(), p.begin() + idx, p.end());
  };
  if (a.empty() || b.empty()) return {};
  reorder(a);
  reorder(b);
  a.push_back(a[0]);
  b.push_back(b[0]);
  int n = a.size(), m = b.size();
  vector<P> res;
  for (int i = 0, j = 0; i < n || j < m;) {
    res.push_back(a[i % n] + b[j % m]);
    if (i >= n) j++;
    else if (j >= m) i++;
    else {
      auto ca = a[(i + 1) % n] - a[i % n];
      auto cb = b[(j + 1) % m] - b[j % m];
      if (ca * cb >= 0) i++;
      if (ca * cb <= 0) j++;
    }
  }
  return res;
}
