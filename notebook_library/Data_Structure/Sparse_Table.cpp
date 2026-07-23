struct Sparse {
  vector<vector<int>> t;
  Sparse(const vector<int>& a) {
    int n = a.size(), lg = n ? 32 - __builtin_clz(n) : 0;
    t.assign(lg, vector<int>(n));
    t[0] = a;
    for (int j = 1; j < lg; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        t[j][i] = max(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
  }
  int qry(int l, int r) const {
    int j = 31 - __builtin_clz(r - l + 1);
    return max(t[j][l], t[j][r - (1 << j) + 1]);
  }
};
// For min: s/max/min/   For gcd: s/max/gcd/
