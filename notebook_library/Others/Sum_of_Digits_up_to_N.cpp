uint64_t sumDigitsUpTo(uint64_t n) {
  if (n <= 0) return 0;
  uint64_t sum = 0;
  for (uint64_t f = 1; f <= n; f *= 10) {
    uint64_t hi = n / (f * 10), cur = (n / f) % 10, lo = n % f;
    sum += hi * 45LL * f + cur * (lo + 1) + f * (cur * (cur - 1) / 2);
  }
  return sum;
}
