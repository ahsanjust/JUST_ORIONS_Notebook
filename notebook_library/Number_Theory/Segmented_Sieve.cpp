vector<char> segmentedSieve(ll L, ll R) {
  ll lim = sqrt(R);
  vector<char> mark(lim + 1, false);
  vector<ll> primes;
  for (ll i = 2; i <= lim; ++i) {
    if (!mark[i]) {
      primes.emplace_back(i);
      for (ll j = i * i; j <= lim; j += i) mark[j] = true;
    }
  }
  vector<char> isPrime(R - L + 1, true);
  for (ll i : primes) {
    ll sm = (L / i) * i;
    if (sm < L) sm += i;
    for (ll j = max(i * i, sm); j <= R; j += i) isPrime[j - L] = false;
  }
  if (L <= 1)
    for (ll i = L; i <= 1 && i <= R; i++) isPrime[i - L] = false;
  return isPrime;
}
