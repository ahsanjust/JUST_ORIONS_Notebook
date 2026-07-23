// O(N)
const int N = 1e6 + 9;
int spf[N], mob[N];
vector<int> primes;
void sieve() {
  mob[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!spf[i])
      spf[i] = i, mob[i] = -1, primes.push_back(i);
    for (int p : primes) {
      if (p > spf[i] || 1LL * i * p >= N)
        break;
      spf[i * p] = p;
      if (i % p == 0) {
        mob[i * p] = 0;
        break;
      }
      mob[i * p] = -mob[i];
    }
  }
}
// factorize x (x <= (N-1)^2)
vector<pair<int, int>> factorize(int x) {
  vector<pair<int, int>> ret;
  for (int p : primes) {
    if (1LL * p * p > x)
      break;
    if (x % p == 0) {
      int c = 0;
      while (x % p == 0)
        x /= p, c++;
      ret.emplace_back(p, c);
    }
  }
  if (x > 1) {
    if (x >= N)
      ret.emplace_back(x, 1);
    else {
      while (x > 1) {
        int p = spf[x], c = 0;
        while (x % p == 0)
          x /= p, c++;
        ret.emplace_back(p, c);
      }
    }
  }
  return ret;
}
// divisors of x (x <= (N-1)^2)
vector<int> divisors(int x) {
  vector<int> ret = {1};
  for (auto [p, c] : factorize(x)) {
    int n = ret.size();
    long long a = 1;
    for (int d = 1; d <= c; d++) {
      a *= p;
      for (int i = 0; i < n; i++)
        ret.push_back(ret[i] * a);
    }
  }
  return ret;
}
