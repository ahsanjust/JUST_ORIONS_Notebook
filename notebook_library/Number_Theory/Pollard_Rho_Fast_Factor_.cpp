#define ull uint64_t
struct Montgomery {
  ull n, nr;
  Montgomery(ull n) {
    this->n = n, nr = 1;
    for (int i = 0; i < 6; i++) nr *= 2 - n * nr;
  }
  ull reduce(__uint128_t x) const {
    ull q = ull(x) * nr, m = ((__uint128_t)q * n) >> 64;
    ull res = (x >> 64) + n - m;
    if (res >= n) res -= n;
    return res;
  }
  ull multiply(ull x, ull y) { return reduce((__uint128_t)x * y); }
};
ull f(ull x, ull n, ull a) {
  return ((__uint128_t)x * x + a) % n;
}
ull diff(ull a, ull b) {
  return a > b ? a - b : b - a;
}
const int M = 1024;
const ull SEED = 42;
ull find_factor(ull n, ull x0 = 2, ull a = 1) {
  ull x = x0, y = x0, d = 1;
  while (d == 1) {
    x = f(x, n, a);
    y = f(f(y, n, a), n, a);
    d = gcd(diff(x, y), n);
  }
  return d == n ? find_factor(n, x0, a + 1) : d;
}
