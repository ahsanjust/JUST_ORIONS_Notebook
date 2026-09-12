int gauss(vector<vector<int>> a, vector<int>& ans) {
  int n = a.size(), m = a[0].size() - 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++) {
    int sel = row;
    for (int i = row; i < n; i++)
      if (a[i][col]) {
        sel = i;
        break;
      }
    if (!a[sel][col]) continue;
    swap(a[sel], a[row]);
    int inv = modpow(a[row][col], MOD - 2);
    for (int j = col; j <= m; j++) a[row][j] = (ll)a[row][j] * inv % MOD;
    for (int i = 0; i < n; i++) {
      if (i == row) continue;
      int c = a[i][col];
      for (int j = col; j <= m; j++) a[i][j] = (a[i][j] - (ll)c * a[row][j] % MOD + MOD) % MOD;
    }
    where[col] = row++;
  }
  ans.assign(m, 0);
  for (int i = 0; i < m; i++)
    if (where[i] != -1) {
      ans[i] = a[where[i]][m];
      if (ans[i] < 0) ans[i] += MOD;
    }
  for (int i = 0; i < n; i++) {
    ll sum = 0;
    for (int j = 0; j < m; j++) sum = (sum + (ll)ans[j] * a[i][j]) % MOD;
    if (sum != a[i][m]) return 0;
  }
  for (int i = 0; i < m; i++)
    if (where[i] == -1) return 2;  // infinite
  return 1;                        // unique
}
