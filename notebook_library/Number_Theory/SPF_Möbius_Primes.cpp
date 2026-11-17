// O(N)
const int N = 1e6 + 9;
int spf[N];      // Smallest prime factor
int phi[N];      // Euler's totient function
int mob[N];      // Möbius function
int divisor[N];  // Number of divisors d(n)
int cnt[N];      // Exponent of spf in n
vector<int> primes;

void linear_sieve() {
  phi[1] = mob[1] = divisor[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!spf[i]) {
      spf[i] = i;
      primes.push_back(i);
      phi[i] = i - 1;
      mob[i] = -1;
      divisor[i] = 2;
      cnt[i] = 1;
    }
    for (int p : primes) {
      if (1LL * i * p >= N) break;
      spf[i * p] = p;
      if (i % p == 0) {
        phi[i * p] = phi[i] * p;
        mob[i * p] = 0;
        cnt[i * p] = cnt[i] + 1;
        divisor[i * p] = divisor[i] / (cnt[i] + 1) * (cnt[i * p] + 1);
        break;
      } else {
        phi[i * p] = phi[i] * (p - 1);
        mob[i * p] = -mob[i];
        cnt[i * p] = 1;
        divisor[i * p] = divisor[i] * 2;
      }
    }
  }
}
// factorize x (x <= (N-1)^2)
vector<pair<int, int>> factorize(int x) {
  vector<pair<int, int>> ret;
  for (int p : primes) {
    if (1LL * p * p > x) break;
    if (x % p == 0) {
      int c = 0;
      while (x % p == 0) x /= p, c++;
      ret.emplace_back(p, c);
    }
  }
  if (x > 1) {
    if (x >= N) ret.emplace_back(x, 1);
    else {
      while (x > 1) {
        int p = spf[x], c = 0;
        while (x % p == 0) x /= p, c++;
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
    ll a = 1;
    for (int d = 1; d <= c; d++) {
      a *= p;
      for (int i = 0; i < n; i++) ret.push_back(ret[i] * a);
    }
  }
  return ret;
}
