struct LSeg {
  int n;
  vector<ll> sm, mx, mn, ad, st;
  const ll INF = 1e18, NO_SET = 9e18;
  LSeg(int n) : n(n), sm(4 * n), mx(4 * n), mn(4 * n), ad(4 * n), st(4 * n, NO_SET) {}
  void pull(int i) {
    sm[i] = sm[i * 2] + sm[i * 2 + 1];
    mx[i] = max(mx[i * 2], mx[i * 2 + 1]);
    mn[i] = min(mn[i * 2], mn[i * 2 + 1]);
  }
  void pset(int i, int s, int e, ll v) {
    st[i] = v;
    ad[i] = 0;
    sm[i] = v * (e - s + 1);
    mx[i] = mn[i] = v;
  }
  void padd(int i, int s, int e, ll v) {
    if (st[i] != NO_SET) st[i] += v;
    else ad[i] += v;
    sm[i] += v * (e - s + 1);
    mx[i] += v;
    mn[i] += v;
  }
  void push(int i, int s, int e) {
    if (s == e) return;
    int m = (s + e) / 2;
    if (st[i] != NO_SET) {
      pset(i * 2, s, m, st[i]);
      pset(i * 2 + 1, m + 1, e, st[i]);
      st[i] = NO_SET;
    }
    if (ad[i]) {
      padd(i * 2, s, m, ad[i]);
      padd(i * 2 + 1, m + 1, e, ad[i]);
      ad[i] = 0;
    }
  }
  void upd(int l, int r, ll v, int t, int i = 1, int s = 0, int e = -1) {
    if (e < 0) e = n - 1;
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
      t ? pset(i, s, e, v) : padd(i, s, e, v);
      return;
    }
    push(i, s, e);
    int m = (s + e) / 2;
    upd(l, r, v, t, i * 2, s, m);
    upd(l, r, v, t, i * 2 + 1, m + 1, e);
    pull(i);
  }
  array<ll, 3> qry(int l, int r, int i = 1, int s = 0, int e = -1) {
    if (e < 0) e = n - 1;
    if (r < s || e < l) return {0, -INF, INF};
    if (l <= s && e <= r) return {sm[i], mx[i], mn[i]};
    push(i, s, e);
    int m = (s + e) / 2;
    auto a = qry(l, r, i * 2, s, m), b = qry(l, r, i * 2 + 1, m + 1, e);
    return {a[0] + b[0], max(a[1], b[1]), min(a[2], b[2])};
  }
  void set(int l, int r, ll v) { upd(l, r, v, 1); }
  void add(int l, int r, ll v) { upd(l, r, v, 0); }
  // auto [s,mx,mn]=seg.qry(l,r);
  // seg.set(l,r,v); seg.add(l,r,v);
};