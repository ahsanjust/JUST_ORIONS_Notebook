int lagrange(vector<int>& y, int k) {
  int n = y.size();
  if (0 <= k && k < n)
    return y[k];
  vector<int> fact(n + 1, 1), invf(n + 1, 1);
  for (int i = 1; i <= n; i++)
    fact[i] = (ll)fact[i - 1] * i % MOD;
  invf[n] = modpow(fact[n], MOD - 2);
  for (int i = n - 1; i >= 0; i--)
    invf[i] = (ll)invf[i + 1] * (i + 1) % MOD;
  vector<int> pre(n + 1, 1), suf(n + 1, 1);
  for (int i = 0; i < n; i++)
    pre[i + 1] = (ll)pre[i] * (((k - i) % MOD + MOD) % MOD) % MOD;
  for (int i = n - 1; i >= 0; i--)
    suf[i] = (ll)suf[i + 1] * (((k - i) % MOD + MOD) % MOD) % MOD;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int num = (ll)pre[i] * suf[i + 1] % MOD;
    int den = (ll)fact[i] * fact[n - 1 - i] % MOD;
    if ((n - 1 - i) & 1)
      den = MOD - den;
    ans = (ans + (ll)y[i] * num % MOD * modpow(den, MOD - 2)) % MOD;
  }
  return ans;
}
