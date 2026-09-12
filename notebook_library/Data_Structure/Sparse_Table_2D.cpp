struct Sparse2D {
  int n, m;
  vector<vector<int>> a;
  vector<int> lg;
  vector<vector<int>> st[11][11];  // st[logA][logB] is a matrix; supports up to 2047
  Sparse2D(int n, int m) : n(n), m(m) {
    a.assign(n, vector<int>(m));
    lg.resize(max(n, m) + 1);
    for (int i = 2; i <= max(n, m); i++) lg[i] = lg[i >> 1] + 1;
  }
  void set_val(int i, int j, int v) { a[i][j] = v; }
  void build() {
    auto &s = st[0][0];
    s.assign(n, vector<int>(m));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) s[i][j] = a[i][j];
    int la = lg[n], lb = lg[m];
    for (int ka = 0; ka <= la; ka++) {
      for (int kb = 0; kb <= lb; kb++) {
        if (ka + kb == 0) continue;
        int pwa = 1 << ka, pwb = 1 << kb;
        auto &cur = st[ka][kb];
        cur.assign(n - pwa + 1, vector<int>(m - pwb + 1));
        for (int i = 0; i + pwa <= n; i++)
          for (int j = 0; j + pwb <= m; j++) {
            if (!ka) cur[i][j] = max(st[ka][kb - 1][i][j], st[ka][kb - 1][i][j + pwb / 2]);
            else cur[i][j] = max(st[ka - 1][kb][i][j], st[ka - 1][kb][i + pwa / 2][j]);
          }
      }
    }
  }
  int qry(int x1, int y1, int x2, int y2) const {
    int a = lg[x2 - x1 + 1], b = lg[y2 - y1 + 1];
    auto &s = st[a][b];
    int m1 = max(s[x1][y1], s[x2 - (1 << a) + 1][y1]);
    int m2 = max(s[x1][y2 - (1 << b) + 1], s[x2 - (1 << a) + 1][y2 - (1 << b) + 1]);
    return max(m1, m2);
  }
};
