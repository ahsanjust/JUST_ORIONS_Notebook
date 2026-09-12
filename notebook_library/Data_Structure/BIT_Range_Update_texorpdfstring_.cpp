struct BITRange {
  int n;
  vector<ll> bit1, bit2;
  BITRange(int n) : n(n), bit1(n + 2), bit2(n + 2) {}
  void add(vector<ll>& bit, int i, ll v) {
    for (; i <= n; i += i & -i) bit[i] += v;
  }
  void upd(int l, int r, ll v) {
    add(bit1, l, v);
    add(bit1, r + 1, -v);
    add(bit2, l, v * (l - 1));
    add(bit2, r + 1, -(r * v));
  }
  ll sum(vector<ll>& bit, int i) {
    ll r = 0;
    for (; i > 0; i -= i & -i) r += bit[i];
    return r;
  }
  ll qry(int l, int r) {
    auto pref = [&](int i) { return sum(bit1, i) * i - sum(bit2, i); };
    return pref(r) - pref(l - 1);
  }
};
