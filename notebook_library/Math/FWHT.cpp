void fwht(vector<int> &a, bool inv, int type) {
  int n = a.size();
  for (int len = 1; len < n; len <<= 1)
    for (int i = 0; i < n; i += 2 * len)
      for (int j = 0; j < len; j++) {
        int u = a[i + j], v = a[i + len + j];
        if (type == 2) {
          a[i + j] = (u + v) % MOD;
          a[i + len + j] = (u - v + MOD) % MOD;
        } else if (type == 1) {
          a[i + j] = inv ? (u - v + MOD) % MOD : (u + v) % MOD;
        } else {
          a[i + len + j] = inv ? (v - u + MOD) % MOD : (u + v) % MOD;
        }
      }
  if (inv && type == 2) {
    int inv_n = modpow(n, MOD - 2);
    for (auto &x : a)
      x = (ll)x * inv_n % MOD;
  }
}
// conv(a, b) = for type=0: c[k]=sum_{i|j=k} a[i]*b[j]
// for type=1: c[k]=sum_{i&j=k} a[i]*b[j]
// for type=2: c[k]=sum_{i^j=k} a[i]*b[j]
