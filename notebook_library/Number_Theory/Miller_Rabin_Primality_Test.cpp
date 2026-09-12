ull pow(ull a, ull t, ull mod) {
  ull r = 1;
  for (; t; t >>= 1, a = (__uint128_t)a * a % mod)
    if (t & 1) r = (__uint128_t)r * a % mod;
  return r;
}
bool isprime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
  for (ull a : A) {
    ull p = pow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) p = (__uint128_t)p * p % n;
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}
