long long lucas(long long n, long long r) {
  if (r == 0)
    return 1;
  return lucas(n / MOD, r / MOD) * nCr(n % MOD, r % MOD) % MOD;
}
