struct BIT2D {
  int n, m;
  vector<vector<ll>> bit;
  BIT2D(int n, int m) : n(n), m(m) { bit.assign(n + 1, vector<ll>(m + 1, 0)); }
  void add(int x, int y, ll val) {
    for (int i = x; i <= n; i += i & -i)
      for (int j = y; j <= m; j += j & -j) bit[i][j] += val;
  }
  ll sum(int x, int y) {
    ll res = 0;
    for (int i = x; i > 0; i -= i & -i)
      for (int j = y; j > 0; j -= j & -j) res += bit[i][j];
    return res;
  }
  ll query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
  }
};
BIT2D fenw2(4, 4);
fenw2.add(1, 1, 5);
fenw2.add(3, 2, 7);
cout << fenw2.query(1, 1, 3, 3) << "\n";
