template <typename T>
struct BIT {
  int n;
  vector<T> bit;
  BIT(int n = 0) { init(n); }
  void init(int n_) {
    n = n_;
    bit.assign(n + 1, 0);
  }
  void add(int i, T v) {
    // walk up: i += i & -i moves to next responsible ancestor
    for (; i <= n; i += i & -i) bit[i] += v;
  }
  T sum(int i) {
    T r = 0;
    // walk down: i -= i & -i strips lowest set bit
    for (; i > 0; i -= i & -i) r += bit[i];
    return r;
  }
  T sum(int l, int r) { return sum(r) - sum(l - 1); }
  // find smallest i with prefix_sum(i) >= k (values must be non-negative)
  int find_kth(T k) {
    int i = 0;
    for (int j = 1 << (31 - __builtin_clz(n)); j; j >>= 1)
      if (i + j <= n && bit[i + j] < k) k -= bit[i += j];
    return i + 1;
  }
};
