struct LiChao {
  struct Line {
    ll m, b;
    ll get(ll x) {
      return m * x + b;
    }
  };
  struct Node {
    int l, r;
    Line line;
  };
  vector<Node> seg;
  LiChao() {
    seg.push_back({-1, -1, {0, LLONG_MAX}});
  }
  void addLine(Line nw, int idx = 0, ll l = -1e9, ll r = 1e9) {
    ll m = l + (r - l) / 2;
    bool left = nw.get(l) < seg[idx].line.get(l);
    bool mid = nw.get(m) < seg[idx].line.get(m);
    if (mid)
      swap(seg[idx].line, nw);
    if (l == r)
      return;
    if (left != mid) {
      if (seg[idx].l == -1) {
        seg[idx].l = seg.size();
        seg.push_back({-1, -1, {0, LLONG_MAX}});
      }
      addLine(nw, seg[idx].l, l, m);
    } else {
      if (seg[idx].r == -1) {
        seg[idx].r = seg.size();
        seg.push_back({-1, -1, {0, LLONG_MAX}});
      }
      addLine(nw, seg[idx].r, m + 1, r);
    }
  }
  ll query(ll x, int idx = 0, ll l = -1e9, ll r = 1e9) {
    if (idx == -1)
      return LLONG_MAX;
    ll m = l + (r - l) / 2;
    ll res = seg[idx].line.get(x);
    if (l != r) {
      if (x <= m)
        res = min(res, query(x, seg[idx].l, l, m));
      else
        res = min(res, query(x, seg[idx].r, m + 1, r));
    }
    return res;
  }
};
// LiChao lct; lct.addLine({slope, intercept});
// ll ans = lct.query(x);
