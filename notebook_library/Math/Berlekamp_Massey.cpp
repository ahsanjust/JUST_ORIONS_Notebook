vector<int> berlekampMassey(vector<int> x) {
  int n = x.size(), L = 0, m = 1;
  ll b = 1;
  vector<int> C(n), B(n);
  C[0] = B[0] = 1;
  for (int i = 0; i < n; i++, m++) {
    ll d = x[i] % MOD;
    for (int j = 1; j <= L; j++)
      d = (d + (ll)C[j] * x[i - j]) % MOD;
    if (!d)
      continue;
    vector<int> T = C;
    ll c = d * modpow(b, MOD - 2) % MOD;
    for (int j = m; j < n; j++)
      C[j] = (C[j] - c * B[j - m] + MOD) % MOD;
    if (2 * L <= i) {
      L = i - L + 1;
      B = T;
      b = d;
      m = 0;
    }
  }
  C.resize(L + 1);
  C.erase(C.begin());
  for (auto &i : C)
    i = (MOD - i) % MOD;
  return C;
}
// Kitamasa: compute k-th term of linear recurrence
// using C (from BM) and first terms.
// Complexity O(L^2 log k).
