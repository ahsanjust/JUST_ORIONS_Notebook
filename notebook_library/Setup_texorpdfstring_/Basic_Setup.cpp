#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("Ofast")
ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
auto rd = []() {
  ll x;
  cin >> x;
  return x;
};
#define dbg(x) cerr << "[" #x "] = " << (x) << "\n"
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int64_t Random(int64_t l, int64_t r) {
  return uniform_int_distribution<int64_t>(l, r)(rnd);
}
// Usage: Random(l, r) returns uniform int in [l, r]
// Use gp_hash_table<ll, ll, custom_hash> mp for
// O(1) lookups without hash collisions
