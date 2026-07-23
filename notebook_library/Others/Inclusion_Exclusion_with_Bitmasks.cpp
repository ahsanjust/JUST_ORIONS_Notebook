template <typename F>
ll inclusion_exclusion(int n, F f) {
  ll ans = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    ll sign = (__builtin_popcount(mask) & 1) ? -1 : 1;
    ans += sign * f(mask);
  }
  return ans;
}
// Count numbers in [1,N] not divisible by any prime in p[0..n-1]
// auto f = [&](int mask) -> ll {
//   ll prod = 1;
//   for (int i = 0; i < n; i++)
//     if (mask >> i & 1) prod *= p[i];
//   return N / prod;
// };
// ll result = inclusion_exclusion(n, f);
