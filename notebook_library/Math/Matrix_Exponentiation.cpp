vector<vector<int>> multiply(vector<vector<int>>& a, vector<vector<int>>& b) {
  int n = sz(a), m = sz(a[0]), p = sz(b[0]);
  vector<vector<int>> result(n, vector<int>(p, 0));
  for (int i = 0; i < n; i++)
    for (int k = 0; k < m; k++) {
      if (a[i][k] == 0)
        continue;
      for (int j = 0; j < p; j++)
        result[i][j] = ((long long)result[i][j] + (long long)a[i][k] * b[k][j]) % mod;
    }
  return result;
}
vector<vector<int>> expo(vector<vector<int>> t, int p) {
  int n = t.size();
  vector<vector<int>> result(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++)
    result[i][i] = 1;
  assert(p >= 0);
  while (p > 0) {
    if (p & 1)
      result = multiply(result, t);
    t = multiply(t, t);
    p >>= 1;
  }
  return result;
}
