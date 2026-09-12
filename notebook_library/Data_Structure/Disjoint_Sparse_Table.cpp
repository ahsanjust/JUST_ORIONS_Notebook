struct DST {
  int n, log;
  vector<vector<int>> t;
  DST(vector<int> a) : n(a.size()) {
    if (n == 0) {
      log = 0;
      return;
    }
    int m = 1;
    while (m < n) m <<= 1;
    a.resize(m, 0);
    log = 32 - __builtin_clz(m);
    t.assign(log, vector<int>(m));
    t[0] = a;
    for (int h = 1; h < log; h++) {
      int half = 1 << (h - 1);
      for (int i = 0; i < m; i += half * 2) {
        int mid = i + half;
        t[h][mid - 1] = a[mid - 1];
        for (int j = mid - 2; j >= i; j--) t[h][j] = t[h][j + 1] + a[j];
        t[h][mid] = a[mid];
        for (int j = mid + 1; j < i + half * 2; j++) t[h][j] = t[h][j - 1] + a[j];
      }
    }
  }
  int query(int l, int r) {
    if (l == r) return t[0][l];
    int h = 32 - __builtin_clz(l ^ r);
    return t[h][l] + t[h][r];
  }
};
