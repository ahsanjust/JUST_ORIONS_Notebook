ll discrete_log(ll a, ll b, ll m) {
  a %= m;
  b %= m;
  if (b == 1)
    return 0;
  ll n = sqrt(m) + 1;
  unordered_map<ll, ll> baby;
  ll cur = b;
  for (ll q = 0; q < n; q++) {
    baby[cur] = q;  // overwrite: keep the largest q for smallest x
    cur = cur * a % m;
  }
  ll an = 1;
  for (ll i = 0; i < n; i++)
    an = an * a % m;
  cur = 1;
  for (ll p = 0; p <= n; p++) {
    if (baby.count(cur)) {
      ll x = p * n - baby[cur];
      if (x >= 0)
        return x;
    }
    cur = cur * an % m;
  }
  return -1;
}
