mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<uint64_t> rnd(N);
for (auto &x : rnd)
  x = rng();

// Prefix XOR for subarray hash
vector<uint64_t> pre(n + 1, 0);
for (int i = 0; i < n; i++)
  pre[i + 1] = pre[i] ^ rnd[a[i]];
// xor of range [l, r] = pre[r+1] ^ pre[l]
