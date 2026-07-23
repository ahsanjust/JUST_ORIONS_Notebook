struct PST {
  struct Node {
    int l, r, val;
  };
  vector<Node> t = {{0, 0, 0}};

  int build(int b, int e) {
    if (b == e) {
      t.push_back({0, 0, 0});
      return t.size() - 1;
    }
    int m = (b + e) / 2, cur = t.size();
    t.push_back({build(b, m), build(m + 1, e), 0});
    return cur;
  }
  int upd(int pre, int b, int e, int i, int v) {
    int cur = t.size();
    t.push_back(t[pre]);
    if (b == e) {
      t[cur].val += v;
      return cur;
    }
    int m = (b + e) / 2;
    if (i <= m)
      t[cur].l = upd(t[pre].l, b, m, i, v);
    else
      t[cur].r = upd(t[pre].r, m + 1, e, i, v);
    t[cur].val = t[t[cur].l].val + t[t[cur].r].val;
    return cur;
  }
  int kth(int pre, int cur, int b, int e, int k) {
    if (b == e)
      return b;
    int cnt = t[t[cur].l].val - t[t[pre].l].val;
    int m = (b + e) / 2;
    if (cnt >= k)
      return kth(t[pre].l, t[cur].l, b, m, k);
    return kth(t[pre].r, t[cur].r, m + 1, e, k - cnt);
  }
  int cnt(int pre, int cur, int b, int e, int x) {
    if (x < b)
      return 0;
    if (b == e)
      return t[cur].val - t[pre].val;
    int m = (b + e) / 2;
    if (x <= m)
      return cnt(t[pre].l, t[cur].l, b, m, x);
    return (t[t[cur].l].val - t[t[pre].l].val) + cnt(t[pre].r, t[cur].r, m + 1, e, x);
  }
  int sum(int pre, int cur, int b, int e, int l, int r) {
    if (l > e || r < b)
      return 0;
    if (l <= b && e <= r)
      return t[cur].val - t[pre].val;
    int m = (b + e) / 2;
    return sum(t[pre].l, t[cur].l, b, m, l, r) + sum(t[pre].r, t[cur].r, m + 1, e, l, r);
  }
};
