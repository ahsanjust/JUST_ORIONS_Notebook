vector<char> segmentedSieve(long long L, long long R) {
  long long lim = sqrt(R);
  vector<char> mark(lim + 1, false);
  vector<long long> primes;
  for (long long i = 2; i <= lim; ++i) {
    if (!mark[i]) {
      primes.emplace_back(i);
      for (long long j = i * i; j <= lim; j += i)
        mark[j] = true;
    }
  }
  vector<char> isPrime(R - L + 1, true);
  for (long long i : primes) {
    ll sm = (L / i) * i;
    if (sm < L)
      sm += i;
    for (long long j = max(i * i, sm); j <= R; j += i)
      isPrime[j - L] = false;
  }
  if (L <= 1) {
    for (long long i = L; i <= 1 && i <= R; i++)
      isPrime[i - L] = false;
  }
  return isPrime;
}
