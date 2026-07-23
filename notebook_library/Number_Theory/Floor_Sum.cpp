ll floor_sum(ll n, ll m, ll a, ll b) {
  ll ans = 0;
  if (a >= m) {
    ans += (n - 1) * n * (a / m) / 2;
    a %= m;
  }
  if (b >= m) {
    ans += n * (b / m);
    b %= m;
  }
  ll y_max = (a * n + b) / m;
  if (y_max == 0)
    return ans;
  ans += floor_sum(y_max, a, m, (a * n + b) % m);
  return ans;
}
