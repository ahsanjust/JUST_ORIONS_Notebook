uint64_t get(uint64_t n) {
  if (n <= 0) return 0;
  uint64_t base = 1, digits = 1, now = 0;
  while (base <= n / 10) {
    base *= 10;
    now += (base - base / 10) * digits;
    digits += 1;
  }
  n -= (base - 1);
  now += n * digits;
  return now;
}
