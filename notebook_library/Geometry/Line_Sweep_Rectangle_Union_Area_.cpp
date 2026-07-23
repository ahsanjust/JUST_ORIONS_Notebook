struct Event {
  ll x, y1, y2, type;
  bool operator<(const Event &o) const {
    return x < o.x;
  }
};
struct SegTree {
  vector<int> cnt;
  vector<ll> len, ys;
  int n;
  SegTree(vector<ll> &ys_) : ys(ys_), n(ys_.size() - 1) {
    cnt.assign(4 * n, 0);
    len.assign(4 * n, 0);
  }
  void upd(int i, int l, int r, int ql, int qr, int v) {
    if (ql >= r || qr <= l)
      return;
    if (ql <= l && r <= qr)
      cnt[i] += v;
    else {
      int m = (l + r) / 2;
      upd(i * 2, l, m, ql, qr, v);
      upd(i * 2 + 1, m, r, ql, qr, v);
    }
    if (cnt[i])
      len[i] = ys[r] - ys[l];
    else
      len[i] = (r - l == 1) ? 0 : len[i * 2] + len[i * 2 + 1];
  }
  ll total() {
    return len[1];
  }
};
ll union_area(vector<tuple<ll, ll, ll, ll>> &rects) {
  vector<Event> ev;
  vector<ll> ys;
  for (auto [x1, y1, x2, y2] : rects) {
    ev.push_back({x1, y1, y2, 1});
    ev.push_back({x2, y1, y2, -1});
    ys.push_back(y1);
    ys.push_back(y2);
  }
  sort(ev.begin(), ev.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  SegTree seg(ys);
  ll ans = 0, prev = ev[0].x;
  for (auto &e : ev) {
    ans += (e.x - prev) * seg.total();
    int l = lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin();
    int r = lower_bound(ys.begin(), ys.end(), e.y2) - ys.begin();
    seg.upd(1, 0, seg.n, l, r, e.type);
    prev = e.x;
  }
  return ans;
}
