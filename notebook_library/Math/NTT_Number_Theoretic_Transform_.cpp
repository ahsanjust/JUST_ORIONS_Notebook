const int MOD = 998244353, ROOT = 62;
int modpow(int a, int e) {
  int r = 1;
  while (e) {
    if (e & 1)
      r = (long long)r * a % MOD;
    a = (long long)a * a % MOD;
    e >>= 1;
  }
  return r;
}
void ntt(vector<int> &a) {
  int n = a.size(), L = 31 - __builtin_clz(n);
  static vector<int> rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    int z[] = {1, modpow(ROOT, MOD >> s)};
    for (int i = k; i < 2 * k; i++)
      rt[i] = (long long)rt[i / 2] * z[i & 1] % MOD;
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        int z = (long long)rt[j + k] * a[i + j + k] % MOD;
        a[i + j + k] = a[i + j] - z + (z > a[i + j] ? MOD : 0);
        a[i + j] += a[i + j] + z >= MOD ? z - MOD : z;
      }
}
vector<int> conv(const vector<int> &a, const vector<int> &b) {
  if (a.empty() || b.empty())
    return {};
  int s = a.size() + b.size() - 1, n = 1 << (32 - __builtin_clz(s));
  int inv = modpow(n, MOD - 2);
  vector<int> L(a), R(b), out(n);
  L.resize(n);
  R.resize(n);
  ntt(L);
  ntt(R);
  for (int i = 0; i < n; i++)
    out[(n - i) & (n - 1)] = (long long)L[i] * R[i] % MOD * inv % MOD;
  ntt(out);
  return {out.begin(), out.begin() + s};
}
